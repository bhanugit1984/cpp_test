# cpp_test

banking system to run in docker

compile the Bank.cpp in Linux machine of any Ubuntu/CentOs systems

for build:
sudo docker build . -t cpp_test:1

for run:
sudo docker run --rm -it cpp_test:1

commands to install docker in ubuntu are below
sudo apt update
sudo apt install docker.io
sudo docker version
sudo usermod -a -G docker ubuntu