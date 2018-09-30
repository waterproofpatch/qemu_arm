SRC_DIR=src
BIN_DIR=bin
LOOP_NAME=loop
MAIN_NAME=main
SERVER_NAME=server

all: main server
	@mkdir -p $(BIN_DIR)
	arm-linux-gnueabi-as $(SRC_DIR)/$(LOOP_NAME).s -g -o $(BIN_DIR)/$(LOOP_NAME).o
	arm-linux-gnueabi-ld $(BIN_DIR)/$(LOOP_NAME).o -o $(BIN_DIR)/$(LOOP_NAME)

clean:
	rm -rf bin

main:
	@mkdir -p $(BIN_DIR)
	arm-linux-gnueabi-gcc $(SRC_DIR)/$(MAIN_NAME).c -g -o $(BIN_DIR)/$(MAIN_NAME)
	
server:
	@mkdir -p $(BIN_DIR)
	arm-linux-gnueabi-gcc $(SRC_DIR)/$(SERVER_NAME).c -g -o $(BIN_DIR)/$(SERVER_NAME)
	gcc $(SRC_DIR)/$(SERVER_NAME).c -g -o $(BIN_DIR)/$(SERVER_NAME)_x86


install:
	@sudo apt-get install qemu-user
	@sudo apt-get install gdb-arm-none-eabi
	@sudo apt-get install gcc-arm-none-eabi
	@sudo apt-get install gcc-arm-linux-gnueabi



