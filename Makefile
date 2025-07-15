# Makefile

CXX       := clang++
SDK_PATH := $(shell xcrun --sdk macosx --show-sdk-path)
CXXFLAGS  := -std=c++17 -Wall -Wextra -pedantic \
            -isystem $(SDK_PATH)/usr/include/c++/v1
SRCS      := $(wildcard *.cpp)
OBJS      := $(SRCS:.cpp=.o)
TARGET    := sailing_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
