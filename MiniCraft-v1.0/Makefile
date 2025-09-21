CXX ?= clang++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2 -I.

TARGET := MiniCraft
SRCS := \
	main.cpp \
	structs/player.cpp \
	fuctions/save.cpp \
	fuctions/inventory.cpp \
	fuctions/ui.cpp \
	fuctions/game.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

