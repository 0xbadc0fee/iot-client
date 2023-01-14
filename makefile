#CC=arm-linux-gnueabi-gcc
CC=gcc
CCFLAGS=
INCLUDES=
LFLAGS=-L/usr/lib/x86_64-linux-gnu
#LFLAGS=-L/buildroot/output/build/libcurl-7.83.1/include/curl
LIBS=-lcurl -lpthread

SRC=requestor.c
OBJ=$(SRC:.c=.o)
MAIN=test

RM=rm -rf


.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
    
$(MAIN): $(OBJ)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $(MAIN) $(OBJ) $(LFLAGS) $(LIBS)
    
all: $(MAIN)

clean:
	$(RM) $(MAIN) *.o *~
