#include <iostream>
using namespace std;

class Employee {
private:
    string name;
public:
    Employee() = default;
    Employee(const string& name) {
        this->name = name;
    }

    virtual ~Employee() = default;

    string getName() const {
        return name;
    }

    friend ostream& operator<<(ostream& os, const Employee& obj) {
        os << obj.getName() << "的薪资是" << obj.calculateSalary();
        return os;
    }

    virtual double calculateSalary() const = 0;
};

class FullTimeEmployee : public Employee {
private:
    double monthlySalary, bonus;
public:
    FullTimeEmployee(const string& name, double monthlySalary, double bonus) : Employee(name) {
        this->monthlySalary = monthlySalary;
        this->bonus = bonus;
    }

    ~FullTimeEmployee() override = default;

    double calculateSalary() const override {
        return monthlySalary + bonus;
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlySalary, workHours;
public:
    PartTimeEmployee(const string& name, const double& hourlySalary, const double& workHours) : Employee(name) {
        this->hourlySalary = hourlySalary;
        this->workHours = workHours;
    }

    ~PartTimeEmployee() override = default;

    double calculateSalary() const override {
        if (workHours > 160) {
            return hourlySalary * 160 + 1.5 * hourlySalary * (workHours - 160);
        }
        return hourlySalary * workHours;
    }
};

struct EmployeeInfo {
    int type;
    string name;
    double val1, val2;
};

int main() {
    Employee* employee[3];
/*
全职员工 张三 8000 2000
全职员工 王五 7500 1500
兼职员工 李四 60 180
*/

    for (int i = 0; i < 3; i++) {
        string type, name;
        double val1, val2;

        cin >> type >> name >> val1 >> val2;

        if (type == "全职员工") {
            employee[i] = new FullTimeEmployee(name, val1, val2);
        } else if (type == "兼职员工"){
            employee[i] = new PartTimeEmployee(name, val1, val2);
        }
    }

    double totalSalary = 0;

    for (int i = 0; i < 3; i++) {
        cout << *employee[i] << endl;
        totalSalary += employee[i]->calculateSalary();
    }
    cout << "总薪资是：" << totalSalary << endl;

    for (int i = 0; i < 3; i++) {
        delete employee[i];
        employee[i] = nullptr;
    }

    return 0;
}