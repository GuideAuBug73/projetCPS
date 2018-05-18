CC=gcc
EXEC = projet
CFLAGS = -Wall -I ../lib
SRCS = $(wildcard *.c)
OBJS = $(SRCS: .c=.o)

all : $(EXEC)

$(EXEC) : 	$(OBJS)
			$(CC) -g $(CFLAGS) -o $@ $(OBJS) -lm
	
%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean : 
		@echo "On efface les fichiers objets"
		rm -f *.o

mrproper :	clean
			rm -f $(EXEC)
