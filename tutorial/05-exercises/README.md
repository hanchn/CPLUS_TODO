# 💪 第五章：练习和挑战

在这一章中，我们将通过一系列练习和挑战来巩固和扩展您对学生管理系统的理解。

## 🎯 本章目标

- 通过实践加深对代码的理解
- 学会独立解决编程问题
- 掌握代码调试和优化技巧
- 培养软件设计思维

## 📚 基础练习

### 练习1：数据验证增强

**任务**: 为Student类添加更严格的数据验证

**要求**:
1. 学号必须是8位数字
2. 姓名不能为空且长度在2-20字符之间
3. 年龄必须在16-100之间
4. 性别只能是"男"或"女"
5. 专业名称不能为空
6. 绩点必须在0.0-4.0之间

**实现提示**:
```cpp
class Student {
public:
    // 添加验证方法
    static bool isValidId(int id);
    static bool isValidName(const std::string& name);
    static bool isValidAge(int age);
    static bool isValidGender(const std::string& gender);
    static bool isValidMajor(const std::string& major);
    static bool isValidGpa(double gpa);
    
    // 在setter中调用验证
    void setId(int id) {
        if (!isValidId(id)) {
            throw std::invalid_argument("无效的学号");
        }
        this->id = id;
    }
};
```

**测试代码**:
```cpp
void testValidation() {
    try {
        Student s;
        s.setId(12345);  // 应该抛出异常
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }
}
```

### 练习2：批量操作功能

**任务**: 实现批量导入和导出功能

**要求**:
1. 从CSV文件批量导入学生数据
2. 支持数据格式验证和错误报告
3. 实现批量删除功能（按专业、年级等）
4. 添加操作确认机制

**实现框架**:
```cpp
class StudentManager {
public:
    struct ImportResult {
        int successCount;
        int failureCount;
        std::vector<std::string> errors;
    };
    
    ImportResult importFromCSV(const std::string& filename);
    bool exportToCSV(const std::string& filename) const;
    int batchDeleteByMajor(const std::string& major, bool confirm = true);
    int batchDeleteByGpaRange(double minGpa, double maxGpa, bool confirm = true);
};
```

### 练习3：搜索功能扩展

**任务**: 实现高级搜索功能

**要求**:
1. 支持多条件组合搜索
2. 实现正则表达式搜索
3. 添加搜索历史记录
4. 支持搜索结果排序

**实现示例**:
```cpp
struct SearchCriteria {
    std::optional<int> minAge, maxAge;
    std::optional<double> minGpa, maxGpa;
    std::optional<std::string> major;
    std::optional<std::string> namePattern;
    std::optional<std::string> gender;
};

class StudentManager {
public:
    std::vector<Student> advancedSearch(const SearchCriteria& criteria) const;
    std::vector<Student> regexSearch(const std::string& field, const std::string& pattern) const;
    void saveSearchHistory(const SearchCriteria& criteria);
    std::vector<SearchCriteria> getSearchHistory() const;
};
```

## 🚀 中级挑战

### 挑战1：实现撤销/重做功能

**任务**: 为系统添加撤销和重做功能

**要求**:
1. 支持撤销最近的10个操作
2. 实现重做功能
3. 显示操作历史
4. 支持批量撤销

**设计思路**:
```cpp
enum class OperationType {
    ADD_STUDENT,
    DELETE_STUDENT,
    UPDATE_STUDENT,
    BATCH_DELETE
};

struct Operation {
    OperationType type;
    std::vector<Student> beforeState;
    std::vector<Student> afterState;
    std::string description;
    std::chrono::system_clock::time_point timestamp;
};

class UndoRedoManager {
private:
    std::stack<Operation> undoStack;
    std::stack<Operation> redoStack;
    static const size_t MAX_HISTORY = 10;
    
public:
    void recordOperation(const Operation& op);
    bool undo(std::vector<Student>& students);
    bool redo(std::vector<Student>& students);
    void clearHistory();
    std::vector<std::string> getOperationHistory() const;
};
```

