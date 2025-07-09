#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

class Student {
private:
    int id;                    // 学号
    std::string name;          // 姓名
    int age;                   // 年龄
    std::string gender;        // 性别
    std::string major;         // 专业
    double gpa;                // 绩点

public:
    // 构造函数
    Student();
    Student(int id, const std::string& name, int age, const std::string& gender, 
            const std::string& major, double gpa);
    
    // 析构函数
    ~Student();
    
    // Getter方法
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getMajor() const;
    double getGpa() const;
    
    // Setter方法
    void setId(int id);
    void setName(const std::string& name);
    void setAge(int age);
    void setGender(const std::string& gender);
    void setMajor(const std::string& major);
    void setGpa(double gpa);
    
    // 显示学生信息
    void display() const;
    
    // 重载运算符
    bool operator==(const Student& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

#endif // STUDENT_H