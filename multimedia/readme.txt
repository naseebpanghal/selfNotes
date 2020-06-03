1. extract elementary stream(h264) from mp4/mov file using ffmpeg
$ ffmpeg -i test.flv -vcodec copy -an -bsf:v h264_mp4toannexb test.h264
or 
Use VLC, Media->Convert/Save ==> Select File ==> select profile ==> select destination folder ==> enter suitable file name ==> start
                                                  \
                                                   ==> profile setting ==> uncheck audio part(if only video is required)
                                                   
 2. Miracast links:
 https://hsc.com/DesktopModules/DigArticle/Print.aspx?PortalId=0&ModuleId=1215&Article=221
 https://www.iwavesystems.com/wireless-devices-to-seamless-videodisplay
