#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// File where user data will be stored
const string DATABASE_FILE = "database.txt";

// User struct to hold username and password
struct User {
    string username;
    string password;
};

// Function to register a new user
void registerUser() {
    User newUser;

    cout << "Enter username: ";
    cin >> newUser.username;

    cout << "Enter password: ";
    cin >> newUser.password;

    ofstream outFile(DATABASE_FILE, ios::app); // Open file in append mode
    if (!outFile) {
        cerr << "Error: Could not open database file." << endl;
        return;
    }

    // Write user data to the file
    outFile << newUser.username << " " << newUser.password << endl;
    outFile.close();

    cout << "Registration successful!" << endl;
}

// Function to validate login
bool loginUser(const string& username, const string& password) {
    ifstream inFile(DATABASE_FILE);
    if (!inFile) {
        cerr << "Error: Could not open database file." << endl;
        return false;
    }

    string storedUsername, storedPassword;
    bool found = false;
    
    // Loop through each line in the file
    while (inFile >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            found = true; // Login successful
            break;
        }
    }

    inFile.close();
    return found;
}

int main() {
    int choice;

    do {
        cout << "\n1. Register\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (loginUser(username, password)) {
                    cout << "Login successful!" << endl;
                } else {
                    cout << "Login failed. Invalid username or password." << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}