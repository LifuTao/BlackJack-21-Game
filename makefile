
# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o card.o player.o
	$(CXX) $(CXXFLAGS) -o main main.o card.o player.o

# The main.o target can be written more simply

main.o: main.cpp card.h player.h
	$(CXX) $(CXXFLAGS) -c main.cpp

card.o: card.h
player.o: player.h
