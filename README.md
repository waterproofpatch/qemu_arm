# Cross Compile & GDB debug ARM binary on Linux

Simple example for compiling barebones ARM binary and running it under qemu-ARM.

## Prerequisites:

* gnu-arm toolchain for cross compiling
```
sudo apt-get install gcc-arm-none-eabi
sudo apt-get install gcc-arm-linux-gnueabi
```

* qemu-user
```
sudo apt-get install qemu-user
```

* gdb-arm-none-eabi
```
sudo apt-get install gdb-arm-none-eabi
```

If you want to run using docker:
* docker
(See docker website)

* docker-compose
(See docker website)

## Build (cross-compile):
```
make
```

## Run under qemu-gdb for ARM (for remote debugging on localhost):
```
qemu-arm -singlestep -g 12345 bin/loop
```

* ```-singlestep``` causes QEMU to halt on the first instruction.

* ```-g``` specifies which port to listen on for remote debugging clients.


## Connect with remote gdb client:
```
arm-none-eabi-gdb
file bin/loop
target remote localhost:12345
```

## Bring up gdb terminal-based frontend:
```
Ctrl+X + A
```

## Useful layouts:
```
layout regs
layout next
...
```
### Personal favorites:
```
layout split
layout regs
```
#### Now, begin GDB stepping...
```
s
s
s
...
```

## Server example (manual, no docker)


To run under QEMU, we must specify the path to the ARM linker (and other .so files, compiled for ARM, such as libc):

```
qemu-arm -L /usr/arm-linux-gnueabi/ bin/server
```


And, for debugging:
```
qemu-arm -singlestep -g 12345 -L /usr/arm-linux-gnueabi/ bin/server
```

Now connect with qemu-gdb using the same method from above.


## Server example (automatic, docker)
```
make
docker-compose up
```

Now a container is running exposing the server's port on 5001 and the GDB server on 12345.

On the hosting running the gdb client:
```
arm-none-eabi-gdb
target remote 0.0.0.0:12345
b *main
c
```

The above is automated via:
```
arm-none-eabi-gdb -x gdb_commands.txt
```
