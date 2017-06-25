include sources.mk

CPPFLAGS= -E
LDFLAGS= -Xlinker -Map=project1.map
BIN= project1.elf


ifeq ($(PLATFORM),HOST)
	CC = gcc
	FLAGS = -Wall -Werror -g -O0 -std=c99 -DPROJECT1 -DVERBOSE
endif

%.i:	%.c
		$(CC) $(INCLUDES) $(FLAGS) -E -o $@ $^
%.asm:	%.c
		$(CC) $(INCLUDES) $(FLAGS) -S -o $@ $^
%.o:	%.c
		$(CC) $(INCLUDES) $(FLAGS) -c -o $@ $^
%.d:	%.c
		$(CC) $(INCLUDES) $(FLAGS) -M -o $@ $^

OBJS:=$(SRC:.c=.o)
PP:=$(SRC:.c=.i)
ASEM:=$(SRC:.c=.asm)
DEP:=$(SRC:.c=.d)

.PHONY:	compile-all
compile-all:	$(OBJS)

.PHONY: clean
clean:	
	rm -rf *.o *.i *.asm *.d *.map *.out *.elf $(BIN)

.PHONY: build
build:	clean $(BIN)

$(BIN):	$(OBJS) $(PP) $(ASEM) $(DEP)
	$(CC) $(OBJS) $(FLAGS) $(LDFLAGS) -o $(BIN)

