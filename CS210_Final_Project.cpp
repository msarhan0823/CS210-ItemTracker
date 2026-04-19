/*
 * Matthew J. Sarhan
 * CS-210 - Programming languages
 * Project Three - FINAL
 * Date: 04/18/2026
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

class ItemTracker {
private:
    map<string, int> itemList;
    string inputFile;
    string outputFile;

    // reads the grocery items from the input file
    void ReadFile() {
        ifstream inFS(inputFile);
        string item;

        if (!inFS.is_open()) {
            cout << "Error opening input file." << endl;
            return;
        }

        while (inFS >> item) {
            itemList[item]++;
        }

        inFS.close();
    }

    // creates the backup file
    void WriteBackupFile() {
        ofstream outFS(outputFile);

        if (!outFS.is_open()) {
            cout << "Error creating backup file." << endl;
            return;
        }

        for (auto item = itemList.begin(); item != itemList.end(); ++item) {
            outFS << item->first << " " << item->second << endl;
        }

        outFS.close();
    }

    // makes searching easier if user types lowercase
    string MakeLower(string word) const {
        for (int i = 0; i < word.size(); ++i) {
            word[i] = tolower(word[i]);
        }
        return word;
    }

public:
    ItemTracker(string inFile, string outFile) {
        inputFile = inFile;
        outputFile = outFile;
        ReadFile();
        WriteBackupFile();
    }

    int SearchItem(string itemName) const {
        string searchWord = MakeLower(itemName);

        for (auto item = itemList.begin(); item != itemList.end(); ++item) {
            if (MakeLower(item->first) == searchWord) {
                return item->second;
            }
        }

        return 0;
    }

    void PrintFrequencies() const {
        for (auto item = itemList.begin(); item != itemList.end(); ++item) {
            cout << item->first << " " << item->second << endl;
        }
    }

    void PrintHistogram() const {
        for (auto item = itemList.begin(); item != itemList.end(); ++item) {
            cout << item->first << " ";
            for (int i = 0; i < item->second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    bool FileLoaded() const {
        return !itemList.empty();
    }
};

void PrintMenu() {
    cout << endl;
    cout << "Corner Grocer Menu" << endl;
    cout << "1. Search for item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

int GetChoice() {
    int choice;

    while (true) {
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 4: ";
        }
        else if (choice < 1 || choice > 4) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 4: ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");

    if (!tracker.FileLoaded()) {
        cout << "No data was loaded. Program ending." << endl;
        return 1;
    }

    int choice;
    string itemToSearch;

    do {
        PrintMenu();
        choice = GetChoice();

        switch (choice) {
        case 1:
            cout << "Enter item to search for: ";
            getline(cin, itemToSearch);
            cout << itemToSearch << " was purchased "
                << tracker.SearchItem(itemToSearch)
                << " time(s)." << endl;
            break;

        case 2:
            cout << endl;
            tracker.PrintFrequencies();
            break;

        case 3:
            cout << endl;
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Goodbye." << endl;
            break;

        default:
            cout << "Invalid option." << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}