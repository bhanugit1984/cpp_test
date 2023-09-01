# cpp_test

banking system to run in docker

1) clone the source files, header files and docker file into your workspace in linux machine

2) using the dockerfile in the workspace run the below commands

for build:
  sudo docker build . -t cpp_test:1

for run:
  sudo docker run --rm -it cpp_test:1

3) commands to install docker in ubuntu are below
sudo apt update

sudo apt install docker.io

sudo docker version

sudo usermod -a -G docker ubuntu

sudo apt-get install docker-compose-plugin

5) When you use, unit testcases, comment the main in Bank.cpp or remove main in that file, and change the cpp file in the Dockerfile to run all the unit testcases at once
