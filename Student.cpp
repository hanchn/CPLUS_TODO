#include "Student.h"
#include <iomanip>

// 默认构造函数
Student::Student() : id(0), name(""), age(0), gender(""), major(""), gpa(0.0) {}

// 带参数的构造函数
Student::Student(int id, const std::string& name, int age, const std::string& gender, 
                 const std::string& major, double gpa) 
    : id(id), name(name), age(age), gender(gender), major(major), gpa(gpa) {}

// 析构函数
Student::~Student() {}

// Getter方法
int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

std::string Student::getGender() const {
    return gender;
}

std::string Student::getMajor() const {
    return major;
}

double Student::getGpa() const {
    return gpa;
}

// Setter方法
void Student::setId(int id) {
    this->id = id;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setAge(int age) {
    this->age = age;
}

void Student::setGender(const std::string& gender) {
    this->gender = gender;
}

void Student::setMajor(const std::string& major) {
    this->major = major;
}

void Student::setGpa(double gpa) {
    this->gpa = gpa;
}

// 显示学生信息
void Student::display() const {
    std::cout << "学号: " << std::setw(8) << id 
              << " | 姓名: " << std::setw(10) << name 
              << " | 年龄: " << std::setw(3) << age 
              << " | 性别: " << std::setw(4) << gender 
              << " | 专业: " << std::setw(15) << major 
              << " | 绩点: " << std::fixed << std::setprecision(2) << gpa << std::endl;
}

// 重载==运算符
bool Student::operator==(const Student& other) const {
    return this->id == other.id;
}

// 重载<<运算符
std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "学号: " << student.id 
       << ", 姓名: " << student.name 
       << ", 年龄: " << student.age 
       << ", 性别: " << student.gender 
       << ", 专业: " << student.major 
       << ", 绩点: " << std::fixed << std::setprecision(2) << student.gpa;
    return os;
}