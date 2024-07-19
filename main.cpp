#include<iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For exit()

using namespace std;

void displayWelcomeMessage() {
    cout << "\n\n";
    cout << "\033[1mWelcome to the Login and Registration System!\033[0m\n";
    cout << "---------------------------------------------\n";
}

bool isUserRegistered(const string& username) {
    ifstream file(username + ".txt");
    return file.is_open();
}

void registerUser() {
    string username, password;
    
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    // Open file in write mode to create a new file
    ofstream file(username + ".txt");
    if (file.is_open()) {
        file << password;
        file.close();
        cout << "\033[1mRegistration successful!\033[0m" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void loginUser() {
    string username, password, storedPassword;
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Open file in read mode to check the password
    ifstream file(username + ".txt");
    if (file.is_open()) {
        getline(file, storedPassword);
        file.close();

        if (storedPassword == password) {
            cout << "\033[1mLogin successful! You are welcome!\033[0m" << endl;
        } else {
            cout << "Invalid password!" << endl;
        }
    } else {
        cout << "Username not found!" << endl;
    }
}

void recoverPassword() {
    string username, oldPassword, newPassword, storedPassword;
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPassword;

    // Open file in read mode to check the old password
    ifstream file(username + ".txt");
    if (file.is_open()) {
        getline(file, storedPassword);
        file.close();

        if (storedPassword == oldPassword) {
            cout << "Enter new password: ";
            cin >> newPassword;

            // Open file in write mode to update the password
            ofstream file(username + ".txt");
            if (file.is_open()) {
                file << newPassword;
                file.close();
                cout << "\033[1mPassword updated successfully!\033[0m" << endl;
            } else {
                cout << "Unable to open file for writing." << endl;
            }
        } else {
            cout << "Old password is incorrect!" << endl;
        }
    } else {
        cout << "Username not found!" << endl;
    }
}

int main() {
    displayWelcomeMessage();

    int choice;

    cout << "1. Register\n2. Login\n3. Recover Password\nEnter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            registerUser();
            cout << "Please log in with your new credentials.\n";
            // Intentional fall-through to login after registration
        case 2:
            if (!isUserRegistered("dummy")) {
                cout << "No users registered. Please register first.\n";
                registerUser();
            }
            loginUser();
            break;
        case 3:
            recoverPassword();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    cout << "\033[1mThank you for using the system! Goodbye!\033[0m" << endl;

    exit(0); // Exit the program
}
