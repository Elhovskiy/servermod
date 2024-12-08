CXX = g++
CXXFLAGS = -Wall -std=c++17 -I.
LDFLAGS = -lssl -lcrypto

OBJS = main.o server.o client_handler.o logger.o database.o hashing.o vector_processor.o

all: server

server: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o server




