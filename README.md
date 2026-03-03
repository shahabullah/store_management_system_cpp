# 🛒 Store Management System (C++)

A comprehensive, console-based retail management application developed in C++. This project demonstrates a robust implementation of file-based data persistence, multi-user access levels, and automated financial reporting.



## 🛡️ Access Levels
The system is divided into three distinct modules to simulate a real-world business hierarchy:

* **Owner Panel:** High-level management for staff. Features include hiring (adding) employees, viewing the staff directory, and firing (removing) employees.
* **Admin Panel:** The core of inventory management. Admins can add new products, update prices, restock existing items, and delete outdated stock.
* **Employee Panel:** A streamlined interface for sales. Employees can view the product list and process customer transactions.

## ✨ Key Features
* **Persistent Storage:** Uses `fstream` to save/load employee and product data from `.csv` files, ensuring no data is lost when the program closes.
* **Automated Receipt Generation:** Automatically generates a timestamped `.txt` receipt for every sale, including itemized costs and employee signatures.
* **Financial Reporting:** * **Daily:** Tracks total cash earned and specific items sold during the session.
    * **Monthly:** Allows input of expenses (rent, bills, salaries) to calculate Net Profit or Loss.
* **Input Formatting:** Utilizes the `<iomanip>` library to create clean, table-based terminal interfaces.

## 🛠️ Technical Implementation (Student Portfolio)
As a programming project, this code showcases:
* **File I/O & StringStreams:** Efficient parsing of CSV data.
* **Parallel Arrays:** Managing linked data across multiple arrays.
* **System Integration:** Using `<windows.h>` for UI elements like loading screens (`Sleep`) and screen clearing.
* **Time Management:** Using `<ctime>` for real-world date and time stamping.



## 🚀 Setup & Installation
1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/YourUsername/Store-Management-System-CPP.git](https://github.com/YourUsername/Store-Management-System-CPP.git)
    ```
2.  **Directory Requirement:** Ensure the following folders exist in your project directory for the code to save files correctly:
    * `Products/`
    * `Receipts/`
    * `monthly_receipts/`
3.  **Compile:**
    ```bash
    g++ main.cpp -o StoreSystem
    ```
4.  **Run:**
    ```bash
    ./StoreSystem
    ```

---
