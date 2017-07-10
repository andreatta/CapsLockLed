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
	@echo "Clean-up last build"
	@rm -f $(wildcard $(OBJ) $(APP))

suid: all
	@echo "Change owner to root and set SUID bit"
	@sudo chown root $(APP)
	@sudo chmod u+s $(APP)

install: all suid
	@echo "Copy binary to $(BINPATH)"
	@sudo cp $(APP) $(BINPATH)

$(APP): $(OBJ)
	@echo "linking $(OBJ) to $@"
	@$(CC) $(LDFLAGS) $(OBJ) -o $@

%.o: %.c
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean install
