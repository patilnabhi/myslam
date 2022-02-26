#!/usr/bin/env bash

# Check args
if [ "$#" -ne 1 ]; then
  echo "Error! Usage should be: ./run_docker_export.sh IMAGE_NAME"
fi

xhost +

docker run \
  --gpus all \
  --net=host \
  -e SHELL \
  -e DISPLAY=unix$DISPLAY \
  -e NO_AT_BRIDGE=1 \
  -e QT_X11_NO_MITSHM=1 \
        -v /tmp/.X11-unix:/tmp/.X11-unix:rw --privileged \
  -v /tmp/.docker.xauth:/tmp/.docker.xauth \
  -v /home/$USER/working_dir:/home/$USER/working_dir \
  -e XAUTHORITY=/tmp/.docker.xauth \
  -it --rm $1 /bin/bash