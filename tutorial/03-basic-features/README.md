# ⚙️ 第三章：基础功能实现

在这一章中，我们将详细分析学生管理系统的基础功能实现，包括增删改查操作。

## 🎯 本章目标

- 深入理解CRUD操作的实现
- 掌握数据验证和错误处理
- 学习STL容器的实际应用
- 了解内存管理和性能优化

## 📝 Student类详解

### 构造函数设计

```cpp
// 默认构造函数
Student::Student() : id(0), name(""), age(0), gender(""), major(""), gpa(0.0) {}

// 参数构造函数
Student::Student(int id, const std::string& name, int age, const std::string& gender, 
                 const std::string& major, double gpa) 
    : id(id), name(name), age(age), gender(gender), major(major), gpa(gpa) {}
```

**设计要点**:
- 使用初始化列表提高效率
- 默认构造函数提供安全的初始值
- 参数构造函数支持直接创建完整对象

### Getter/Setter模式

```cpp
// Getter方法 - const保证不修改对象
int Student::getId() const {
    return id;
}

// Setter方法 - 可以添加验证逻辑
void Student::setId(int id) {
    this->id = id;  // 使用this指针区分参数和成员变量
}
```

**最佳实践**:
- Getter方法标记为const
- 可以在Setter中添加数据验证
- 使用引用传递避免不必要的拷贝

### 显示方法实现

```cpp
void Student::display() const {
    std::cout << "学号: " << std::setw(8) << id 
              << " | 姓名: " << std::setw(10) << name 
              << " | 年龄: " << std::setw(3) << age 
              << " | 性别: " << std::setw(4) << gender 
              << " | 专业: " << std::setw(15) << major 
              << " | 绩点: " << std::fixed << std::setprecision(2) << gpa << std::endl;
}
```

**格式化技巧**:
- `std::setw()`: 设置字段宽度
- `std::fixed`: 固定小数点格式
- `std::setprecision()`: 设置小数位数

## 🔧 CRUD操作实现

### 1. Create - 添加学生

```cpp
bool StudentManager::addStudent(const Student& student) {
    // 1. 验证学号唯一性
    if (!isValidId(student.getId())) {
        std::cout << "错误：学号 " << student.getId() << " 已存在！" << std::endl;
        return false;
    }
    
    // 2. 添加到容器
    students.push_back(student);
    std::cout << "学生添加成功！" << std::endl;
    return true;
}
```

**实现要点**:
- 先验证数据有效性
- 使用push_back添加到vector末尾
- 返回bool值表示操作结果
- 提供用户友好的反馈信息

### 2. Read - 查找学生

```cpp
Student* StudentManager::findStudent(int id) {
    int index = findStudentIndex(id);
    if (index == -1) {
        return nullptr;  // 未找到返回空指针
    }
    return &students[index];  // 返回对象地址
}

// 辅助方法：查找索引
int StudentManager::findStudentIndex(int id) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1;  // 未找到返回-1
}
```

**设计考虑**:
- 返回指针而非对象，避免拷贝开销
- 使用nullptr表示未找到
- 辅助方法提高代码复用性
- size_t到int的安全转换

### 3. Update - 更新学生

```cpp
bool StudentManager::updateStudent(int id, const Student& newInfo) {
    int index = findStudentIndex(id);
    if (index == -1) {
        std::cout << "错误：未找到学号为 " << id << " 的学生！" << std::endl;
        return false;
    }
    
    students[index] = newInfo;  // 直接赋值更新
    std::cout << "学生信息更新成功！" << std::endl;
    return true;
}
```

**实现特点**:
- 复用查找逻辑
- 整体替换对象
- 也可以实现部分字段更新

### 4. Delete - 删除学生

```cpp
bool StudentManager::deleteStudent(int id) {
    int index = findStudentIndex(id);
    if (index == -1) {
        std::cout << "错误：未找到学号为 " << id << " 的学生！" << std::endl;
        return false;
    }
    
    students.erase(students.begin() + index);  // 删除指定位置元素
    std::cout << "学生删除成功！" << std::endl;
    return true;
}
```

