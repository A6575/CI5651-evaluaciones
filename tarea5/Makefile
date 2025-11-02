# Makefile para pregunta2.cpp y pregunta3.cpp
CXX = g++
CXXFLAGS = -Wall -O2

.PHONY: p2 p4 run clean

p2: pregunta2.cpp
	$(CXX) $(CXXFLAGS) -o pregunta2 pregunta2.cpp

p4: pregunta4.cpp
	$(CXX) $(CXXFLAGS) -o pregunta4 pregunta4.cpp

run-p2: p2
	./pregunta2

run-p4: p4
	./pregunta4

clean-p2:
	rm -f pregunta2

clean-p4:
	rm -f pregunta4