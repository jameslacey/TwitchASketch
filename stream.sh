streaming() {
 CBR="20k" # constant bitrate (should be between 1000k - 3000k)
     

ffmpeg  \
-f v4l2 -video_size 640x480 -framerate 5 -i /dev/video0 \
-c:v libx264 -x264-params keyint=120 -preset slow  -pix_fmt yuv420p \
-maxrate $CBR -minrate $CBR -bufsize $CBR   \
-nostdin -f flv \
rtmp://live.twitch.tv/app/live_STREAM_KEY_HERE

}

streaming &> /dev/null
