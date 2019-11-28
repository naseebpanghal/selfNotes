# docker-specific

- Install and create rockchip docker using below link:
https://github.com/rockchip-linux/docker-rockchip
- To install docker properly after apt install docker below command should be run.
sudo curl -sSL https://get.docker.com/ | sh

- Map package directory and enter docker:
docker run -it -v /home/naseeb/wowvision/webrtc/build_ball:/home/rk/packages rockchip /bin/bash
docker run -it -v /home/naseeb/wowvision/webrtc/boost_1_64_0:/home/rk/packages rockchip /bin/bash

Build Package on docker:
cd /home/rk/packages/
DEB_BUILD_OPTIONS=nocheck dpkg-buildpackage -rfakeroot -b -d -uc -us -aarmhf
ls ../ | grep *.deb


To Commit into a docker
1. docker run -it -v /home/naseeb/wowvision/webrtc/build_ball:/home/rk/packages rockchip /bin/bash
2. Install anything for eg:
    $ apt install <any package>
    $ exit
3. docker ps -a 
   This command will list all the containers. Here you can get the container ID on the top which you just exit and we need to use this container id to commit.
4. docker commit <container id from step 3> rockchip
    name rockhip is the name of docker image -> from step 1.
