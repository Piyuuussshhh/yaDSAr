CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I
TARGET = dsa.exe

SOURCES = misc\main.cpp
HEADERS = include\dsa.hpp Data_Structures\Trees\include\treenode.hpp Data_Structures\Trees\"Binary Trees"\Structure\binary_tree.hpp Data_Structures\Trees\"Binary Search Trees"\Structure\bst.hpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -c $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	# rm -f $(TARGET) $(OBJECTS)
	rm -f $(OBJECTS)