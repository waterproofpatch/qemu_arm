FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install qemu-user -y
RUN apt-get install gdb-arm-none-eabi -y
RUN apt-get install gcc-arm-none-eabi -y
RUN apt-get install gcc-arm-linux-gnueabi -y
RUN apt-get install make -y
RUN apt-get install gcc -y

ADD . /sandbox
WORKDIR ./sandbox

RUN make

ENTRYPOINT qemu-arm -singlestep -g 12345 -L /usr/arm-linux-gnueabi/ bin/server
