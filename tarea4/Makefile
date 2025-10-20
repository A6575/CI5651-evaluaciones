# Makefile para pregunta2.cpp y pregunta3.cpp
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

.PHONY: p2 p4 p3 run clean

p2: pregunta2.cpp
	$(CXX) $(CXXFLAGS) -o pregunta2 pregunta2.cpp

p3: pregunta3.cpp
	$(CXX) $(CXXFLAGS) -o pregunta3 pregunta3.cpp

p4: pregunta4.cpp
	$(CXX) $(CXXFLAGS) -o pregunta4 pregunta4.cpp

run-p2: p2
	./pregunta2

run-p3: p3
	./pregunta3 $(arg)

run-p4: p4
	./pregunta4

clean-p2:
	rm -f pregunta2

clean-p3:
	rm -f pregunta3

clean-p4:
	rm -f pregunta4