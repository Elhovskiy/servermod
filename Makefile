CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src
LDFLAGS = -lssl -lcrypto

SRC = main.cpp ClientHandler.cpp VectorProcessor.cpp Logger.cpp Utils.cpp DatabaseConnector.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

