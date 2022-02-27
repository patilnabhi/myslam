#/bin/bash

# Create X11 Instance
export DISPLAY=:0
xinit &

# Start the container
docker run -it \
  --gpus=all \
  --name=super-container \
  --security-opt seccomp=unconfined \
  --init \
  --net=host \
  --privileged=true \
  --rm=true \
  -e DISPLAY=:1 \
  -v /tmp/.X11-unix/X0:/tmp/.X11-unix/X0:ro \
  -v /etc/localtime:/etc/localtime:ro \
  -v /share-docker:/share-docker \
  -v /home/$USER/working_dir:/home/$USER/working_dir \
  -e VNC_PORT=$2 \
  --expose=$2 \
  $1

# Kill X11 Server
pkill xinit