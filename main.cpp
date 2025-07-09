#include "StudentManager.h"
#include <iostream>
#include <limits>
#include <string>

class Menu {
private:
  StudentManager manager;

  // 清除输入缓冲区
  void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // 获取整数输入
  int getIntInput(const std::string &prompt) {
    int value;
    while (true) {
      std::cout << prompt;
      if (std::cin >> value) {
        clearInputBuffer();
        return value;
      } else {
        std::cout << "输入无效，请输入一个整数！" << std::endl;
        clearInputBuffer();
      }
    }
  }

  // 获取浮点数输入
  double getDoubleInput(const std::string &prompt) {
    double value;
    while (true) {
      std::cout << prompt;
      if (std::cin >> value) {
        clearInputBuffer();
        return value;
      } else {
        std::cout << "输入无效，请输入一个数字！" << std::endl;
        clearInputBuffer();
      }
    }
  }

  // 获取字符串输入
  std::string getStringInput(const std::string &prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
  }

public:
  Menu() : manager("students.txt") {}

  // 显示主菜单
  void displayMainMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "           学生管理系统" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. 添加学生" << std::endl;
    std::cout << "2. 删除学生" << std::endl;
    std::cout << "3. 修改学生信息" << std::endl;
    std::cout << "4. 查找学生" << std::endl;
    std::cout << "5. 显示所有学生" << std::endl;
    std::cout << "6. 按专业查看学生" << std::endl;
    std::cout << "7. 按绩点查看学生" << std::endl;
    std::cout << "8. 排序功能" << std::endl;
    std::cout << "9. 搜索功能" << std::endl;
    std::cout << "10. 统计信息" << std::endl;
    std::cout << "11. 清空所有数据" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
  }

  // 添加学生
  void addStudent() {
    std::cout << "\n========== 添加学生 ==========" << std::endl;

    int id = getIntInput("请输入学号：");
    std::string name = getStringInput("请输入姓名：");
    int age = getIntInput("请输入年龄：");
    std::string gender = getStringInput("请输入性别：");
    std::string major = getStringInput("请输入专业：");
    double gpa = getDoubleInput("请输入绩点：");

    Student student(id, name, age, gender, major, gpa);
    manager.addStudent(student);
  }

  // 删除学生
  void deleteStudent() {
    std::cout << "\n========== 删除学生 ==========" << std::endl;
    int id = getIntInput("请输入要删除的学生学号：");
    manager.deleteStudent(id);
  }

  // 修改学生信息
  void updateStudent() {
    std::cout << "\n========== 修改学生信息 ==========" << std::endl;
    int id = getIntInput("请输入要修改的学生学号：");

    Student *student = manager.findStudent(id);
    if (student == nullptr) {
      std::cout << "未找到该学生！" << std::endl;
      return;
    }

    std::cout << "当前学生信息：" << std::endl;
    student->display();
    std::cout << std::endl;

    std::string name = getStringInput("请输入新姓名（直接回车保持不变）：");
    if (!name.empty())
      student->setName(name);

    std::cout << "请输入新年龄（输入-1保持不变）：";
    int age;
    std::cin >> age;
    clearInputBuffer();
    if (age != -1)
      student->setAge(age);

    std::string gender = getStringInput("请输入新性别（直接回车保持不变）：");
    if (!gender.empty())
      student->setGender(gender);

    std::string major = getStringInput("请输入新专业（直接回车保持不变）：");
    if (!major.empty())
      student->setMajor(major);

    std::cout << "请输入新绩点（输入-1保持不变）：";
    double gpa;
    std::cin >> gpa;
    clearInputBuffer();
    if (gpa != -1)
      student->setGpa(gpa);

    std::cout << "学生信息修改成功！" << std::endl;
  }

  // 查找学生
  void findStudent() {
    std::cout << "\n========== 查找学生 ==========" << std::endl;
    int id = getIntInput("请输入要查找的学生学号：");

    Student *student = manager.findStudent(id);
    if (student != nullptr) {
      std::cout << "找到学生：" << std::endl;
      student->display();
    } else {
      std::cout << "未找到该学生！" << std::endl;
    }
  }

  // 按专业查看学生
  void displayByMajor() {
    std::string major = getStringInput("请输入专业名称：");
    manager.displayStudentsByMajor(major);
  }

  // 按绩点查看学生
  void displayByGpa() {
    double minGpa = getDoubleInput("请输入最低绩点：");
    manager.displayStudentsByGpa(minGpa);
  }

  // 排序菜单
  void sortMenu() {
    std::cout << "\n========== 排序功能 ==========" << std::endl;
    std::cout << "1. 按学号排序" << std::endl;
    std::cout << "2. 按姓名排序" << std::endl;
    std::cout << "3. 按绩点排序" << std::endl;

    int choice = getIntInput("请选择排序方式：");
    switch (choice) {
    case 1:
      manager.sortById();
      break;
    case 2:
      manager.sortByName();
      break;
    case 3:
      manager.sortByGpa();
      break;
    default:
      std::cout << "无效选择！" << std::endl;
    }
  }

  // 搜索菜单
  void searchMenu() {
    std::cout << "\n========== 搜索功能 ==========" << std::endl;
    std::cout << "1. 按姓名搜索" << std::endl;
    std::cout << "2. 按专业搜索" << std::endl;

    int choice = getIntInput("请选择搜索方式：");
    switch (choice) {
    case 1: {
      std::string name = getStringInput("请输入姓名关键字：");
      auto results = manager.searchByName(name);
      if (results.empty()) {
        std::cout << "未找到匹配的学生！" << std::endl;
      } else {
        std::cout << "搜索结果：" << std::endl;
        for (const auto &student : results) {
          student.display();
        }
      }
      break;
    }
    case 2: {
      std::string major = getStringInput("请输入专业名称：");
      auto results = manager.searchByMajor(major);
      if (results.empty()) {
        std::cout << "未找到该专业的学生！" << std::endl;
      } else {
        std::cout << "搜索结果：" << std::endl;
        for (const auto &student : results) {
          student.display();
        }
      }
      break;
    }
    default:
      std::cout << "无效选择！" << std::endl;
    }
  }

  // 清空数据
  void clearAllData() {
    std::cout << "\n警告：此操作将删除所有学生数据！" << std::endl;
    std::string confirm = getStringInput("请输入 'YES' 确认删除：");
    if (confirm == "YES") {
      manager.clearAllStudents();
    } else {
      std::cout << "操作已取消。" << std::endl;
    }
  }

  // 运行主程序
  void run() {
    std::cout << "欢迎使用学生管理系统！" << std::endl;

    while (true) {
      displayMainMenu();
      int choice = getIntInput("请选择操作：");

      switch (choice) {
      case 1:
        addStudent();
        break;
      case 2:
        deleteStudent();
        break;
      case 3:
        updateStudent();
        break;
      case 4:
        findStudent();
        break;
      case 5:
        manager.displayAllStudents();
        break;
      case 6:
        displayByMajor();
        break;
      case 7:
        displayByGpa();
        break;
      case 8:
        sortMenu();
        break;
      case 9:
        searchMenu();
        break;
      case 10:
        manager.getStatistics();
        break;
      case 11:
        clearAllData();
        break;
      case 0:
        std::cout << "感谢使用学生管理系统，再见！" << std::endl;
        return;
      default:
        std::cout << "无效选择，请重新输入！" << std::endl;
      }

      std::cout << "\n按回车键继续...";
      std::cin.get();
    }
  }
};

int main() {
  Menu menu;
  menu.run();
  return 0;
}