// TxtDataBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Data is saved in db.txt
// db structure:  Id:int Name:string Email:string
// One line per entry

#include <iostream>
#include <string>
#include <fstream>
#include <format>
using namespace std;



void getLineById();
void createEntry();
void getAllEntries();

int main()
{

    int clientInput = 0;

    string consoleStatement = "Commands:\n   0: Exit\n   1: List all entries\n   2: List entry by id\n   3: Create a new entry\n";

    do {
        cout << consoleStatement;
        cin >> clientInput;

        switch (clientInput) {
            case 1: getAllEntries();
                break;
            case 2: getLineById();
                break;
            case 3: createEntry();
                break;
            default:
                cout << "Unknown input, try again";
                break;
        }

    } while (clientInput != 0);

}


void getAllEntries() {
    
    ifstream db;
    db.open("db.txt");

    string line;
    
    while (std::getline(db, line)) {
        cout << line << "\n";
    }

    db.close();
}
 

void getLineById() {
    int idNum;
    string line;
    cout << "\nEnter Entry id: ";
    cin >> idNum;
    string idString = "Id:" + std::to_string(idNum);

    ifstream db;
    db.open("db.txt");

    while (std::getline(db, line)) {
        if (line.find(idString) != string::npos) {
            
            cout << "idString: " << idString << "\n";
            cout << line;
        }
    }
    cout << "\nFinished finding entry, closind DB file\n";
    db.close();
}

void createEntry() {
    std::string dbTemplate = "Id:{} Name:{} Email:{}";
    int lastMaxId = 0; // Initialize to 0 to consider the case when there are no entries.
    std::fstream db;
    db.open("db.txt", std::ios::in | std::ios::out | std::ios::ate);

    std::string newId, newName, newEmail;

    std::cout << "\nEnter Name: ";
    std::cin >> newName;
    std::cout << "\nEnter Email: ";
    std::cin >> newEmail;

    if (db.is_open()) {
        db.seekg(0, std::ios_base::beg); // Move to the beginning of the file

        std::string line;
        while (std::getline(db, line)) {
            size_t idStartPos = line.find("Id:");
            if (idStartPos != std::string::npos) {
                size_t idEndPos = line.find(" ", idStartPos);
                if (idEndPos != std::string::npos) {
                    int id = std::stoi(line.substr(idStartPos + 3, idEndPos - idStartPos - 3));
                    if (id > lastMaxId) {
                        lastMaxId = id;
                    }
                }
            }
        }

        // Calculate the new ID
        newId = std::to_string(lastMaxId + 1);

        db.close();
        db.open("db.txt", std::ios::out | std::ios::app);

        // Write the new entry to the file
        std::string newEntry = "\nId:" + newId + " Name:" + newName + " Email:" + newEmail;
        db << newEntry;
        std::cout << "New entry added: " << newEntry;

        db.close();
    }
    else {
        std::cout << "Error opening file: db.txt" << std::endl;
    }
}