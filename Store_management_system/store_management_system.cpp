#include <iostream>
#include <fstream> // To read/write files
#include <string>
#include <ctime>     // For date and time functions
#include <iomanip>   // For formatting output
#include <windows.h> // For Sleep() and system("cls")
#include <sstream>   // Allows reading from or writing to strings just like cin/cout

using namespace std;

// Employee Management Variables
string empUsernames[50];
string empPasswords[50];
string empNames[50];
int empCount = 0;
string empFilePath = "employees.csv";
string receiptFolderPath = "D:\\1st sem\\Programming fundamental theory\\Store_management_system\\Receipts";

// --- VARIABLES ---
int id[100];
string names[100];
int prices[100];
int quantities[100];
int soldCounts[100]; // Keeps track of how many we sold today
int count;
int totalMoneyToday = 0; // Total cash earned today
string filePath = "D:\\1st sem\\Programming fundamental theory\\Store_management_system\\Products\\products_in_Store.csv";

void showLoadingScreen()
{
    system("cls");
    cout << "Loading";
    for (int i = 0; i < 5; i++)
    {
        cout << ".";
        Sleep(500); // Pause for half a second(30 ms).
    }
}

// --- LOAD EMPLOYEES FROM FILE ---
void loadEmployees()
{
    ifstream file(empFilePath);
    string line;
    empCount = 0;

    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, empUsernames[empCount], ',');
        getline(ss, empPasswords[empCount], ',');
        getline(ss, empNames[empCount], ',');
        empCount++;
    }
    file.close();
}

// --- ADD NEW EMPLOYEE ---
void addEmployee()
{
    ofstream file(empFilePath, ios::app);
    cout << "Enter New Employee Details" << endl;
    cout << "==========================" << endl;
    cout << "Enter Employee Username: ";
    cin >> empUsernames[empCount];

    cout << "Enter Password: ";
    cin >> empPasswords[empCount];

    cout << "Enter Employee Name: ";
    cin >> empNames[empCount];
    cout << "==========================" << endl;

    file << empUsernames[empCount] << ","
         << empPasswords[empCount] << ","
         << empNames[empCount] << endl;

    empCount++;
    file.close();

    cout << "Employee account created successfully!" << endl;
    system("pause");
}

void employeeList()
{
    loadEmployees();
    cout << "========== EMPLOYEE LIST ===========" << endl;
    cout << left << setw(25) << "Username" << setw(25) << "Employee Name" << endl;
    cout << "====================================" << endl;
    for (int i = 0; i < empCount; i++)
    {
        string userName = empUsernames[i];
        string empName = empNames[i];
        if (userName.length() > 24)
            userName = userName.substr(0, 24);
        if (empName.length() > 24)
            empName = empName.substr(0, 24);

        cout << left << setw(25) << userName << setw(25) << empName << endl;
    }
    cout << "====================================" << endl;
    system("pause");
}

// --- FIRE EMPLOYEE ---
void fireEmployee()
{
    if (empCount == 0)
    {
        cout << "No employees to fire!" << endl;
        system("pause");
        return;
    }

    cout << "===== EMPLOYEE LIST =====" << endl;
    cout << left << setw(25) << "Username" << left << setw(25) << "Employee Name" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < empCount; i++)
    {
        string username = empUsernames[i];
        string empName = empNames[i];
        if (username.length() > 24)
            username = username.substr(0, 24);
        if (empName.length() > 24)
            empName = empName.substr(0, 24);
        cout << left << setw(25) << username << left << setw(25) << empName << endl;
    }

    string usernameToFire;
    cout << "\nEnter Username of Employee to Fire: ";
    cin >> usernameToFire;

    int index = -1;
    for (int i = 0; i < empCount; i++)
    {
        if (empUsernames[i] == usernameToFire)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Employee not found!" << endl;
        system("pause");
        return;
    }

    // Shift arrays to remove the employee
    for (int i = index; i < empCount - 1; i++)
    {
        empUsernames[i] = empUsernames[i + 1];
        empPasswords[i] = empPasswords[i + 1];
        empNames[i] = empNames[i + 1];
    }

    empCount--;

    // Rewrite CSV file
    ofstream file(empFilePath, ios::trunc); // overwrite existing
    for (int i = 0; i < empCount; i++)
    {
        file << empUsernames[i] << "," << empPasswords[i] << "," << empNames[i] << endl;
    }
    file.close();

    cout << "Employee " << usernameToFire << " has been fired successfully!" << endl;
    system("pause");
}

