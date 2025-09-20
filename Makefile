LOCALLIB = -I./lib -I ./bin
LIB = -lglfw -lGL
RESULT = -o iron_source

TARGET = $(shell find ./bin/src -name '*.cpp')

all:
	g++ $(TARGET) $(LOCALLIB) $(LIB) $(RESULT) && ./iron_source

debug: 
	g++ $(TARGET) $(LOCALLIB) $(LIB) -g $(RESULT) 