# Makefile for a simple C++ project

# 指定使用 g++ 作为 C++ 编译器。
CXX = g++

# -Wall 打开所有警告，-std=c++17 指定使用 C++17 标准
CXXFLAGS = -Wall -std=c++2a

# 定义源文件列表
# SRCS = main.cpp foo.cpp bar.cpp
# SRCS = $(wildcard src/*.cpp)
SRCS = $(shell find src/ -name '*.cpp')
# 目标文件列表  模式替换，将 .cpp 替换为 .o
OBJS = $(SRCS:.cpp=.o)

# 最终执行程序
TARGET = my_program

# all 是一个伪目标 后面定义的是它的依赖项
all: $(TARGET)

# 生成可执行文件的规则
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets to avoid conflicts with files named 'all', 'clean', or 'run'
.PHONY: all clean run