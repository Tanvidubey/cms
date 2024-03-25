#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class Contact {
public:
    int id;
    string name;
    string phone_number;

    Contact(int i, string n, string num) : id(i), name(n), phone_number(num) {}
};

class CMS {
private:
    vector<Contact> contacts;
    const string db = "contacts_db.txt";

public:
    CMS() {
        load();
    }

    bool isValidInput(const string& input) {
    if (input.length() == 10) {
        for (char digit : input) {
            if (!isdigit(digit)) {
                return false; // Non-numeric character found
            }
            else{
                int first_digit = stoll(input);
                if(first_digit<6000000000){
                return false;
                }
            }
        }
        return true; // All characters are digits
    }
    return false; // Incorrect length
}

string getUserContact() {
    string userInput;

    do {
        cout << "Enter a 10-digit numeric value: ";
        cin >> userInput;

        if (!isValidInput(userInput)) {
            cout << "Invalid input. Please enter a 10-digit numeric value.\n";
        }

    } while (!isValidInput(userInput));

    return userInput;
}

    void add() {
        int id;
        string name, phone_number;


        bool isUnique;
        do {
            isUnique = true;

            cout << "Enter ID: ";
            cin >> id;

            for (const auto &contact : contacts) {
                if (contact.id == id) {
                    cout << "ID already exists. Please enter a unique ID.\n";
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Phone Number: ";
        phone_number = getUserContact();

        Contact New(id, name, phone_number);
        contacts.push_back(New);
        save();

        cout << "Contact added successfully!\n";
    }

    void display() {
        if (contacts.empty()) {
            cout << "No contacts found.\n";
        } else {
            cout << "Contacts:\n";
            for (const auto &contact : contacts) {
                cout << "ID: " << contact.id << "\tName: " << contact.name << "\tPhone Number: " << contact.phone_number << "\n";
            }
        }
    }

    void Search() {
        int s;
        cout << "Enter ID to search: ";
        cin >> s;

        for (const auto &contact : contacts) {
            if (contact.id == s) {
                cout << "Contact found:\n";
                cout << "ID: " << contact.id << "\tName: " << contact.name << "\tPhone Number: " << contact.phone_number << "\n";
                return;
            }
        }

        cout << "Contact not found.\n";
    }

    void modify() {
        int m;
        cout << "Enter ID of the contact to modify: ";
        cin >> m;

        for (auto &contact : contacts) {
            if (contact.id == m) {
                cout << "Enter new Name: ";
                cin >> contact.name;
                cout << "Enter new Phone Number: ";
                contact.phone_number = getUserContact();

                cout << "Contact modified successfully!\n";
                save();
                return;
            }
        }

        cout << "Contact not found.\n";
    }

    void Delete() {
        int d;
        cout << "Enter ID to delete: ";
        cin >> d;

        auto it = find_if(contacts.begin(), contacts.end(), [d](const Contact &c) { return c.id == d; });

        if (it != contacts.end()) {
            contacts.erase(it);
            save();
            cout << "Contact deleted successfully!\n";
        } else {
            cout << "Contact not found.\n";
        }
    }

    void load() {
        ifstream inFile(db);

        if (inFile.is_open()) {
            contacts.clear();
            int id;
            string name, phone_number;

            while (inFile >> id >> name >> phone_number) {
                Contact loaded(id, name, phone_number);
                contacts.push_back(loaded);
            }

            inFile.close();
        }
    }

    void save() {
        ofstream outFile(db);

        if (outFile.is_open()) {
            for (const auto &contact : contacts) {
                outFile << contact.id << ' ' << contact.name << ' ' << contact.phone_number << '\n';
            }

            outFile.close();
        }
    }
};

int main() {
    CMS cms;
    int choice;

    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Modify Contact\n";
        cout << "5. Delete Contact\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cms.add(); break;
            case 2: cms.display(); break;
            case 3: cms.Search(); break;
            case 4: cms.modify(); break;
            case 5: cms.Delete(); break;
            case 0: cout << "Exiting the program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