// --- EMPLOYEE LOGIN ---
bool employeeLogin(string &loggedInName)
{
    string user, pass;
    cout << "Enter Your Credentials" << endl;
    cout << "=========================" << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    cout << "=========================" << endl;

    for (int i = 0; i < empCount; i++)
    {
        if (empUsernames[i] == user && empPasswords[i] == pass)
        {
            loggedInName = empNames[i];
            return true;
        }
    }
    return false;
}

// --- STEP 1: READ & WRITE EXCEL ---
void saveToFile()
{
    ofstream file;
    // ios::trunc deletes old data and writes new fresh data
    file.open(filePath, ios::trunc);

    if (file.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            // Write: ID,Name,Price,Quantity
            file << id[i] << "," << names[i] << "," << prices[i] << "," << quantities[i] << endl;
        }
        file.close();
    }
}

void readFromFile()
{
    ifstream file;
    file.open(filePath);

    string line;
    count = 0; // Reset count

    while (getline(file, line))
    {
        stringstream ss(line);
        string s_id, s_name, s_price, s_qty;

        // Break the line by commas
        getline(ss, s_id, ',');
        getline(ss, s_name, ',');
        getline(ss, s_price, ',');
        getline(ss, s_qty, ',');

        // Convert strings to numbers and store in arrays
        if (!s_name.empty())
        {
            id[count] = stoi(s_id); // stoi() Convert string to int
            names[count] = s_name;
            prices[count] = stoi(s_price);
            quantities[count] = stoi(s_qty);
            soldCounts[count] = 0; // Reset sold count for today
            count++;
        }
    }
    file.close();
}

// --- SHOW LIST ---
void showProducts()
{
    cout << "===============================================" << endl;
    cout << left << setw(6) << "S_No"
         << left << setw(25) << "Name"
         << left << setw(10) << "Price"
         << left << setw(10) << "Quantity" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        string productName = names[i];
        if (productName.length() > 24) // truncate long names
            productName = productName.substr(0, 24);

        cout << left << setw(6) << id[i]
             << left << setw(25) << productName
             << left << setw(10) << prices[i]
             << left << setw(10) << quantities[i] << endl;
    }
    cout << "===============================================" << endl;
}

// Customer Receipt
void saveReceiptToFile(string empName, string itemNames[], int totalCost[], int itemsToBuy,
                       int total, int discount, int finalPay)
{
    time_t now = time(0);
    string fileName = receiptFolderPath + "\\Receipt_" + "By_" + empName + "_" + to_string(now) + ".txt";
    ofstream file(fileName);

    if (file.is_open())
    {
        file << "******** RECEIPT ********\n";

        // Use fixed width for employee name
        file << left << setw(15) << "Printed by:" << empName << "\n";
        file << string(30, '*') << "\n"; // line of stars

        // Header for items
        file << left << setw(25) << "Item Name" << setw(10) << "Price" << "\n";
        file << string(35, '-') << "\n";

        for (int i = 0; i < itemsToBuy; i++)
        {
            if (totalCost[i] > 0)
            {
                // left-align item name, right-align price
                file << left << setw(25) << itemNames[i]
                     << right << setw(10) << totalCost[i] << "\n";
            }
        }

        file << string(35, '-') << "\n";
        file << left << setw(25) << "Total:" << right << setw(10) << total << "\n";
        file << left << setw(25) << "Discount:" << right << setw(10) << discount << "\n";
        file << left << setw(25) << "Paid:" << right << setw(10) << finalPay << "\n";
        file << string(35, '*') << "\n";

        file.close();
    }
}