### 挑战2：数据分析模块

**任务**: 实现数据分析和可视化功能

**要求**:
1. 生成各种统计报告
2. 创建ASCII图表显示数据分布
3. 实现趋势分析（如果有时间数据）
4. 导出分析报告

**实现示例**:
```cpp
class DataAnalyzer {
public:
    struct Statistics {
        double mean, median, mode;
        double standardDeviation;
        double min, max;
        std::map<std::string, int> distribution;
    };
    
    Statistics analyzeGpa(const std::vector<Student>& students);
    Statistics analyzeAge(const std::vector<Student>& students);
    void generateReport(const std::vector<Student>& students, const std::string& filename);
    void displayGpaHistogram(const std::vector<Student>& students);
    void displayMajorDistribution(const std::vector<Student>& students);
};

// ASCII柱状图示例
void DataAnalyzer::displayGpaHistogram(const std::vector<Student>& students) {
    std::map<std::string, int> ranges;
    // 统计各绩点范围的人数
    for (const auto& s : students) {
        double gpa = s.getGpa();
        if (gpa >= 3.7) ranges["3.7-4.0"]++;
        else if (gpa >= 3.0) ranges["3.0-3.7"]++;
        else if (gpa >= 2.0) ranges["2.0-3.0"]++;
        else ranges["0.0-2.0"]++;
    }
    
    // 绘制ASCII柱状图
    std::cout << "\n绩点分布图:\n";
    for (const auto& [range, count] : ranges) {
        std::cout << range << " |";
        for (int i = 0; i < count; ++i) {
            std::cout << "█";
        }
        std::cout << " (" << count << ")\n";
    }
}
```

### 挑战3：多用户支持

**任务**: 实现简单的用户权限管理

**要求**:
1. 支持管理员和普通用户角色
2. 不同角色有不同的操作权限
3. 实现简单的登录验证
4. 记录用户操作日志

**设计框架**:
```cpp
enum class UserRole {
    ADMIN,
    TEACHER,
    STUDENT
};

class User {
private:
    std::string username;
    std::string passwordHash;
    UserRole role;
    
public:
    User(const std::string& username, const std::string& password, UserRole role);
    bool authenticate(const std::string& password) const;
    UserRole getRole() const { return role; }
    std::string getUsername() const { return username; }
};

class UserManager {
private:
    std::vector<User> users;
    User* currentUser = nullptr;
    
public:
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool hasPermission(const std::string& operation) const;
    void logOperation(const std::string& operation);
};
```

## 🔥 高级挑战

### 挑战4：数据库集成

**任务**: 将文件存储替换为SQLite数据库

**要求**:
1. 设计合适的数据库表结构
2. 实现数据库连接和操作
3. 支持事务处理
4. 实现数据迁移功能

**表结构设计**:
```sql
CREATE TABLE students (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    age INTEGER NOT NULL,
    gender TEXT NOT NULL,
    major TEXT NOT NULL,
    gpa REAL NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE operations_log (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id TEXT,
    operation TEXT,
    details TEXT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

### 挑战5：网络功能

**任务**: 实现简单的客户端-服务器架构

**要求**:
1. 创建TCP服务器处理客户端请求
2. 实现简单的协议进行数据交换
3. 支持多客户端并发访问
4. 实现数据同步机制

**协议设计示例**:
```cpp
enum class MessageType {
    ADD_STUDENT = 1,
    DELETE_STUDENT = 2,
    UPDATE_STUDENT = 3,
    QUERY_STUDENT = 4,
    LIST_ALL = 5
};

struct Message {
    MessageType type;
    uint32_t length;
    std::string data;  // JSON格式的数据
};

