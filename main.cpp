#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct User {
    string username;
    string email;
    string password;
};

// Function to check password strength
bool isStrongPassword(const string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    string specialChars = "!@#$%^&*()-_+=<>?/";

    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
        if (specialChars.find(ch) != string::npos) hasSpecial = true;
    }

    return password.length() >= 8 && hasUpper && hasLower && hasDigit && hasSpecial;
}

// Function to save user data to file
bool saveUser(const User& user) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << user.username << "|" << user.email << "|" << user.password << endl;
        file.close();
        return true;
    } else {
        cout << "Error: Unable to open file!" << endl;
        return false;
    }
}

// Function to read all users from file
vector<User> readUsers() {
    vector<User> users;
    ifstream file("users.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string username, email, password;
        if (getline(ss, username, '|') && getline(ss, email, '|') && getline(ss, password, '|')) {
            users.push_back({username, email, password});
        }
    }
    file.close();
    return users;
}

// Signup function
void signup() {
    User user;
    cout << "\n|------ Sign Up ------|\n";
    cout << "Enter Username (no spaces or |): ";
    cin >> user.username;
    if (user.username.find('|') != string::npos) {
        cout << "Error: Username cannot contain '|'.\n";
        return;
    }

    cout << "Enter Email (no spaces or |): ";
    cin >> user.email;
    if (user.email.find('|') != string::npos) {
        cout << "Error: Email cannot contain '|'.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
    cout << "Enter Password (min 8 chars, upper, lower, digit, special, no |): ";
    getline(cin, user.password);
    if (user.password.find('|') != string::npos) {
        cout << "Error: Password cannot contain '|'.\n";
        return;
    }

    if (!isStrongPassword(user.password)) {
        cout << "Weak password! Must contain uppercase, lowercase, digit, and special character.\n";
        return;
    }

    vector<User> users = readUsers();
    for (const User& u : users) {
        if (u.username == user.username || u.email == user.email) {
            cout << "Error: Username or Email already exists!\n";
            return;
        }
    }

    if (saveUser(user)) {
        cout << "Sign-up successful!\n";
    } else {
        cout << "Error: Failed to save user data.\n";
    }
}

// Login function with account lockout
void login() {
    string username, password;
    int attempts = 3;
    vector<User> users = readUsers(); // Read users once

    cout << "\n|------ Log In ------|\n";
    while (attempts--) {
        cout << "Enter Username: ";
        cin >> username;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
        cout << "Enter Password: ";
        getline(cin, password);

        for (const User& u : users) {
            if (u.username == username && u.password == password) {
                cout << "Login successful!\n";
                cout << "Welcome, " << username << "!\n";
                return;
            }
        }
        cout << "Incorrect credentials. Attempts left: " << attempts << endl;
    }
    cout << "Account locked due to too many failed attempts. Try again later.\n";
}

// Forgot Password function
void forgotPassword() {
    string email;
    cout << "\n|------ Forgot Password ------|\n";
    cout << "Enter your Email: ";
    cin >> email;

    vector<User> users = readUsers();
    for (const User& u : users) {
        if (u.email == email) {
            cout << "Your password is: " << u.password << endl;
            return;
        }
    }
    cout << "No account found with this email.\n";
}

// Main menu
int main() {
    int choice;
    while (true) {
        cout << "\n|------ Authentication System ------|\n";
        cout << "1. Sign Up\n2. Log In\n3. Forgot Password\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                cout << "Exiting system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}