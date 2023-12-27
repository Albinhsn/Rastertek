CC := g++
CFLAGS := -O2
TARGET := client

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard ./src/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst ./src/%.cpp,./obj/%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -l GL -l X11 
./obj/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -l GL -l X11  -c $<  && mv *.o ./obj/
clean:
	rm -rf $(TARGET) *.o
conv:
	$(CC) ./convert/convert.cpp -o ./convert_blender && ./convert_blender

.PHONY: all clean

