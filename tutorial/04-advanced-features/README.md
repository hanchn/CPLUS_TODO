# 🚀 第四章：高级功能实现

在这一章中，我们将深入学习学生管理系统的高级功能，包括排序、搜索、统计和文件操作。

## 🎯 本章目标

- 掌握STL算法库的使用
- 理解Lambda表达式的应用
- 学习文件I/O和数据持久化
- 了解统计算法的实现
- 掌握搜索算法的优化

## 🔄 排序功能实现

### Lambda表达式在排序中的应用

```cpp
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

// 按绩点排序（降序）
void StudentManager::sortByGpa() {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getGpa() > b.getGpa();  // 注意：> 表示降序
        });
    std::cout << "已按绩点排序（从高到低）！" << std::endl;
}
```

**Lambda表达式解析**:
```cpp
[capture](parameters) -> return_type { body }
```
- `[]`: 捕获列表（这里为空，不捕获外部变量）
- `(const Student& a, const Student& b)`: 参数列表
- `{ return a.getId() < b.getId(); }`: 函数体

### 多级排序实现

```cpp
// 先按专业排序，再按绩点排序
void StudentManager::sortByMajorAndGpa() {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            if (a.getMajor() != b.getMajor()) {
                return a.getMajor() < b.getMajor();
            }
            return a.getGpa() > b.getGpa();  // 同专业按绩点降序
        });
}
```

### 稳定排序的使用

```cpp
// 使用stable_sort保持相等元素的相对顺序
void StudentManager::stableSortByGpa() {
    std::stable_sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getGpa() > b.getGpa();
        });
}
```

## 🔍 搜索功能实现

### 线性搜索

```cpp
// 按姓名搜索（支持部分匹配）
std::vector<Student> StudentManager::searchByName(const std::string& name) const {
    std::vector<Student> result;
    
    for (const auto& student : students) {
        if (student.getName().find(name) != std::string::npos) {
            result.push_back(student);
        }
    }
    
    return result;
}

// 按专业搜索（精确匹配）
std::vector<Student> StudentManager::searchByMajor(const std::string& major) const {
    std::vector<Student> result;
    
    for (const auto& student : students) {
        if (student.getMajor() == major) {
            result.push_back(student);
        }
    }
    
    return result;
}
```

### 使用STL算法优化搜索

```cpp
// 使用std::copy_if进行条件拷贝
std::vector<Student> StudentManager::searchByGpaRange(double minGpa, double maxGpa) const {
    std::vector<Student> result;
    
    std::copy_if(students.begin(), students.end(), std::back_inserter(result),
        [minGpa, maxGpa](const Student& s) {
            return s.getGpa() >= minGpa && s.getGpa() <= maxGpa;
        });
    
    return result;
}

// 使用std::find_if查找第一个匹配项
Student* StudentManager::findFirstByMajor(const std::string& major) {
    auto it = std::find_if(students.begin(), students.end(),
        [&major](const Student& s) {
            return s.getMajor() == major;
        });
    
    return (it != students.end()) ? &(*it) : nullptr;
}
```

### 二分搜索优化

```cpp
// 在已排序的容器中使用二分搜索
Student* StudentManager::binarySearchById(int id) {
    // 确保容器已按ID排序
    auto it = std::lower_bound(students.begin(), students.end(), id,
        [](const Student& s, int targetId) {
            return s.getId() < targetId;
        });
    
    if (it != students.end() && it->getId() == id) {
        return &(*it);
    }
    
    return nullptr;
}
```

## 📊 统计功能实现

### 基础统计

```cpp
// 获取学生总数
int StudentManager::getTotalStudents() const {
    return static_cast<int>(students.size());
}

// 计算平均绩点
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
```

### 使用STL算法进行统计

```cpp
// 使用std::accumulate计算总和
double StudentManager::getTotalGpa() const {
    return std::accumulate(students.begin(), students.end(), 0.0,
        [](double sum, const Student& s) {
            return sum + s.getGpa();
        });
}

// 使用std::minmax_element查找最值
std::pair<Student*, Student*> StudentManager::getGpaRange() const {
    if (students.empty()) {
        return {nullptr, nullptr};
    }
    
    auto result = std::minmax_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.getGpa() < b.getGpa();
        });
    
    return {const_cast<Student*>(&(*result.first)), 
            const_cast<Student*>(&(*result.second))};
}

// 统计各专业人数
std::map<std::string, int> StudentManager::getMajorStatistics() const {
    std::map<std::string, int> stats;
    
    for (const auto& student : students) {
        stats[student.getMajor()]++;
    }
    
    return stats;
}
```

### 高级统计功能

```cpp
// 计算绩点标准差
double StudentManager::getGpaStandardDeviation() const {
    if (students.size() < 2) {
        return 0.0;
    }
    
    double mean = getAverageGpa();
    double variance = 0.0;
    
    for (const auto& student : students) {
        double diff = student.getGpa() - mean;
        variance += diff * diff;
    }
    
    variance /= (students.size() - 1);  // 样本标准差
    return std::sqrt(variance);
}

// 绩点分布统计
std::map<std::string, int> StudentManager::getGpaDistribution() const {
    std::map<std::string, int> distribution;
    
    for (const auto& student : students) {
        double gpa = student.getGpa();
        std::string range;
        
        if (gpa >= 3.7) range = "优秀(3.7-4.0)";
        else if (gpa >= 3.0) range = "良好(3.0-3.7)";
        else if (gpa >= 2.0) range = "及格(2.0-3.0)";
        else range = "不及格(<2.0)";
        
        distribution[range]++;
    }
    
    return distribution;
}
```