class StudentServer {
private:
    int serverSocket;
    StudentManager manager;
    std::vector<std::thread> clientThreads;
    
public:
    bool start(int port);
    void handleClient(int clientSocket);
    void processMessage(const Message& msg, int clientSocket);
};
```

### 挑战6：图形界面

**任务**: 使用Qt或其他GUI框架创建图形界面

**要求**:
1. 设计直观的用户界面
2. 实现表格显示和编辑功能
3. 添加图表显示统计信息
4. 支持拖拽操作

## 🧪 测试练习

### 单元测试编写

**任务**: 为核心功能编写单元测试

```cpp
#include <cassert>

void testStudentCreation() {
    Student s(20210001, "张三", 20, "男", "计算机科学", 3.8);
    assert(s.getId() == 20210001);
    assert(s.getName() == "张三");
    assert(s.getAge() == 20);
    std::cout << "✅ Student creation test passed\n";
}

void testStudentManagerAdd() {
    StudentManager manager("test.txt");
    Student s(20210001, "张三", 20, "男", "计算机科学", 3.8);
    
    assert(manager.addStudent(s) == true);
    assert(manager.getTotalStudents() == 1);
    assert(manager.addStudent(s) == false);  // 重复添加应该失败
    
    std::cout << "✅ StudentManager add test passed\n";
}

void runAllTests() {
    testStudentCreation();
    testStudentManagerAdd();
    // 添加更多测试...
    std::cout << "🎉 All tests passed!\n";
}
```

### 性能测试

**任务**: 测试系统在大数据量下的性能

```cpp
#include <chrono>

void performanceTest() {
    StudentManager manager("perf_test.txt");
    
    // 测试添加性能
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; ++i) {
        Student s(20210000 + i, "Student" + std::to_string(i), 
                 20, "男", "计算机科学", 3.0 + (i % 100) / 100.0);
        manager.addStudent(s);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "添加10000个学生耗时: " << duration.count() << "ms\n";
    
    // 测试查找性能
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000; ++i) {
        manager.findStudent(20210000 + i);
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "查找1000次耗时: " << duration.count() << "ms\n";
}
```

## 📝 项目扩展建议

### 1. 课程管理模块
```cpp
class Course {
private:
    std::string courseId;
    std::string courseName;
    int credits;
    std::string instructor;
    
public:
    // 课程相关方法
};

class Enrollment {
private:
    int studentId;
    std::string courseId;
    double grade;
    std::string semester;
    
public:
    // 选课相关方法
};
```

### 2. 成绩管理系统
```cpp
class GradeManager {
private:
    std::vector<Enrollment> enrollments;
    
public:
    void addGrade(int studentId, const std::string& courseId, double grade);
    double calculateGPA(int studentId) const;
    std::vector<Enrollment> getTranscript(int studentId) const;
};
```

### 3. 报表生成器
```cpp
class ReportGenerator {
public:
    void generateStudentReport(int studentId, const std::string& filename);
    void generateClassReport(const std::string& major, const std::string& filename);
    void generateStatisticsReport(const std::string& filename);
};
```

## 🎯 学习检查清单

完成练习后，检查您是否掌握了以下技能：

- [ ] 能够独立设计和实现新功能
- [ ] 掌握异常处理和错误管理
- [ ] 理解性能优化的基本原则
- [ ] 能够编写单元测试
- [ ] 掌握代码重构技巧
- [ ] 理解软件架构设计原则
- [ ] 能够处理并发和多线程问题
- [ ] 掌握数据库操作基础
- [ ] 理解网络编程概念
- [ ] 能够设计用户友好的界面

## 🎯 本章小结

通过本章的练习和挑战，您应该：
- ✅ 巩固了C++编程技能
- ✅ 学会了独立解决复杂问题
- ✅ 掌握了软件测试和调试方法
- ✅ 了解了系统扩展的可能性

## 🚀 下一步

现在让我们探讨项目的扩展方向和实际应用场景。

[👉 进入第六章：项目扩展](../06-extensions/README.md)

---

💡 **小贴士**: 编程是一门实践性很强的技能，建议您至少完成3-5个练习来巩固所学知识。