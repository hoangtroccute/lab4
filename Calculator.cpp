#include <iostream>
#include <string>
#include <limits> // For numeric_limits
#include <cmath>  // For pow in conversions
#include <algorithm> // For std::reverse
#include <sstream> // For hexadecimal conversions
using namespace std;

// --- Function Prototypes ---
void displayMainMenu();
void performArithmeticOperations();
void performNumberConversions();

// Arithmetic Functions
double add(double num1, double num2);
double subtract(double num1, double num2);
double multiply(double num1, double num2);
double divide(double num1, double num2);

// Conversion Functions (Declarations - implementations below)
string decToBin(long long decimalNum);
string decToOct(long long decimalNum);
string decToHex(long long decimalNum);
long long binToDec(const string& binaryNum);
long long octToDec(const string& octalNum);
long long hexToDec(const string& hexNum);

// Input Validation Helper
double getValidDoubleInput(const string& prompt);
int getValidIntInput(const string& prompt);
string getValidStringInput(const string& prompt);

// --- Main Function ---
int main() {
    int choice;
    do {
        displayMainMenu();
        choice = getValidIntInput("Enter your choice: ");

        switch (choice) {
        case 1:
            performArithmeticOperations();
            break;
        case 2:
            performNumberConversions();
            break;
        case 3:
            cout << "Exiting Calculator. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        cout << "\n"; // Add a newline for better spacing between main menu loops
    } while (choice != 3);

    return 0;
}

// --- Function Definitions ---

void displayMainMenu() {
    cout << "Welcome to the C++ Calculator!\n";
    cout << "Main Menu:\n";
    cout << "1. Arithmetic Operations\n";
    cout << "2. Number Base Conversions\n";
    cout << "3. Exit\n";
}

void performArithmeticOperations() {
    int choice;
    double num1, num2;
    char continueOp;

    do {
        cout << "\nArithmetic Operations:\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Back to Main Menu\n";
        choice = getValidIntInput("Enter your choice: ");

        if (choice >= 1 && choice <= 4) {
            num1 = getValidDoubleInput("Enter first number: ");
            num2 = getValidDoubleInput("Enter second number: ");

            switch (choice) {
            case 1:
                cout << "Result: " << add(num1, num2) << "\n";
                break;
            case 2:
                cout << "Result: " << subtract(num1, num2) << "\n";
                break;
            case 3:
                cout << "Result: " << multiply(num1, num2) << "\n";
                break;
            case 4:
                if (num2 != 0) {
                    cout << "Result: " << divide(num1, num2) << "\n";
                }
                else {
                    cout << "Error: Division by zero is not allowed.\n";
                }
                break;
            }
        }
        else if (choice == 5) {
            break; // Exit to main menu
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "Do you want to perform another arithmetic operation? (y/n): ";
        cin >> continueOp;
        // Clear buffer after char input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (tolower(continueOp) == 'y');
}

void performNumberConversions() {
    int choice;
    long long decimalNum;
    string numString;
    char continueConv;

    do {
        cout << "\nNumber Base Conversions:\n";
        cout << "1. Decimal to Binary\n";
        cout << "2. Decimal to Octal\n";
        cout << "3. Decimal to Hexadecimal\n";
        cout << "4. Binary to Decimal\n";
        cout << "5. Octal to Decimal\n";
        cout << "6. Hexadecimal to Decimal\n";
        cout << "7. Back to Main Menu\n";
        choice = getValidIntInput("Enter your choice: ");

        switch (choice) {
        case 1:
            decimalNum = getValidIntInput("Enter decimal number: ");
            cout << "Binary equivalent: " << decToBin(decimalNum) << "\n";
            break;
        case 2:
            decimalNum = getValidIntInput("Enter decimal number: ");
            cout << "Octal equivalent: " << decToOct(decimalNum) << "\n";
            break;
        case 3:
            decimalNum = getValidIntInput("Enter decimal number: ");
            cout << "Hexadecimal equivalent: " << decToHex(decimalNum) << "\n";
            break;
        case 4:
            numString = getValidStringInput("Enter binary number: ");
            try {
                long long dec = binToDec(numString);
                cout << "Decimal equivalent: " << dec << "\n";
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << "\n";
            }
            break;
        case 5:
            numString = getValidStringInput("Enter octal number: ");
            try {
                long long dec = octToDec(numString);
                cout << "Decimal equivalent: " << dec << "\n";
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << "\n";
            }
            break;
        case 6:
            numString = getValidStringInput("Enter hexadecimal number: ");
            try {
                long long dec = hexToDec(numString);
                cout << "Decimal equivalent: " << dec << "\n";
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << "\n";
            }
            break;
        case 7:
            break; // Exit to main menu
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        if (choice != 7) { // Don't ask to continue if user chose to go back
            cout << "Do you want to perform another conversion? (y/n): ";
            cin >> continueConv;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            continueConv = 'n'; // Exit loop if user chose to go back
        }

    } while (tolower(continueConv) == 'y');
}

// --- Arithmetic Function Implementations ---
double add(double num1, double num2) { return num1 + num2; }
double subtract(double num1, double num2) { return num1 - num2; }
double multiply(double num1, double num2) { return num1 * num2; }
double divide(double num1, double num2) { return num1 / num2; }

// --- Conversion Function Implementations ---

string decToBin(long long decimalNum) {
    if (decimalNum == 0) return "0";
    string binaryString = "";
    bool isNegative = false;
    if (decimalNum < 0) {
        isNegative = true;
        decimalNum = -decimalNum; // Work with positive value
    }

    while (decimalNum > 0) {
        binaryString = (decimalNum % 2 == 0 ? "0" : "1") + binaryString;
        decimalNum /= 2;
    }
    return (isNegative ? "-" : "") + binaryString;
}

string decToOct(long long decimalNum) {
    if (decimalNum == 0) return "0";
    string octalString = "";
    bool isNegative = false;
    if (decimalNum < 0) {
        isNegative = true;
        decimalNum = -decimalNum;
    }

    while (decimalNum > 0) {
        octalString = to_string(decimalNum % 8) + octalString;
        decimalNum /= 8;
    }
    return (isNegative ? "-" : "") + octalString;
}

string decToHex(long long decimalNum) {
    if (decimalNum == 0) return "0";
    string hexString = "";
    char hexChars[] = "0123456789ABCDEF";
    bool isNegative = false;
    if (decimalNum < 0) {
        isNegative = true;
        decimalNum = -decimalNum;
    }

    while (decimalNum > 0) {
        hexString = hexChars[decimalNum % 16] + hexString;
        decimalNum /= 16;
    }
    return (isNegative ? "-" : "") + hexString;
}

long long binToDec(const string& binaryNum) {
    long long decimal = 0;
    long long power = 1; // Represents 2^0, 2^1, 2^2, ...

    // Validate binary string (only '0' and '1')
    for (char c : binaryNum) {
        if (c != '0' && c != '1') {
            throw invalid_argument("Invalid binary number: " + binaryNum + ". Contains non-binary digits.");
        }
    }

    // Iterate from right to left (least significant bit to most significant bit)
    for (int i = binaryNum.length() - 1; i >= 0; i--) {
        if (binaryNum[i] == '1') {
            decimal += power;
        }
        power *= 2;
    }
    return decimal;
}

long long octToDec(const string& octalNum) {
    long long decimal = 0;
    long long power = 1; // Represents 8^0, 8^1, 8^2, ...

    // Validate octal string (only '0'-'7')
    for (char c : octalNum) {
        if (c < '0' || c > '7') {
            throw invalid_argument("Invalid octal number: " + octalNum + ". Contains non-octal digits.");
        }
    }

    for (int i = octalNum.length() - 1; i >= 0; i--) {
        decimal += (octalNum[i] - '0') * power;
        power *= 8;
    }
    return decimal;
}

long long hexToDec(const string& hexNum) {
    long long decimal = 0;
    long long power = 1; // Represents 16^0, 16^1, 16^2, ...

    for (int i = hexNum.length() - 1; i >= 0; i--) {
        char c = toupper(hexNum[i]); // Convert to uppercase for consistent handling
        int digitValue;

        if (c >= '0' && c <= '9') {
            digitValue = c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            digitValue = 10 + (c - 'A');
        }
        else {
            throw invalid_argument("Invalid hexadecimal number: " + hexNum + ". Contains non-hexadecimal digits.");
        }
        decimal += digitValue * power;
        power *= 16;
    }
    return decimal;
}

// --- Input Validation Helpers ---

double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear(); // Clear the error flag
            // Discard invalid input from the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            // Discard any remaining characters in the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid integer.\n";
            cin.clear(); // Clear the error flag
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
    getline(cin, value); // Read the whole line
    return value;
}