// --- STEP 2 & 6: SELL PRODUCT ---
void sellProduct(string empName)
{
    int idNo, qty;
    int currentBill = 0; // Bill for this customer

    cout << "How many different items are you buying: ";
    int itemsToBuy;
    cin >> itemsToBuy;

    int totalCost[itemsToBuy];
    string itemNames[itemsToBuy];

    showProducts();

    for (int i = 0; i < itemsToBuy; i++)
    {
        cout << "\nEnter S_No to sell: ";
        cin >> idNo;

        // Find the product index
        int index = -1;
        for (int j = 0; j < count; j++)
        {
            if (id[j] == idNo)
            {
                index = j;
                break;
            }
        }

        if (index != -1)
        {
            cout << "Enter Quantity: ";
            cin >> qty;

            if (qty <= quantities[index])
            {
                quantities[index] -= qty;
                soldCounts[index] += qty;

                int cost = prices[index] * qty;
                currentBill += cost;

                totalCost[i] = cost;
                itemNames[i] = names[index];

                saveToFile(); // Save stock changes
            }
            else
            {
                cout << "Not enough stock!" << endl;
                totalCost[i] = 0;
                itemNames[i] = "N/A";
            }
        }
        else
        {
            cout << "Wrong ID!" << endl;
            totalCost[i] = 0;
            itemNames[i] = "Nill";
        }
    }
    time_t t = time(0);
    tm *now = localtime(&t);
    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;
    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;

    cout << "************* RECEIPT *************" << endl;
    cout << left << setw(15) << "Printed by:" << empName << endl;
    cout << left << setw(15) << "Date:"
         << day << "/" << month << "/" << year << endl;
    cout << left << setw(15) << "Time:"
         << setw(2) << setfill('0') << hour << ":"
         << setw(2) << setfill('0') << min << ":"
         << setw(2) << setfill('0') << sec << endl;
    cout << setfill(' ');
    cout << string(35, '-') << endl;

    // Header for items
    cout << left << setw(25) << "Item Name" << right << setw(10) << "Price" << endl;
    cout << string(35, '-') << endl;

    for (int i = 0; i < itemsToBuy; i++)
    {
        if (totalCost[i] > 0)
        {
            cout << left << setw(25) << itemNames[i]
                 << right << setw(10) << totalCost[i] << endl;
        }
    }

    cout << string(35, '-') << endl;
    cout << left << setw(25) << "Total:" << right << setw(10) << currentBill << endl;
    cout << string(35, '-') << endl << endl;

    // --- DISCOUNT LOGIC ---
    int discount;
    cout << "Give Discount (Enter amount, 0 for none): ";
    cin >> discount;

    if (discount < 0 || discount > currentBill)
        discount = 0;

    int finalPay = currentBill - discount;
    totalMoneyToday += finalPay;

    // Get current date and time

    system("cls");

    cout << "\nHere is Your Receipt:\n\n";
    cout << "************* RECEIPT *************" << endl;
    cout << left << setw(15) << "Printed by:" << empName << endl;
    cout << left << setw(15) << "Date:"
         << day << "/" << month << "/" << year << endl;
    cout << left << setw(15) << "Time:"
         << setw(2) << setfill('0') << hour << ":"
         << setw(2) << setfill('0') << min << ":"
         << setw(2) << setfill('0') << sec << endl;
    cout << setfill(' ');
    cout << string(35, '-') << endl;

    // Header for items
    cout << left << setw(25) << "Item Name" << right << setw(10) << "Price" << endl;
    cout << string(35, '-') << endl;

    for (int i = 0; i < itemsToBuy; i++)
    {
        if (totalCost[i] > 0)
        {
            cout << left << setw(25) << itemNames[i]
                 << right << setw(10) << totalCost[i] << endl;
        }
    }

    cout << string(35, '-') << endl;
    cout << left << setw(25) << "Total:" << right << setw(10) << currentBill << endl;
    cout << left << setw(25) << "Discount:" << right << setw(10) << discount << endl;
    cout << left << setw(25) << "Paid:" << right << setw(10) << finalPay << endl;
    cout << string(35, '*') << endl;

    system("pause");

    // Save receipt to file
    saveReceiptToFile(empName, itemNames, totalCost, itemsToBuy, currentBill, discount, finalPay);
}

