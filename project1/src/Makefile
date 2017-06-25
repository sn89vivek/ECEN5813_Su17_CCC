PLATFORM=HOST

CPPFLAGS= -E
LDFLAGS= -Xlinker -Map=project1.map
BIN= project1.elf
RM= /bin/rm

ifeq ($(PLATFORM),HOST)
	CC = gcc
	CFLAGS = -Wall -Werror -g -O0 -std=c99 -DPROJECT1 -DVERBOSE
	SRC = \
		memory.c		\
		conversion.c		\
		debug.c			\
		main.c			\
		project1.c
	INCLUDES = \
		-I ../include/common
endif

ifeq ($(PLATFORM),CMSIS)
	CC = gcc
	CFLAGS = -Wall -Werror -g -O0 -std=c99 -DPROJECT1 -DVERBOSE
	SRC = \
		memory.c		\
		conversion.c		\
		debug.c			\
		main.c			\
		project1.c
	INCLUDES = \
		-I ../include/common	\
		-I ../include/CMSIS
endif

ifeq ($(PLATFORM),MLK)
	CC = gcc
	CFLAGS = -Wall -Werror -g -O0 -std=c99 -DPROJECT1 -DVERBOSE
	SRC = \
		memory.c		\
		conversion.c		\
		debug.c			\
		main.c			\
		project1.c		\
		startup_MKL25Z4.S	\
		system_MKL25Z4.c
	INCLUDES = \
		-I ../include/common	\
		-I ../include/kl25z
endif

%.i : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -E -o $@ $^
%.asm : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -S -o $@ $^
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^
%.d : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -M -o $@ $^

OBJS := $(SRC:.c=.o)
PP := $(SRC:.c=.i)
ASM := $(SRC:.c=.asm)
DEP := $(SRC:.c=.d)

.PHONY:	all
all: $(BIN)
	@true

.PHONY: clean
clean:
	@$(RM) -f *.o
	@$(RM) -f *.i
	@$(RM) -f *.asm
	@$(RM) -f *.map
	@$(RM) -f *.out
	@$(RM) -f *.elf
	@$(RM) -f $(BIN)

.PHONY: build
build: clean $(BIN)

$(BIN):	$(OBJS) $(PP) $(ASM) $(DEP)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(BIN)
