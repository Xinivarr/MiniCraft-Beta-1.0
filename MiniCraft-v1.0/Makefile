CXX ?= clang++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2 -I.

TARGET := MiniCraft

# Sources
SRCS := \
	main.cpp \
	structs/player.cpp \
	fuctions/save.cpp \
	fuctions/inventory.cpp \
	fuctions/ui.cpp \
	fuctions/game.cpp \
	fuctions/actions/mine.cpp \
	fuctions/actions/arena.cpp

# Single output directory for object files (keeps subdirs under it)
OBJDIR := build/obj
# Mirror source tree under OBJDIR so no files go next to sources
OBJS := $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Compile objects into $(OBJDIR)/... and create subdirs on demand
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJDIR)
	find . -name '*.o' -type f -delete

run: $(TARGET)
	./$(TARGET)
