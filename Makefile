CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Iinclude
LDFLAGS  ?=
LDLIBS   ?= -pthread -lcurl

TARGET   := game
BUILD    := build

# 源码：src/*.cpp
SRCS     := $(wildcard src/*.cpp)

# 把 src/foo.cpp 映射成 build/foo.o
OBJS     := $(patsubst src/%.cpp,$(BUILD)/%.o,$(SRCS))
DEPS     := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

# 最终可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# 每个 .cpp → build/xxx.o
$(BUILD)/%.o: src/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# 自动建 build 目录
$(BUILD):
	mkdir -p $(BUILD)

run: all
	./$(TARGET)

clean:
	$(RM) -rf $(BUILD) $(TARGET)

-include $(DEPS)