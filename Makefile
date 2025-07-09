# Makefile for Student Management System

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# 目标文件
TARGET = student_manager

# 源文件
SOURCES = main.cpp Student.cpp StudentManager.cpp

# 对象文件
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "编译完成！可执行文件：$(TARGET)"

# 编译源文件为对象文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "清理完成！"

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 安装（复制到系统路径，需要管理员权限）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	@echo "安装完成！"

# 卸载
uninstall:
	rm -f /usr/local/bin/$(TARGET)
	@echo "卸载完成！"

# 显示帮助信息
help:
	@echo "可用的make目标："
	@echo "  all      - 编译程序（默认）"
	@echo "  clean    - 清理编译文件"
	@echo "  run      - 编译并运行程序"
	@echo "  install  - 安装到系统（需要sudo）"
	@echo "  uninstall- 从系统卸载（需要sudo）"
	@echo "  help     - 显示此帮助信息"

# 声明伪目标
.PHONY: all clean run install uninstall help