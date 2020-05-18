1. extract elementary stream(h264) from mp4/mov file using ffmpeg
$ ffmpeg -i test.flv -vcodec copy -an -bsf:v h264_mp4toannexb test.h264
or 
Use VLC, Media->Convert/Save ==> Select File ==> select profile ==> select destination folder ==> enter suitable file name ==> start
                                                  \
                                                   ==> profile setting ==> uncheck audio part(if only video is required)
