.PHONY = all clean

EXEC := server 
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src%,obj%, $(patsubst %.c,%.o, $(SRCS)))

LIBS :=
INCLUDES :=
CFLAGS := -Wall -pedantic -Werror=incompatible-pointer-types-discards-qualifiers -std=c99 -g -O0
CC := clang

all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

# Compile all *.c files to *.o
obj/%.o: src/%.c
	@mkdir -p $(@D) # Make `obj/` dir
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf obj/
	rm -f $(EXEC)
	rm -rf .cache/
