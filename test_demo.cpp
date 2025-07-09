#include "StudentManager.h"
#include <iostream>

int main() {
    std::cout << "========== 学生管理系统功能演示 ==========" << std::endl;
    
    // 创建学生管理器
    StudentManager manager("demo_students.txt");
    
    std::cout << "\n1. 添加示例学生数据..." << std::endl;
    
    // 添加示例学生
    Student s1(20210001, "张三", 20, "男", "计算机科学", 3.8);
    Student s2(20210002, "李四", 19, "女", "软件工程", 3.9);
    Student s3(20210003, "王五", 21, "男", "计算机科学", 3.6);
    Student s4(20210004, "赵六", 20, "女", "数据科学", 3.7);
    Student s5(20210005, "钱七", 22, "男", "软件工程", 3.5);
    
    manager.addStudent(s1);
    manager.addStudent(s2);
    manager.addStudent(s3);
    manager.addStudent(s4);
    manager.addStudent(s5);
    
    std::cout << "\n2. 显示所有学生信息：" << std::endl;
    manager.displayAllStudents();
    
    std::cout << "\n3. 查找学号为20210002的学生：" << std::endl;
    Student* found = manager.findStudent(20210002);
    if (found) {
        found->display();
    }
    
    std::cout << "\n4. 按专业查看（计算机科学）：" << std::endl;
    manager.displayStudentsByMajor("计算机科学");
    
    std::cout << "\n5. 按绩点查看（>= 3.7）：" << std::endl;
    manager.displayStudentsByGpa(3.7);
    
    std::cout << "\n6. 按绩点排序：" << std::endl;
    manager.sortByGpa();
    manager.displayAllStudents();
    
    std::cout << "\n7. 按姓名搜索（包含'张'）：" << std::endl;
    auto results = manager.searchByName("张");
    for (const auto& student : results) {
        student.display();
    }
    
    std::cout << "\n8. 统计信息：" << std::endl;
    manager.getStatistics();
    
    std::cout << "\n9. 修改学生信息（修改张三的绩点为3.95）：" << std::endl;
    Student* student = manager.findStudent(20210001);
    if (student) {
        student->setGpa(3.95);
        std::cout << "修改后的信息：" << std::endl;
        student->display();
    }
    
    std::cout << "\n10. 删除学生（删除学号20210005）：" << std::endl;
    manager.deleteStudent(20210005);
    manager.displayAllStudents();
    
    std::cout << "\n========== 演示完成 ==========" << std::endl;
    std::cout << "数据已保存到 demo_students.txt 文件中。" << std::endl;
    
    return 0;
}