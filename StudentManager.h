#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>

class StudentManager {
private:
    std::vector<Student> students;     // 存储学生信息的容器
    std::string filename;              // 数据文件名
    
    // 私有辅助方法
    bool isValidId(int id) const;      // 检查学号是否有效
    int findStudentIndex(int id) const; // 根据学号查找学生索引
    
public:
    // 构造函数和析构函数
    StudentManager(const std::string& filename = "students.txt");
    ~StudentManager();
    
    // 基本操作
    bool addStudent(const Student& student);           // 添加学生
    bool deleteStudent(int id);                        // 删除学生
    bool updateStudent(int id, const Student& newInfo); // 更新学生信息
    Student* findStudent(int id);                      // 查找学生
    
    // 显示操作
    void displayAllStudents() const;                  // 显示所有学生
    void displayStudentsByMajor(const std::string& major) const; // 按专业显示
    void displayStudentsByGpa(double minGpa) const;   // 按绩点显示
    
    // 统计操作
    int getTotalStudents() const;                     // 获取学生总数
    double getAverageGpa() const;                     // 获取平均绩点
    void getStatistics() const;                      // 显示统计信息
    
    // 排序操作
    void sortById();                                  // 按学号排序
    void sortByName();                               // 按姓名排序
    void sortByGpa();                                // 按绩点排序
    
    // 文件操作
    bool saveToFile() const;                         // 保存到文件
    bool loadFromFile();                             // 从文件加载
    
    // 搜索操作
    std::vector<Student> searchByName(const std::string& name) const; // 按姓名搜索
    std::vector<Student> searchByMajor(const std::string& major) const; // 按专业搜索
    
    // 清空数据
    void clearAllStudents();
};

#endif // STUDENTMANAGER_H