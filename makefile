CC=clang++
FLAGS=-g -Wall -fPIC
BASE_PATH=/opt/homebrew/opt/openssl@3
INCLUDES=-I$(BASE_PATH)/include/
LINKS=-L$(BASE_PATH)/lib -lcrypto -lssl
TARGETS=server client
EXECS=$(TARGETS) + crypto

all: $(TARGETS)

server: server.cpp block.cpp 
		$(CC) $(FLAGS) $^ -o $@

client: client.cpp block.cpp 
		$(CC) $(FLAGS) $^ -o $@

crypto: crypto.cpp 
		$(CC) $(FLAGS) $^ -o $@ $(INCLUDES) $(LINKS)

clean:
		rm -f $(EXECS)
		rm -rf *.dSYM
		rm a.out
                
                




