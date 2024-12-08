CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.. -I/usr/include
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lUnitTest++ -lssl -lcrypto

SRC = ../vector_processor.cpp ../server.cpp ../database.cpp ../client_handler.cpp ../logger.cpp ../hashing.cpp
TEST = tests.cpp

TARGET = run_tests

all: $(TARGET)

$(TARGET): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
