CC := g++
CFLAGS := -O2
TARGET := client

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard ./src/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst ./src/%.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -l GL -l X11 
%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -l GL -l X11  -c $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean
