# Makefile

CXX        := clang++
SDK_PATH   := $(shell xcrun --sdk macosx --show-sdk-path)
CXXFLAGS   := -std=c++17 -Wall -Wextra -pedantic \
              -isystem $(SDK_PATH)/usr/include/c++/v1

SRCS       := $(wildcard *.cpp)
BUILD_DIR  := build
OBJS       := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
TARGET     := $(BUILD_DIR)/reservation_app

.PHONY: all clean

all: $(TARGET)

# Ensure build directory exists before compiling or linking
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the executable inside build/
$(TARGET): | $(BUILD_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each .cpp into build/%.o
# The order of prerequisites ensures build/ is created first
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
