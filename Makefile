###
# Makefile to compile and install CapsLockLed program

APP=capslockled
BINPATH=~/bin

CC=gcc
CFLAGS=-Wall
LDFLAGS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(SRC) $(APP)

clean:
	rm $(wildcard $(OBJ) $(APP))

install: all
	sudo chown root $(APP)
	sudo chmod u+s $(APP)
	sudo cp $(APP) $(BINPATH)

$(APP): $(OBJ)
	@echo "linking $(OBJ) to $@"
	@$(CC) $(LDFLAGS) $(OBJ) -o $@

%.o: %.c
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean install
