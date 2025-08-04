# Makefile

CXX        := clang++
SDK_PATH   := $(shell xcrun --sdk macosx --show-sdk-path)
CXXFLAGS   := -std=c++17 -Wall -Wextra -pedantic \
              -isystem $(SDK_PATH)/usr/include/c++/v1 \
              -MMD -MP

SRCS       := $(wildcard *.cpp)
BUILD_DIR  := build
OBJS       := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS       := $(OBJS:.o=.d)
TARGET     := $(BUILD_DIR)/sailing_app

.PHONY: all clean

all: $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each .cpp into build/%.o, generating .d deps
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) 

clean.dat:
	rm *.dat

# Auto‐include dependency files
-include $(DEPS)
