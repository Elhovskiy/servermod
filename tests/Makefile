CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.. -I/usr/include
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lUnitTest++ -lssl -lcrypto

SRC = ../VectorProcessor.cpp ../Utils.cpp ../DatabaseConnector.cpp ../ClientHandler.cpp ../Logger.cpp

TEST = test_server.cpp

TARGET = run_tests

all: $(TARGET)

$(TARGET): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

