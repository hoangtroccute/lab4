// Bean Nguyen

// CS201L Lab 4 - Calculator with File I/O

// Objective: Create a menu-driven calculator that performs
// basic arithmetic and number base conversions with input/output
// from console and output logging to a file.

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

// Global output file stream
ofstream logFile("CalculatorOutput.txt", ios::app);

// Function Prototypes
void displayMainMenu();
void performArithmeticOperations();
void performNumberConversions();
double getValidDoubleInput(const string& prompt);
int getValidIntInput(const string& prompt);
string getValidStringInput(const string& prompt);

// Arithmetic operations
// Pseudocode: Receive two numbers and perform the selected operation
// Return the result or error if division by zero
void performArithmeticOperations() {
    int choice;
    double num1, num2;
    char again;

    do {
        cout << "\nArithmetic Operations:\n";
        cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Return to Main Menu\n";
        choice = getValidIntInput("Enter your choice: ");

        if (choice >= 1 && choice <= 4) {
            num1 = getValidDoubleInput("Enter first number: ");
            num2 = getValidDoubleInput("Enter second number: ");

            double result;
            string op;
            switch (choice) {
            case 1: result = num1 + num2; op = "+"; break;
            case 2: result = num1 - num2; op = "-"; break;
            case 3: result = num1 * num2; op = "*"; break;
            case 4:
                if (num2 == 0) {
                    cout << "Error: Division by zero.\n";
                    logFile << "Division by zero attempted.\n";
                    continue;
                }
                else {
                    result = num1 / num2;
                    op = "/";
                }
                break;
            }
            cout << "Result: " << result << "\n";
            logFile << "Arithmetic: " << num1 << " " << op << " " << num2 << " = " << result << endl;
        }
        else if (choice != 5) {
            cout << "Invalid choice.\n";
        }

        if (choice != 5) {
            cout << "Perform another arithmetic operation? (y/n): ";
            cin >> again;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            again = 'n';
        }

    } while (tolower(again) == 'y');
}

// Number Base Conversions
// Pseudocode: Prompt for input number, convert to requested base, display and log
void performNumberConversions() {
    int choice;
    char again;
    long long decNum;
    string inputStr;

    do {
        cout << "\nNumber Base Conversions:\n";
        cout << "1. Decimal to Binary\n2. Decimal to Octal\n3. Decimal to Hex\n";
        cout << "4. Binary to Decimal\n5. Octal to Decimal\n6. Hex to Decimal\n7. Return to Main Menu\n";
        choice = getValidIntInput("Enter your choice: ");

        switch (choice) {
        case 1:
            decNum = getValidIntInput("Enter decimal number: ");
            cout << "Binary: ";
            {
                string bin = "";
                int n = decNum;
                if (n == 0) bin = "0";
                while (n > 0) {
                    bin = to_string(n % 2) + bin;
                    n /= 2;
                }
                cout << bin << endl;
                logFile << "Decimal to Binary: " << decNum << " -> " << bin << endl;
            }
            break;
        case 2:
            decNum = getValidIntInput("Enter decimal number: ");
            cout << "Octal: ";
            {
                string oct = "";
                int n = decNum;
                if (n == 0) oct = "0";
                while (n > 0) {
                    oct = to_string(n % 8) + oct;
                    n /= 8;
                }
                cout << oct << endl;
                logFile << "Decimal to Octal: " << decNum << " -> " << oct << endl;
            }
            break;
        case 3:
            decNum = getValidIntInput("Enter decimal number: ");
            cout << "Hex: ";
            {
                string hex = "";
                int n = decNum;
                char hexChars[] = "0123456789ABCDEF";
                if (n == 0) hex = "0";
                while (n > 0) {
                    hex = hexChars[n % 16] + hex;
                    n /= 16;
                }
                cout << hex << endl;
                logFile << "Decimal to Hex: " << decNum << " -> " << hex << endl;
            }
            break;
        case 4:
            inputStr = getValidStringInput("Enter binary number: ");
            try {
                long long decimal = 0, power = 1;
                for (int i = inputStr.size() - 1; i >= 0; i--) {
                    if (inputStr[i] != '0' && inputStr[i] != '1') throw invalid_argument("Invalid binary input");
                    if (inputStr[i] == '1') decimal += power;
                    power *= 2;
                }
                cout << "Decimal: " << decimal << endl;
                logFile << "Binary to Decimal: " << inputStr << " -> " << decimal << endl;
            }
            catch (...) {
                cout << "Invalid binary number.\n";
            }
            break;
        case 5:
            inputStr = getValidStringInput("Enter octal number: ");
            try {
                long long decimal = 0, power = 1;
                for (int i = inputStr.size() - 1; i >= 0; i--) {
                    if (inputStr[i] < '0' || inputStr[i] > '7') throw invalid_argument("Invalid octal input");
                    decimal += (inputStr[i] - '0') * power;
                    power *= 8;
                }
                cout << "Decimal: " << decimal << endl;
                logFile << "Octal to Decimal: " << inputStr << " -> " << decimal << endl;
            }
            catch (...) {
                cout << "Invalid octal number.\n";
            }
            break;
        case 6:
            inputStr = getValidStringInput("Enter hex number: ");
            try {
                long long decimal = 0, power = 1;
                for (int i = inputStr.size() - 1; i >= 0; i--) {
                    char c = toupper(inputStr[i]);
                    int digit;
                    if (c >= '0' && c <= '9') digit = c - '0';
                    else if (c >= 'A' && c <= 'F') digit = 10 + (c - 'A');
                    else throw invalid_argument("Invalid hex input");
                    decimal += digit * power;
                    power *= 16;
                }
                cout << "Decimal: " << decimal << endl;
                logFile << "Hex to Decimal: " << inputStr << " -> " << decimal << endl;
            }
            catch (...) {
                cout << "Invalid hexadecimal number.\n";
            }
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice.\n";
            break;
        }

        cout << "Perform another conversion? (y/n): ";
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (tolower(again) == 'y');
}

// Display the main menu
void displayMainMenu() {
    cout << "\n==== C++ Calculator ====" << endl;
    cout << "1. Arithmetic Operations\n2. Number Base Conversions\n3. Exit\n";
}

// Input validation helpers
int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getValidStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// Main Program
int main() {
    int choice;
    do {
        displayMainMenu();
        choice = getValidIntInput("Enter your choice: ");
        switch (choice) {
        case 1: performArithmeticOperations(); break;
        case 2: performNumberConversions(); break;
        case 3: cout << "Goodbye!\n"; break;
        default: cout << "Invalid option.\n"; break;
        }
    } while (choice != 3);

    logFile.close();
    return 0;
}
