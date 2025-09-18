LOCALLIB = -I./lib -I ./bin
LIB = -lglfw -lGL
RESULT = -o iron_source
TARGET = ./bin/src/main.cpp ./bin/src/core/Application.cpp ./bin/src/core/Initializer.cpp ./bin/src/graphics/Polygon.cpp
all: 
	g++ $(TARGET) $(LOCALLIB) $(LIB) $(RESULT) && ./iron_source
