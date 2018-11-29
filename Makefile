CC := g++
CFLAGS := -O3 -g3 -w -Wall -fPIC -std=c++11
TARGET := cmpt379Complier

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET) clean run
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o

run:
	./$(TARGET) csvFiles/ > test.s