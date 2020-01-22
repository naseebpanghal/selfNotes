MPP demo application

This demo is for lowlevel API rockchip MPI/MPP with zero copy output to DRM and display as DRM FB overlay with ASUS Tinker (and other) without Xserver directly from console.
MPP is low level API for ffmpeg/OpenMax/gstreamer/libva (see https://github.com/rockchip-linux/mpp/blob/develop/readme.txt ).
TinkerBoard/RK3288 has two video coprocessors VPU1 (for h264 and other decoders and encoders) (/dev/vpu-service) and HEVC_DEC (for HEVC decoder) (/dev/hevc-service) (The problem is in naming "-" and/or "_", see patch).
MPP is https://github.com/rockchip-linux/mpp works on TinkerBoard/RK3288 (see https://github.com/rockchip-linux/mpp/blob/develop/osal/mpp_platform.cpp#L53 ).
This demo uses MPP buffers (frames) "Mode 3: Pure external mode" (see https://github.com/rockchip-linux/mpp/blob/develop/readme.txt#L354 ) with zero copy DRM buffers.
DRM (/dev/dri/card0) is used (see https://github.com/rockchip-linux/mpp/blob/develop/inc/mpp_buffer.h#L152 ) with some problems (see patch). 
DRM buffers works in "commit flow" DRM buffes mode ( https://github.com/rockchip-linux/mpp/blob/develop/inc/mpp_buffer.h#L97 ).
The demo use "split standard mode". Warning - do not use "advanced mode" (see https://github.com/rockchip-linux/mpp/blob/develop/inc/mpp_task.h#L62 ) works only with MJPEG now.

0) prepare board / download os

I used ASUS Tinker Board with TinkerOS_Debian V1.4 (https://www.asus.com/uk/Single-board-Computer/Tinker-Board/HelpDesk_Download/).
Many build dependencies like autoconf automake libdrm-dev libtool cmake git ...

1) build MPP

git clone -b for_linux https://github.com/rockchip-linux/mpp.git
cd mpp
git apply ../mpp_for_tinkeros_drm.patch
# there is development in progress, there should not be needed patches later
cmake -DRKPLATFORM=ON -DHAVE_DRM=ON -DCMAKE_BUILD_TYPE=Debug .
make -j4
make install

(installed in /usr/local/...)

2) build application (mpp_dec)

make

3) prepare h264 and/or hevc(h265) raw streams

ffmpeg -i bbb_sunflower_2160p_30fps_normal.mp4  -c:v copy -an -bsf:v h264_mp4toannexb 4k.h264
ffmpeg -i bbb-1920x1080-cfg06.mkv -c:v copy -an -bsf:v hevc_mp4toannexb 2k.hevc 
ffmpeg -i bbb-3840x2160-cfg02.mkv -c:v copy -an -bsf:v hevc_mp4toannexb 4k.hevc 

4) test it

./mpi_dec
./mpi_dec "filename" "type"
./mpi_dec 4k.h264 7
./mpi_dec 2k.hevc 16777220

NOTES:

CPU:

- RK CPU power management is active (interactive mode) and CPU very slow reacts to load it leads to drops frame due to high CPU loads peaks.
  SEE: 
     grep ''  /sys/devices/system/cpu/cpufreq/policy0/*
  TEST:
     echo userspace > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor 
     echo 216000 > /sys/devices/system/cpu/cpufreq/policy0/scaling_setspeed
     ./mpi_dec 4k.hevc 16777220
  and compute frame rate "FRAME 57157.321400 first 43613795 previous   1253 frid 2024" == frameid/first(usec) = 2024/43.613795 = 46 FPS
  
RESULTS (4k.hevc):

   freqency GHz   0.1   0.2   0.4   0.8   1.0   1.2
   CPU load %     <65   <60   <30   <20   <16   <14
   FPS             36    46    62    68    71    72
   TEMPERATURE     ~55              ~60         ~62
   
Be aware of CPU power management, it has negative impact on FPS.
Fix CPU to >=0.4Ghz or higher like:
     echo userspace > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor 
     echo 1008000 > /sys/devices/system/cpu/cpufreq/policy0/scaling_setspeed
OR:
     echo interactive > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor
     echo 1008000 > /sys/devices/system/cpu/cpufreq/policy0/scaling_min_freq

DECODER:

- decoder running at maximum realtime speed (eg. no clock synchronization from sources) and DRM FB displays at vsync rate (eg. some decoded frames are dropped/skipped).

RESULTS (with fixed 1GHz CPU):

                   hevc(h265)   h264
2k (1080p, FHD)    240 FPS      69 FPS
4k (2160p, UHD)     71 FPS      32 FPS