**注意事项**:
- erase操作的时间复杂度为O(n)
- 删除后后续元素会前移
- 考虑使用软删除（标记删除）提高性能

## 🔍 数据验证机制

### 学号唯一性检查

```cpp
bool StudentManager::isValidId(int id) const {
    return findStudentIndex(id) == -1;  // 未找到说明可用
}
```

### 输入验证示例

```cpp
// 在Menu类中的输入验证
int Menu::getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInputBuffer();  // 清除输入缓冲区
            return value;
        } else {
            std::cout << "输入无效，请输入一个整数！" << std::endl;
            clearInputBuffer();
        }
    }
}

void Menu::clearInputBuffer() {
    std::cin.clear();  // 清除错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

**验证策略**:
- 类型验证：确保输入类型正确
- 范围验证：检查数值范围
- 格式验证：验证字符串格式
- 业务验证：检查业务规则

## 📊 显示功能实现

### 显示所有学生

```cpp
void StudentManager::displayAllStudents() const {
    if (students.empty()) {
        std::cout << "暂无学生信息！" << std::endl;
        return;
    }
    
    std::cout << "\n========== 所有学生信息 ==========" << std::endl;
    std::cout << std::string(80, '-') << std::endl;  // 分隔线
    
    for (const auto& student : students) {  // 范围for循环
        student.display();
    }
    
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "总计：" << students.size() << " 名学生" << std::endl;
}
```

**实现亮点**:
- 空容器检查
- 美观的格式化输出
- 使用范围for循环
- 统计信息显示

### 条件查询实现

```cpp
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
```

## 🎯 性能优化考虑

### 1. 时间复杂度分析

| 操作 | 当前复杂度 | 优化方案 |
|------|------------|----------|
| 添加 | O(n) | 使用哈希表索引 |
| 查找 | O(n) | 使用map或unordered_map |
| 删除 | O(n) | 软删除或链表结构 |
| 显示 | O(n) | 无法优化 |

### 2. 内存优化

```cpp
// 预分配容器大小
students.reserve(1000);  // 预期最大学生数

// 使用引用避免拷贝
for (const auto& student : students) {  // 而非 for (auto student : students)
    // ...
}
```

### 3. 缓存友好的数据结构

```cpp
// 考虑使用结构体数组而非对象数组
struct StudentData {
    int id;
    char name[32];  // 固定长度字符串
    int age;
    // ...
};
```

## 🔧 实践练习

### 练习1：添加数据验证

为Student类添加更严格的数据验证：

```cpp
void Student::setAge(int age) {
    if (age < 16 || age > 100) {
        throw std::invalid_argument("年龄必须在16-100之间");
    }
    this->age = age;
}

void Student::setGpa(double gpa) {
    if (gpa < 0.0 || gpa > 4.0) {
        throw std::invalid_argument("绩点必须在0.0-4.0之间");
    }
    this->gpa = gpa;
}
```

### 练习2：实现批量操作

```cpp
// 批量添加学生
bool StudentManager::addStudents(const std::vector<Student>& newStudents) {
    // 实现批量添加逻辑
}

// 批量删除学生
bool StudentManager::deleteStudentsByMajor(const std::string& major) {
    // 实现按专业批量删除
}
```

### 练习3：实现撤销功能

```cpp
class StudentManager {
private:
    std::stack<std::vector<Student>> history;  // 操作历史
    
public:
    void saveState();     // 保存当前状态
    bool undo();          // 撤销上一步操作
};
```

## 🎯 本章小结

通过本章学习，您掌握了：
- ✅ CRUD操作的标准实现模式
- ✅ 数据验证和错误处理机制
- ✅ STL容器的高效使用
- ✅ 性能优化的基本考虑
- ✅ 代码质量和可维护性

## 🚀 下一步

现在让我们学习更高级的功能实现，包括排序、搜索和文件操作。

[👉 进入第四章：高级功能实现](../04-advanced-features/README.md)

---

💡 **小贴士**: 基础功能是系统的核心，建议您亲自实现一遍每个功能，加深理解。