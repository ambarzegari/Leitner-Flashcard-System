CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

SOURCES = main.cpp Flashcard.cpp Leitner.cpp Box.cpp Day.cpp
HEADERS = Flashcard.hpp Leitner.hpp Box.hpp Day.hpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = LeitnerBox

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
