#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cstdlib>
using namespace std;

void waitForEnter()
{
    cout << "Press Enter to continue..." <<endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayHeader()
{
    cout << "***********************" << endl;
    cout << "*   BANK MANAGEMENT   *" << endl;
    cout << "***********************" << endl;
}

void displayMenu()
{
    cout << "1. Create" << endl;
    cout << "2. Display" << endl;
    cout << "3. Update" << endl;
    cout << "4. Delete" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

class admin
{
private:
    string username;
    string password;

public:
    admin() {
        username = "admin";
        password = "password";
    }

    void login() {
        string u, p;
        displayHeader();
        cout << "Enter username: ";
        cin >> u;
        cout << "Enter password: ";
        cin >> p;
        if (u == username && p == password) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Login failed!" << endl;
            waitForEnter();
            system("clear");
            login();
        }
    }
};
// Abstract base class Employee
class Employee
{
protected:
    string name;
    int id;

public:
    Employee(string n, int i) : name(n), id(i) {}
    virtual ~Employee() {}
    virtual void displayInfo() const = 0;
    void setName(string n) { name = n; }            //setter
    string getName() const { return name; }         //getter
    void setId(int i) { id = i; }
    int getId() const { return id; }
};

// Derived classes from Employee
class BankTeller : public Employee
{
public:
    BankTeller(string n, int i) : Employee(n, i) {}
    void displayInfo() const override
    {
        cout << "Bank Teller: " << name << ", ID: " << id << endl;
    }
};

class Security : public Employee
{
public:
    Security(string n, int i) : Employee(n, i) {}
    void displayInfo() const override
    {
        cout << "Security: " << name << ", ID: " << id << endl;
    }
};

// Abstract base class Account
class Account
{
protected:
    string accountID;
    double balance;

public:
    Account(string accNum, double bal) : accountID(accNum), balance(bal) {}
    virtual ~Account() {}
    virtual void displayAccountInfo() const = 0;
    void setaccountID(string accNum) { accountID = accNum; }
    string getaccountID() const { return accountID; }
    void setBalance(double bal) { balance = bal; }
    double getBalance() const { return balance; }
};

// Derived classes from Account
class SavingsAccount : public Account
{
public:
    SavingsAccount(string accNum, double bal) : Account(accNum, bal) {}
    void displayAccountInfo() const override
    {
        cout << "Savings Account: " << accountID << ", Balance: " << balance << endl;
    }
};

class CheckingAccount : public Account
{
public:
    CheckingAccount(string accNum, double bal) : Account(accNum, bal) {}
    void displayAccountInfo() const override
    {
        cout << "Checking Account: " << accountID << ", Balance: " << balance << endl;
    }
};

// CRUD operations
class BankManagementSystem
{
    vector<Employee *> employees;
    vector<Account *> accounts;

public:
    BankManagementSystem()
    {
        // Add default employees
        employees.push_back(new BankTeller("Hazwan Adhikara Nasution", 17));
        employees.push_back(new Security("Danar Bagus Rasendriya", 55));
        employees.push_back(new BankTeller("Elgracito Iryanda Endia", 57));

        // Add default accounts
        accounts.push_back(new SavingsAccount("HAN017", 2000.0));
        accounts.push_back(new CheckingAccount("DBR055", 15.0));
        accounts.push_back(new SavingsAccount("EIE057", 1500.0));
    }

    // Create operations
    void addEmployee(Employee *emp)
    {
        employees.push_back(emp);
    }

    void createAccount(Account *acc)
    {
        accounts.push_back(acc);
    }

    // Read operations
    void displayEmployees() const
    {
        for (const auto &emp : employees)
        {
            emp->displayInfo();
        }
    }

    void displayAccounts() const
    {
        for (const auto &acc : accounts)
        {
            acc->displayAccountInfo();
        }
    }

    // Update operations
    void updateEmployee(int id, string newName)
    {
        for (auto &emp : employees)
        {
            if (emp->getId() == id)
            {
                emp->setName(newName);
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }

    void updateAccountBalance(string accNum, double newBalance)
    {
        for (auto &acc : accounts)
        {
            if (acc->getaccountID() == accNum)
            {
                acc->setBalance(newBalance);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    // Delete operations
    void deleteEmployee(int id)
    {
        for (auto it = employees.begin(); it != employees.end(); ++it)
        {
            if ((*it)->getId() == id)
            {
                delete *it;
                employees.erase(it);
                return;
            }
        }
        cout << "Employee not found!" << endl;
    }

    void deleteAccount(string accNum)
    {
        for (auto it = accounts.begin(); it != accounts.end(); ++it)
        {
            if ((*it)->getaccountID() == accNum)
            {
                delete *it;
                accounts.erase(it);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    ~BankManagementSystem()
    {
        for (auto &emp : employees)
        {
            delete emp;
        }
        for (auto &acc : accounts)
        {
            delete acc;
        }
    }
};

// Helper function to read a line of input and trim whitespace
string readLine()
{
    string input;
    getline(cin, input);
    return input;
}

// Helper function to read a double value, stripping out non-numeric characters
double readDouble()
{
    string input;
    double value;
    while (true)
    {
        getline(cin, input);
        input.erase(remove(input.begin(), input.end(), '$'), input.end());
        stringstream ss(input);
        if (ss >> value)
        {
            return value;
        }
        else
        {
            cout << "Invalid input. Please enter a numeric value: ";
        }
    }
}

int main()
{
    admin admin;
    BankManagementSystem bms;
    int choice;
    admin.login();

    do
    {
        system("clear");
        displayHeader();
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("clear");
        switch (choice)
        {
        case 1:
        {
            system("clear");
            displayHeader();
            cout << "1. Add Employee" << endl;
            cout << "2. Create Account" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your choice: ";
            int createChoice;
            cin >> createChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (createChoice == 1)
            {
                system("clear");
                displayHeader();
                cout << "Enter Employee Type (1. Bank Teller, 2. Security, 3.Cancel): ";
                int empType;
                cin >> empType;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(empType == 3) continue;
                cout << "Enter Name: ";
                string name = readLine();
                cout << "Enter ID: ";
                int id;
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (empType == 1)
                {
                    bms.addEmployee(new BankTeller(name, id));
                }
                else if (empType == 2)
                {
                    bms.addEmployee(new Security(name, id));
                }
                else
                {
                    cout << "Invalid Employee Type!" << endl;
                    waitForEnter();
                }
            }
            else if (createChoice == 2)
            {
                system("clear");
                displayHeader();
                cout << "Enter Account Type (1. Savings, 2. Checking, 3. Back): ";
                int accType;
                cin >> accType;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(accType == 3) continue;
                cout << "Enter Account ID: ";
                string accNum = readLine();
                cout << "Enter Balance: ";
                double balance = readDouble();
                if (accType == 1)
                {
                    bms.createAccount(new SavingsAccount(accNum, balance));
                }
                else if (accType == 2)
                {
                    bms.createAccount(new CheckingAccount(accNum, balance));
                }
                else
                {
                    cout << "Invalid Account Type!" << endl;
                    waitForEnter();
                }
            }
            else if (createChoice == 3)
            {
                continue;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
                waitForEnter();
            }
            break;
        }
        case 2:
        {
            displayHeader();
            cout << "1. Display Employees" << endl;
            cout << "2. Display Accounts" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your choice: ";
            int displayChoice;
            cin >> displayChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (displayChoice == 1)
            {
                system("clear");
                bms.displayEmployees();
                waitForEnter();
            }
            else if (displayChoice == 2)
            {
                system("clear");
                bms.displayAccounts();
                waitForEnter();
            }
            else if (displayChoice == 3)
            {
                continue;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
                waitForEnter();
            }
            break;
        }
        case 3:
        {
            displayHeader();
            cout << "1. Update Employee" << endl;
            cout << "2. Update Account Balance" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your choice: ";
            int updateChoice;
            cin >> updateChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (updateChoice == 1)
            {
                vector<Employee *> employees;
                Employee *emp;
                system("clear");
                displayHeader();
                cout << "Enter Employee ID: ";
                int id;
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter New Name: ";
                string newName = readLine();
                bms.updateEmployee(id, newName);
                waitForEnter();
            }
            else if (updateChoice == 2)
            {
                system("clear");
                displayHeader();
                cout << "Enter Account Number: ";
                string accNum = readLine();
                cout << "Enter New Balance: ";
                double newBalance = readDouble();
                bms.updateAccountBalance(accNum, newBalance);
                waitForEnter();
            }
            else if (updateChoice == 3)
            {
                continue;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
                waitForEnter();
            }
            break;
        }
        case 4:
        {
            displayHeader();
            cout << "1. Delete Employee" << endl;
            cout << "2. Delete Account" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your choice: ";
            int deleteChoice;
            cin >> deleteChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (deleteChoice == 1)
            {
                system("clear");
                displayHeader();
                cout << "Enter Employee ID: ";
                int id;
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                bms.deleteEmployee(id);
            }
            else if (deleteChoice == 2)
            {
                system("clear");
                displayHeader();
                cout << "Enter Account Number: ";
                string accNum = readLine();
                bms.deleteAccount(accNum);
            }
            else if (deleteChoice == 3)
            {
                continue;
            }
            else
            {
                cout << "Invalid Choice!" << endl;
                waitForEnter();
            }
            break;
        }
        case 5:
            system("clear");
            cout << "***********************" << endl;
            cout << "*     HAVE A NICE     *" << endl;
            cout << "*        DAY!         *" << endl;
            cout << "***********************";
            break;
        default:
            cout << "Invalid Choice!" << endl;
            waitForEnter();
        }

    } while (choice != 5);

    return 0;
}
