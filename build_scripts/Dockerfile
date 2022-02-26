FROM ubuntu:20.04

# ARG SOURCEFORGE=https://sourceforge.net/projects
# ARG TURBOVNC_VERSION=2.1.2
# ARG VIRTUALGL_VERSION=2.5.2
# ARG LIBJPEG_VERSION=1.5.2
# ARG WEBSOCKIFY_VERSION=0.8.0
# ARG NOVNC_VERSION=1.0.0

MAINTAINER Abhishek Patil <Abhishek.Patil@hilti.com>

ENV DEBIAN_FRONTEND=noninteractive


#---------------------------------------------------------------------
# Install Linux stuff
#---------------------------------------------------------------------
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates curl wget less sudo lsof git net-tools nano psmisc xz-utils nemo vim net-tools iputils-ping traceroute htop \
    lubuntu-desktop \
    xterm terminator zenity make cmake gcc libc6-dev \
    x11-xkb-utils xauth xfonts-base xkb-data \
    mesa-utils xvfb libgl1-mesa-dri libgl1-mesa-glx libglib2.0-0 libxext6 libsm6 libxrender1 \
    libglu1 libxv1 \
    python3 python3-numpy libpython3-dev libsuitesparse-dev libgtest-dev \
    libeigen3-dev libsdl1.2-dev libsdl-image1.2-dev libsdl-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# #---------------------------------------------------------------------
# # Install VirtualGL and TurboVNC
# #---------------------------------------------------------------------
# RUN cd /tmp && \
#     curl -fsSL -O ${SOURCEFORGE}/turbovnc/files/${TURBOVNC_VERSION}/turbovnc_${TURBOVNC_VERSION}_amd64.deb \
#     -O ${SOURCEFORGE}/libjpeg-turbo/files/${LIBJPEG_VERSION}/libjpeg-turbo-official_${LIBJPEG_VERSION}_amd64.deb \
#     -O ${SOURCEFORGE}/virtualgl/files/${VIRTUALGL_VERSION}/virtualgl_${VIRTUALGL_VERSION}_amd64.deb \
#     -O ${SOURCEFORGE}/virtualgl/files/${VIRTUALGL_VERSION}/virtualgl32_${VIRTUALGL_VERSION}_amd64.deb && \
#     dpkg -i *.deb && \
#     rm -f /tmp/*.deb && \
#     sed -i 's/$host:/unix:/g' /opt/TurboVNC/bin/vncserver
# ENV PATH ${PATH}:/opt/VirtualGL/bin:/opt/TurboVNC/bin

# #---------------------------------------------------------------------
# # Install noVNC
# #---------------------------------------------------------------------
# RUN curl -fsSL https://github.com/novnc/noVNC/archive/v${NOVNC_VERSION}.tar.gz | tar -xzf - -C /opt && \
#     curl -fsSL https://github.com/novnc/websockify/archive/v${WEBSOCKIFY_VERSION}.tar.gz | tar -xzf - -C /opt && \
#     mv /opt/noVNC-${NOVNC_VERSION} /opt/noVNC && \
#     chmod -R a+w /opt/noVNC && \
#     mv /opt/websockify-${WEBSOCKIFY_VERSION} /opt/websockify && \
#     cd /opt/websockify && make && \
#     cd /opt/noVNC/utils && \
#     ln -s /opt/websockify

# COPY requirements/xorg.conf /etc/X11/xorg.conf
# COPY requirements/index.html /opt/noVNC/index.html
# COPY requirements/run /opt/noVNC/utils/websockify/run

# Expose whatever port NoVNC will serve from. In our case it will be 40001, see ./start_desktop.sh
# EXPOSE 40001
# ENV DISPLAY :1

# #---------------------------------------------------------------------
# # Install desktop files for this user
# #---------------------------------------------------------------------
# RUN mkdir -p /root/Desktop
# COPY ./requirements/terminator.desktop /root/Desktop
# RUN mkdir -p /root/.config/terminator
# COPY ./requirements/terminator_config /root/.config/terminator/config
# COPY ./requirements/self.pem /root/self.pem

# # Precede bash on all new terminator shells with vglrun so that 3d graphics apps will use the GPU
# RUN perl -pi -e 's/^Exec=terminator$/Exec=terminator -e "vglrun bash"/g' /usr/share/applications/terminator.desktop

# # Start setups for TurboVNC
# RUN mkdir -p /root/.vnc
# COPY ./requirements/xstartup.turbovnc /root/.vnc/xstartup.turbovnc
# RUN chmod a+x /root/.vnc/xstartup.turbovnc

# ====================================================================================================================

#---------------------------------------------------------------------
# Install softwares
#---------------------------------------------------------------------
# COPY . /tmp/ir

# # Install other dependencies
RUN apt-get -y update && apt-get install -y \
    sudo ssh build-essential git software-properties-common apt-utils curl cmake \
    libglew-dev \
    libeigen3-dev libboost-all-dev libopencv-dev libgoogle-glog-dev libgflags-dev libfmt-dev \
    unzip


# Sophus
RUN cd /tmp/ \
    && git clone https://github.com/strasdat/Sophus.git \
    && cd Sophus \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j$(nproc) \
    && make install

# ceres
RUN cd /tmp/ \
    && git clone https://ceres-solver.googlesource.com/ceres-solver \
    && cd ceres-solver \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j$(nproc) \
    && make install

# G2O
RUN cd /tmp/ \
    && git clone https://github.com/RainerKuemmerle/g2o.git \
    && cd g2o \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j$(nproc) \
    && make install


# # ------------------------------------------------------------------------------------ #

#Fix locale (UTF8) issue https://askubuntu.com/questions/162391/how-do-i-fix-my-locale-issue
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y locales
RUN locale-gen "en_US.UTF-8"


# Env vars for the nvidia-container-runtime.
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute

RUN ldconfig
RUN rm -rf /tmp/*

#---------------------------------------------------------------------
# Startup
#---------------------------------------------------------------------
# COPY requirements/launch.sh /opt/noVNC/utils/launch.sh
# COPY requirements/start_desktop.sh /usr/local/bin/start_desktop.sh

# Uncomment for autostart of the VNC server
# CMD /usr/local/bin/start_desktop.sh
CMD /bin/bash