#include <iostream>
#include <fstream>
using namespace std;

class AUTH {
    string username, email, password;
    fstream file;

public:
    void login();
    void signup();
    void forgotPass();
};

void AUTH::signup() {
    cout << "\n|------------------ Sign Up --------------------|\n";

    cin.ignore();
    cout << "Enter your Username: ";
    getline(cin, username);

    cout << "Enter your Email: ";
    getline(cin, email);

    cout << "Enter your Password: ";
    getline(cin, password);

    file.open("signUpData.txt", ios::out | ios::app);
    if (!file) {
        cout << "Error opening file!";
        return;
    }

    file << username << "*" << email << "*" << password << "\n";
    file.close();
    cout << "Sign-up successful!\n";
}

void AUTH::login() {
    string searchName, searchPass;
    bool found = false;

    cout << "\n|------------------ Log In --------------------|\n";

    cin.ignore();
    cout << "Enter your Username: ";
    getline(cin, searchName);

    cout << "Enter your Password: ";
    getline(cin, searchPass);

    file.open("signUpData.txt", ios::in);
    if (!file) {
        cout << "No user data found! Please sign up first.\n";
        return;
    }

    while (getline(file, username, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
        if (username == searchName && password == searchPass) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        cout << "Account Login Successful!\n";
        cout << "Username: " << username << "\nEmail: " << email << "\n";
    } else {
        cout << "Incorrect Username or Password!\n";
    }
}

void AUTH::forgotPass() {
    string searchEmail;
    bool found = false;

    cout << "\n|---------------- Forgot Password ----------------|\n";

    cin.ignore();
    cout << "Enter your registered Email: ";
    getline(cin, searchEmail);

    file.open("signUpData.txt", ios::in);
    if (!file) {
        cout << "No user data found! Please sign up first.\n";
        return;
    }

    while (getline(file, username, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
        if (email == searchEmail) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        cout << "Your registered password is: " << password << "\n";
    } else {
        cout << "Email not found in records!\n";
    }
}

int main() {
    AUTH auth;
    int choice;

    while (true) {
        cout << "\n|----------- Authentication System -----------|\n";
        cout << "1. Log In\n";
        cout << "2. Sign Up\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            auth.login();
            break;
        case 2:
            auth.signup();
            break;
        case 3:
            auth.forgotPass();
            break;
        case 4:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}