// --- EMPLOYEE PANEL to Sale items ---
void employeePanel(string empName)
{
    system("cls");
    cout << "===== EMPLOYEE PANEL =====" << endl;
    cout << "Welcome: " << empName << endl;
    cout << "====================================" << endl;
    cout << "1. View Products" << endl;
    cout << "2. Sell Product" << endl;
    cout << "3. Logout & goto main menu" << endl;
    cout << "====================================" << endl;
    cout << "Choice: ";
}

// --- STEP 4: DAILY REPORT ---
void dailyReport()
{
    system("cls");
    cout << "********** DAILY REPORT **********" << endl;
    cout << "Total Cash Earned: " << totalMoneyToday << " Rs" << endl;
    cout << string(40, '-') << endl;

    cout << "-------- Items Sold Today ---------" << endl;
    cout << string(40, '-') << endl;

    // Header with proper spacing
    cout << left << setw(25) << "Item Name" << right << setw(10) << "Sold Count" << endl;
    cout << string(35, '-') << endl;

    // Print items sold
    for (int i = 0; i < count; i++)
    {
        if (soldCounts[i] > 0)
        {
            cout << left << setw(25) << names[i]
                 << right << setw(10) << soldCounts[i] << endl;
        }
    }

    system("pause");
}

// --- UPDATE PRICE ---
void updatePrice()
{
    int idNo, newPrice;
    char choice;
    do
    {
        system("cls");
        showProducts();
        cout << "Enter S_No to Update Price: ";
        cin >> idNo;

        // Simple search
        int index = -1;
        for (int i = 0; i < count; i++)
        {
            if (id[i] == idNo)
                index = i;
        }

        if (index != -1)
        {
            cout << "Enter New Price: ";
            cin >> newPrice;
            prices[index] = newPrice;
            saveToFile();
            cout << "Updated!" << endl;
        }

        cout << "Update another? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

// --- STEP 5: MONTHLY REPORT ---
void monthlyReport()
{
    system("cls");

    string monthlyReportFile = "D:\\1st sem\\Programming fundamental theory\\Store_management_system\\monthly_receipts";

    // Get current date and time
    time_t t = time(0); // get time now
    tm *now = localtime(&t);

    int day = now->tm_mday;
    int month = now->tm_mon + 1; // tm_mon is 0-11
    int year = now->tm_year + 1900;

    int hour = now->tm_hour;
    int min = now->tm_min;
    int sec = now->tm_sec;

    int rent, bill, empSalary;

    cout << "********** MONTHLY REPORT **********" << endl;
    cout << "\nTotal Income: " << totalMoneyToday << " Rs"
         << "   Date: " << day << "/" << month << "/" << year
         << "   Time: " << setw(2) << setfill('0') << hour
         << ":" << setw(2) << setfill('0') << min
         << ":" << setw(2) << setfill('0') << sec << endl;

    cout << setfill(' ');
    cout << string(70, '-') << endl;

    // Input expenses
    cout << left << setw(25) << "Enter Rent:";
    cin >> rent;
    cout << left << setw(25) << "Enter Bills:";
    cin >> bill;
    cout << left << setw(25) << "Enter Employee Salary:";
    cin >> empSalary;

    int totalExpense = rent + bill + empSalary;
    int profit = totalMoneyToday - totalExpense;

    stringstream fileName;
    fileName << monthlyReportFile << "\\MonthlyReport_"
             << year << "_" << setw(2) << setfill('0') << month
             << "_" << setw(2) << setfill('0') << day
             << "_" << setw(2) << setfill('0') << hour << setw(2) << min << setw(2) << sec << ".txt";

    ofstream file(fileName.str());

    if (file.is_open())
    {
        file << "********** MONTHLY REPORT **********\n\n";
        file << "Total Income: " << totalMoneyToday << " Rs"
             << "   Date: " << day << "/" << month << "/" << year
             << "   Time: " << setw(2) << setfill('0') << hour
             << ":" << setw(2) << min
             << ":" << setw(2) << sec << "\n";
        file << setfill(' ');
        file << string(70, '-') << "\n\n";

        file << left << setw(30) << "Expense Type" << right << setw(17) << "Amount (Rs)" << endl;
        file << string(45, '-') << endl;
        file << left << setw(30) << "Rent" << right << setw(15) << rent << endl;
        file << left << setw(30) << "Bills" << right << setw(15) << bill << endl;
        file << left << setw(30) << "Employee Salary" << right << setw(15) << empSalary << endl;
        file << string(45, '-') << endl;

        if (profit >= 0)
            file << left << setw(30) << "NET PROFIT" << right << setw(15) << profit << " Rs" << endl;
        else
            file << left << setw(30) << "NET LOSS" << right << setw(15) << -profit << " Rs" << endl;

        file << string(45, '*') << endl;

        file.close();
        cout << "\nMonthly report saved as: " << fileName.str() << endl;
    }
    else
    {
        cout << "Error: Cannot save monthly report!" << endl;
    }

    system("pause");
}

// --- ADD NEW ITEM ---
void addItem()
{
    system("cls");

    cout << "How Many Items to Add: ";
    int itemsToAdd;
    cin >> itemsToAdd;

    for (int i = 0; i < itemsToAdd; i++)
    {

        id[count] = count + 1; // Auto ID
        cout << "New ID: " << id[count] << endl;
        cout << "Name: ";
        cin >> names[count];
        cout << "Price: ";
        cin >> prices[count];
        cout << "Quantity: ";
        cin >> quantities[count];
        cout << "Item Added!" << endl
             << endl;
        count++;

        saveToFile();
    }
}

// --- Delete ITEM ---
void deleteItem()
{
    int idNo;

    system("cls");
    showProducts();

    cout << "How many items to delete: ";
    int itemsToDelete;
    cin >> itemsToDelete;

    for (int i = 0; i < itemsToDelete; i++)
    {

        cout << "Enter S_No to Delete: ";
        cin >> idNo;

        // Simple search

        if (idNo <= 0 || idNo > count)
        {
            cout << "Invalid S_No!" << endl;
        }

        int index = -1;
        for (int i = 0; i < count; i++)
        {
            if (id[i] == idNo)
                index = i;
        }

        if (index != -1)
        {
            // Shift items left to overwrite deleted i
            for (int j = index; j < count - 1; j++)
            {
                id[j] = id[j + 1];
                names[j] = names[j + 1];
                prices[j] = prices[j + 1];
                quantities[j] = quantities[j + 1];
            }
            count--; // Decrease count
            saveToFile();
            cout << "Deleted!" << endl;
        }
    }
}

// --- RESTOCK ---
void restockItem()
{
    int idNo, qty;
    char choice;
    do
    {
        system("cls");
        showProducts();
        cout << "Enter S_No to Restock: ";
        cin >> idNo;

        // Simple search
        int index = -1;
        for (int i = 0; i < count; i++)
        {
            if (id[i] == idNo)
                index = i;
        }

        if (index != -1)
        {
            cout << "Enter Quantity to add: ";
            cin >> qty;
            quantities[index] += qty;
            saveToFile();
            cout << "Updated!" << endl;
        }

        cout << "Restock another? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

// --- MAIN MENU ---
int main()
{
    readFromFile();  // Load data when game starts
    loadEmployees(); // Load employees when game starts

    string adminPassword = "admin";
    string pass;

again:
    system("cls");
    cout << "====================================" << endl;
    cout << "               MAIN MENU           " << endl;
    cout << "====================================" << endl;
    cout << "1. Employee Login" << endl;
    cout << "2. Admin Panel" << endl;
    cout << "3. Owner Panel" << endl;
    cout << "4. Exit" << endl;
    cout << "====================================" << endl;
    cout << "Select: ";
    int n;
    cin >> n;
    if (n == 1)
    {
        cin.ignore();
    empLogin:
        string empName;
        if (employeeLogin(empName))
        {
            cin.ignore();
            int choice;
            while (true)
            {
                employeePanel(empName);
                cin >> choice;
                if (choice == 1)
                {
                    showProducts();
                    system("pause");
                }
                else if (choice == 2)
                {
                    sellProduct(empName);
                }
                else if (choice == 3)
                {
                    goto again;
                }
                else
                {
                    cout << "Invalid Input" << endl;
                    cout << "Press any key to continue...";
                    system("pause");
                }
            }
        }
        else
        {
            cout << "Invalid Credentials!" << endl;
            cout << "Enter valid username and password." << endl;
            goto empLogin;
        }
    }
    else if (n == 2)
    {
        cin.ignore();
        cout << "Enter Password of Admin Panel: ";
    start2:
        getline(cin, pass);

        if (pass != adminPassword)
        {
            cout << "Incorrect Password" << endl;
            cout << "Please Re-Enter Your Password: ";
            goto start2;
        }
        else
        {
            int option;
            showLoadingScreen();
            while (true)
            {
                system("cls");
                cout << "======================================================================" << endl;
                cout << "                    WELCOME TO ADMIN PANEL                  " << endl;
                cout << "======================================================================" << endl;
                cout << "1. View Products" << endl;
                cout << "2. Add New Item" << endl;
                cout << "3. Update Price" << endl;
                cout << "4. Restock Item" << endl;
                cout << "5. Daily Report" << endl;
                cout << "6. Monthly Report" << endl;
                cout << "7. Delete Item" << endl;
                cout << "8. Main Menu" << endl;
                cout << "=======================================================================" << endl;
                cout << "Select: ";
                cin >> option;

                if (option == 1)
                {
                    system("cls");
                    showProducts();
                    system("pause");
                }

                else if (option == 2)
                    addItem();

                else if (option == 3)
                    updatePrice();

                else if (option == 4)
                    restockItem();

                else if (option == 5)
                    dailyReport();

                else if (option == 6)
                    monthlyReport();

                else if (option == 7)
                    deleteItem();

                else if (option == 8)
                    goto again;
                else
                {
                    cout << "Invalid Input" << endl;
                    cout << "Press any key to continue...";
                    system("pause");
                }
            }
        }
    }
    else if (n == 3)
    {
        int choice;
        while (true)
        {
            system("cls");
            cout << "Welcome to Owner Panel" << endl;
            // Owner specific functionalities can be added here
            cout << "====================================" << endl;
            cout << "1. Add Employee" << endl;
            cout << "2. Show Employees" << endl;
            cout << "3. Fire Employee" << endl;
            cout << "4. Main Menu" << endl;
            cout << "5. Exit" << endl;
            cout << "====================================" << endl;
            cout << "Select: ";
            cin >> choice;
            if (choice == 1)
            {
                addEmployee();
            }
            else if (choice == 2)
            {
                employeeList();
            }
            else if (choice == 3)
            {
                fireEmployee();
            }
            else if (choice == 4)
            {
                goto again;
            }
            else if (choice == 5)
            {
                return 0;
            }
            else
            {
                cout << "Invalid Input" << endl;
                system("pause");
            }
        }
    }
    else if (n == 4)
    {
        return 0;
    }
    else
    {
        cout << "Invalid Input" << endl;
        system("pause");
    }
    return 0;
}