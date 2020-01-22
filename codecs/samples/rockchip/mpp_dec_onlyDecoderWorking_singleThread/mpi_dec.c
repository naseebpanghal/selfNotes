/*
   Copyright (c) 2017, Martin Cerveny

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of the copyright holder nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define MODULE_TAG "mpi_dec"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#include <unistd.h>

#include <rk_mpi.h>


#define READ_BUF_SIZE (SZ_1M)
#define MAX_FRAMES 24		// min 16 and 20+ recommended (mpp/readme.txt) ?

struct {
  MppCtx          ctx;
  MppApi          *mpi;
} mpi;


int dump_mpp_frame_to_file(MppFrame frame, FILE *fp)
{
    RK_U32 width = 0;
    RK_U32 height = 0;
    RK_U32 h_stride = 0;
    RK_U32 v_stride = 0;
    MppFrameFormat fmt = MPP_FMT_YUV420SP;
    MppBuffer buffer = NULL;
    RK_U8 *base = NULL;

    if (!fp || !frame)
        return -1;

    width = mpp_frame_get_width(frame);
    height = mpp_frame_get_height(frame);
    h_stride = mpp_frame_get_hor_stride(frame);
    v_stride = mpp_frame_get_ver_stride(frame);
    fmt = mpp_frame_get_fmt(frame);
    buffer = mpp_frame_get_buffer(frame);

    if(!buffer)
        return -2;

    base = (RK_U8 *)mpp_buffer_get_ptr(buffer);
    {
        RK_U32 i;
        RK_U8 *base_y = base;
        RK_U8 *base_u = base + h_stride * v_stride;
        RK_U8 *base_v = base_u + h_stride * v_stride / 4;

        for (i = 0; i < height; i++, base_y += h_stride)
            fwrite(base_y, 1, width, fp);
        for (i = 0; i < height / 2; i++, base_u += h_stride / 2)
            fwrite(base_u, 1, width / 2, fp);
        for (i = 0; i < height / 2; i++, base_v += h_stride / 2)
            fwrite(base_v, 1, width / 2, fp);
    }

    return 0;
}

int decode(FILE *mFout)
{
  int ret;
  MppFrame  frame  = NULL;
  int frm_eos = 0;

  ret = mpi.mpi->decode_get_frame(mpi.ctx, &frame);

  dump_mpp_frame_to_file(frame, mFout);
  if (frame) {
    if (mpp_frame_get_info_change(frame)) {
      ret = mpi.mpi->control(mpi.ctx, MPP_DEC_SET_INFO_CHANGE_READY, NULL);
    }
    frm_eos = mpp_frame_get_eos(frame);
    mpp_frame_deinit(&frame);
  } else assert(0);
  if(frm_eos) return 1;
  return 0;
}

// main

int main(int argc, char **argv)
{
  int ret;	
  int i, j;

  ////////////////////////////////// PARAMETER SETUP
  if (argc != 3) {
    printf("usage: %s raw_filename mpp_coding_id\n\n", argv[0]);
    mpp_show_support_format();
    return 0;
  }

  int data_fd=open(argv[1], O_RDONLY);

  MppCodingType mpp_type = (MppCodingType)atoi(argv[2]);
  ret = mpp_check_support_format(MPP_CTX_DEC, mpp_type);

  ////////////////////////////////////////////// MPI SETUP
  MppPacket packet;
  void *pkt_buf = malloc(READ_BUF_SIZE);
  ret = mpp_packet_init(&packet, pkt_buf, READ_BUF_SIZE);

  ret = mpp_create(&mpi.ctx, &mpi.mpi);

  // decoder split mode (multi-data-input) need to be set before init
  int param = 1;
  ret = mpi.mpi->control(mpi.ctx, MPP_DEC_SET_PARSER_SPLIT_MODE, &param);
  ret = mpp_init(mpi.ctx, MPP_CTX_DEC, mpp_type);

  // blocked/wait read of frame in thread 
  param = MPP_POLL_BLOCK;
  ret = mpi.mpi->control(mpi.ctx, MPP_SET_OUTPUT_BLOCK, &param);

  ////////////////////////////////////////////// MAIN LOOP

  int decoder_ret = 0;
  int encoded_data_finish = 0;
  FILE *mFout = fopen("rawdump.yuv", "wb+");
  if (!mFout) {
    printf("failed to open output file .\n");
    return -1;
  }

  do {
    if(!encoded_data_finish)
    {
      do {
        ret=read(data_fd, pkt_buf, READ_BUF_SIZE);
      } while (ret == -1 && (errno == EINTR || errno == EAGAIN));
      int read_size = ret;
      static RK_S64 pts, dts;
      if (read_size) {
        mpp_packet_set_pos(packet, pkt_buf);
        mpp_packet_set_length(packet, read_size);

        while (MPP_OK != (ret = mpi.mpi->decode_put_packet(mpi.ctx, packet))) {
          // buffer 4 packet is hardcoded (actual is MPP_DEC_GET_STREAM_COUNT) and does not support blocking write 
          usleep(10000);
        }

        RK_U32 s_cnt, v_cnt; 
        ret = mpi.mpi->control(mpi.ctx, MPP_DEC_GET_STREAM_COUNT, &s_cnt);
        ret = mpi.mpi->control(mpi.ctx, MPP_DEC_GET_VPUMEM_USED_COUNT, &v_cnt);
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);	
        printf("PACKET SEND %d.%06d S %d V %d\n", ts.tv_sec, ts.tv_nsec/1000, s_cnt, v_cnt);	
      }
      else {
        printf("PACKET EOS\n");
        mpp_packet_set_eos(packet);
        mpp_packet_set_pos(packet, pkt_buf);
        mpp_packet_set_length(packet, 0);
        while (MPP_OK != (ret = mpi.mpi->decode_put_packet(mpi.ctx, packet))) {
          usleep(10000);
        }
        encoded_data_finish = 1;
      }
    }
    decoder_ret = decode(mFout);
    if(decoder_ret) break;
  } while(1);
  close(data_fd);

  ////////////////////////////////////////////// MPI CLEANUP

  ret = mpi.mpi->reset(mpi.ctx);

  mpp_packet_deinit(&packet);
  mpp_destroy(mpi.ctx);
  free(pkt_buf);

  return 0;
}