## 💾 文件操作实现

### CSV格式的数据保存

```cpp
bool StudentManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "错误：无法打开文件 " << filename << " 进行写入！" << std::endl;
        return false;
    }
    
    // 写入CSV格式数据
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
```

### 数据加载和解析

```cpp
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
        
        // 解析CSV行
        std::vector<std::string> tokens = parseCSVLine(line);
        
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

// CSV行解析辅助函数
std::vector<std::string> StudentManager::parseCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string item;
    
    while (std::getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    
    return tokens;
}
```

### 数据备份和恢复

```cpp
// 创建数据备份
bool StudentManager::createBackup() const {
    std::string backupFilename = filename + ".backup." + getCurrentTimestamp();
    
    std::ifstream src(filename, std::ios::binary);
    std::ofstream dst(backupFilename, std::ios::binary);
    
    if (!src.is_open() || !dst.is_open()) {
        return false;
    }
    
    dst << src.rdbuf();  // 复制文件内容
    
    std::cout << "备份已创建：" << backupFilename << std::endl;
    return true;
}

// 获取当前时间戳
std::string StudentManager::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S");
    return ss.str();
}
```

## 🔧 性能优化技巧

### 1. 预分配容器大小

```cpp
// 在构造函数中预分配
StudentManager::StudentManager(const std::string& filename) : filename(filename) {
    students.reserve(1000);  // 预期最大学生数
    loadFromFile();
}
```

### 2. 使用移动语义

```cpp
// 使用emplace_back避免拷贝
students.emplace_back(id, name, age, gender, major, gpa);

// 使用移动构造
students.push_back(std::move(student));
```

### 3. 缓存计算结果

```cpp
class StudentManager {
private:
    mutable double cachedAverageGpa = -1.0;  // 缓存平均绩点
    mutable bool cacheValid = false;
    
public:
    double getAverageGpa() const {
        if (!cacheValid) {
            cachedAverageGpa = calculateAverageGpa();
            cacheValid = true;
        }
        return cachedAverageGpa;
    }
    
    void invalidateCache() {
        cacheValid = false;
    }
};
```

## 🎯 实践练习

### 练习1：实现模糊搜索

```cpp
// 实现不区分大小写的模糊搜索
std::vector<Student> StudentManager::fuzzySearchByName(const std::string& pattern) const {
    std::vector<Student> result;
    std::string lowerPattern = toLower(pattern);
    
    for (const auto& student : students) {
        std::string lowerName = toLower(student.getName());
        if (lowerName.find(lowerPattern) != std::string::npos) {
            result.push_back(student);
        }
    }
    
    return result;
}
```

### 练习2：实现数据导出功能

```cpp
// 导出为JSON格式
bool StudentManager::exportToJSON(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "{\n  \"students\": [\n";
    
    for (size_t i = 0; i < students.size(); ++i) {
        const auto& s = students[i];
        file << "    {\n"
             << "      \"id\": " << s.getId() << ",\n"
             << "      \"name\": \"" << s.getName() << "\",\n"
             << "      \"age\": " << s.getAge() << ",\n"
             << "      \"gender\": \"" << s.getGender() << "\",\n"
             << "      \"major\": \"" << s.getMajor() << "\",\n"
             << "      \"gpa\": " << s.getGpa() << "\n"
             << "    }";
        
        if (i < students.size() - 1) file << ",";
        file << "\n";
    }
    
    file << "  ]\n}";
    file.close();
    return true;
}
```

### 练习3：实现数据分页

```cpp
// 分页显示学生信息
void StudentManager::displayStudentsWithPagination(int pageSize, int pageNumber) const {
    int totalPages = (students.size() + pageSize - 1) / pageSize;
    int startIndex = (pageNumber - 1) * pageSize;
    int endIndex = std::min(startIndex + pageSize, static_cast<int>(students.size()));
    
    std::cout << "第 " << pageNumber << " 页，共 " << totalPages << " 页\n";
    std::cout << std::string(80, '-') << std::endl;
    
    for (int i = startIndex; i < endIndex; ++i) {
        students[i].display();
    }
    
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "显示 " << (endIndex - startIndex) << " 条记录，共 " << students.size() << " 条\n";
}
```

## 🎯 本章小结

通过本章学习，您掌握了：
- ✅ STL算法库的高效使用
- ✅ Lambda表达式在实际项目中的应用
- ✅ 文件I/O和数据持久化的最佳实践
- ✅ 统计算法的实现技巧
- ✅ 性能优化的实用方法

## 🚀 下一步

现在让我们通过练习和挑战来巩固所学知识。

[👉 进入第五章：练习和挑战](../05-exercises/README.md)

---

💡 **小贴士**: 高级功能是系统的亮点，建议您深入理解每个算法的原理和适用场景。