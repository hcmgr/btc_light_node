CC=g++
FLAGS=-g -pedantic -fPIC
EXECS=server client

all: server client


server: server.cpp
		$(CC) $(FLAGS) $^ -o $@

client: client.cpp
		$(CC) $(FLAGS) $^ -o $@

clean:
		rm -f $(EXECS)
		rm -rf *.dSYM
		rm a.out
                
                

