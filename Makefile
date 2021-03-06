# Name of the project
PROJ_NAME=main
 
# .c files
C_SOURCE=$(wildcard *.c)
 
# .h files
H_SOURCE=$(wildcard headers/*.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)
 
# Compiler
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -fopenmp	\
 
#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ -fopenmp

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

paralelo:
	gcc -g -Wall -fopenmp *.c -o main -DPARALELO
	rm -rf *.o *.out *.dot *.txt *~

clean:
	rm -rf *.o *.out *.dot *.txt $(PROJ_NAME) *~