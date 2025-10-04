# Makefile para pregunta1.cpp

CXX = g++
CXXFLAGS = -Wall -O2
TARGET = pregunta1
SRC = pregunta1.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)