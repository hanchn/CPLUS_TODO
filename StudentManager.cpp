#include "StudentManager.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>

// 构造函数
StudentManager::StudentManager(const std::string& filename) : filename(filename) {
    loadFromFile();
}

// 析构函数
StudentManager::~StudentManager() {
    saveToFile();
}

// 检查学号是否有效（不重复）
bool StudentManager::isValidId(int id) const {
    return findStudentIndex(id) == -1;
}

// 根据学号查找学生索引
int StudentManager::findStudentIndex(int id) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// 添加学生
bool StudentManager::addStudent(const Student& student) {
    if (!isValidId(student.getId())) {
        std::cout << "错误：学号 " << student.getId() << " 已存在！" << std::endl;
        return false;
    }
    
    students.push_back(student);
    std::cout << "学生添加成功！" << std::endl;
    return true;
}

// 删除学生
bool StudentManager::deleteStudent(int id) {
    int index = findStudentIndex(id);
    if (index == -1) {
        std::cout << "错误：未找到学号为 " << id << " 的学生！" << std::endl;
        return false;
    }
    
    students.erase(students.begin() + index);
    std::cout << "学生删除成功！" << std::endl;
    return true;
}

// 更新学生信息
bool StudentManager::updateStudent(int id, const Student& newInfo) {
    int index = findStudentIndex(id);
    if (index == -1) {
        std::cout << "错误：未找到学号为 " << id << " 的学生！" << std::endl;
        return false;
    }
    
    students[index] = newInfo;
    std::cout << "学生信息更新成功！" << std::endl;
    return true;
}

// 查找学生
Student* StudentManager::findStudent(int id) {
    int index = findStudentIndex(id);
    if (index == -1) {
        return nullptr;
    }
    return &students[index];
}

// 显示所有学生
void StudentManager::displayAllStudents() const {
    if (students.empty()) {
        std::cout << "暂无学生信息！" << std::endl;
        return;
    }
    
    std::cout << "\n========== 所有学生信息 ==========" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    for (const auto& student : students) {
        student.display();
    }
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "总计：" << students.size() << " 名学生" << std::endl;
}

// 按专业显示学生
void StudentManager::displayStudentsByMajor(const std::string& major) const {
    std::cout << "\n========== 专业：" << major << " ==========" << std::endl;
    bool found = false;
    for (const auto& student : students) {
        if (student.getMajor() == major) {
            student.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "未找到该专业的学生！" << std::endl;
    }
}

// 按绩点显示学生
void StudentManager::displayStudentsByGpa(double minGpa) const {
    std::cout << "\n========== 绩点 >= " << minGpa << " 的学生 ==========" << std::endl;
    bool found = false;
    for (const auto& student : students) {
        if (student.getGpa() >= minGpa) {
            student.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "未找到符合条件的学生！" << std::endl;
    }
}

// 获取学生总数
int StudentManager::getTotalStudents() const {
    return static_cast<int>(students.size());
}

// 获取平均绩点
double StudentManager::getAverageGpa() const {
    if (students.empty()) {
        return 0.0;
    }
    
    double total = 0.0;
    for (const auto& student : students) {
        total += student.getGpa();
    }
    return total / students.size();
}

// 显示统计信息
void StudentManager::getStatistics() const {
    std::cout << "\n========== 统计信息 ==========" << std::endl;
    std::cout << "学生总数：" << getTotalStudents() << std::endl;
    std::cout << "平均绩点：" << std::fixed << std::setprecision(2) << getAverageGpa() << std::endl;
    
    if (!students.empty()) {
        auto maxGpa = std::max_element(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getGpa() < b.getGpa();
            });
        auto minGpa = std::min_element(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getGpa() < b.getGpa();
            });
        
        std::cout << "最高绩点：" << maxGpa->getGpa() << " (" << maxGpa->getName() << ")" << std::endl;
        std::cout << "最低绩点：" << minGpa->getGpa() << " (" << minGpa->getName() << ")" << std::endl;
    }
}

// 按学号排序
void StudentManager::sortById() {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getId() < b.getId();
        });
    std::cout << "已按学号排序！" << std::endl;
}

// 按姓名排序
void StudentManager::sortByName() {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getName() < b.getName();
        });
    std::cout << "已按姓名排序！" << std::endl;
}

// 按绩点排序
void StudentManager::sortByGpa() {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getGpa() > b.getGpa();
        });
    std::cout << "已按绩点排序（从高到低）！" << std::endl;
}

// 保存到文件
bool StudentManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "错误：无法打开文件 " << filename << " 进行写入！" << std::endl;
        return false;
    }
    
    for (const auto& student : students) {
        file << student.getId() << "," 
             << student.getName() << "," 
             << student.getAge() << "," 
             << student.getGender() << "," 
             << student.getMajor() << "," 
             << student.getGpa() << std::endl;
    }
    
    file.close();
    return true;
}

// 从文件加载
bool StudentManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // 文件不存在是正常的，创建新文件
        return true;
    }
    
    students.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }
        
        if (tokens.size() == 6) {
            try {
                int id = std::stoi(tokens[0]);
                std::string name = tokens[1];
                int age = std::stoi(tokens[2]);
                std::string gender = tokens[3];
                std::string major = tokens[4];
                double gpa = std::stod(tokens[5]);
                
                students.emplace_back(id, name, age, gender, major, gpa);
            } catch (const std::exception& e) {
                std::cout << "警告：读取文件时跳过无效行：" << line << std::endl;
            }
        }
    }
    
    file.close();
    return true;
}

// 按姓名搜索
std::vector<Student> StudentManager::searchByName(const std::string& name) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (student.getName().find(name) != std::string::npos) {
            result.push_back(student);
        }
    }
    return result;
}

// 按专业搜索
std::vector<Student> StudentManager::searchByMajor(const std::string& major) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (student.getMajor() == major) {
            result.push_back(student);
        }
    }
    return result;
}

// 清空所有学生数据
void StudentManager::clearAllStudents() {
    students.clear();
    std::cout << "所有学生数据已清空！" << std::endl;
}