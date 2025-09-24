CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -I./lib -I./bin

LDFLAGS  := -lglfw -lGL -lGLEW

RESULT   := iron_source

SRC_DIR  := ./bin/src
SRCS     := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS     := $(SRCS:.cpp=.o)

all: $(RESULT)

$(RESULT): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS += -g
debug: clean $(RESULT)

clean:
	rm -f $(OBJS) $(RESULT)

.PHONY: all debug clean
