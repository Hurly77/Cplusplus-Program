#include <iostream>
#include <iomanip>
#include "InventoryTracker.h"

using namespace std;

// Responsible for printing the menu Options to the User
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

/// User will be able to:
// 1. Look up a particular item;
// 2. Print the frequency of all item; I.E Onions 5
// 3. Print the frequency of all items in a histogram; I.E Onions: *****


// The InventoryTracker class should initialize a map<string, int> itemList
// Given that the BACKUP_FILE_NAME exists it will skip reading the file InventoryTracker_FILE_NAME and read the backup file
class InventoryTracker {
public:
  InventoryTracker(); // should run the InitializeData() function
  void GetItemCount(string itemWord);
  void PrintAllItemCounts();
  void PrintHistogram();

private:
  map<string, int> inventoryMap;
  const string INPUT_FILE_NAME = "CS210_Project_Three_Input_File.txt";
  const string BACKUP_FILE_NAME = "frequencies.dat"; // the backup for the InventoryTracker file that store the words and counts
  void ReadInputFileAndAddValueToInventoryMap();
  void WriteBackupFile(); // should write the itemList to the BACKUP_FILE_NAME
};

InventoryTracker::InventoryTracker() {
  // Read The Input File & The Values to The Inventor Map; Must happen before the backup file is written
  this->ReadInputFileAndAddValueToInventoryMap();

  // Write The Inventory Map to the BACKUP_FILE_NAME
  this->WriteBackupFile();
}

void InventoryTracker::GetItemCount(string itemWord) {
  // checks that the itemWord is in the inventoryMap
  // because if it is not then it will throw an error
  if (this->inventoryMap.count(itemWord) > 0) {
    cout << itemWord << " " << this->inventoryMap.at(itemWord) << endl;
  }
  else {
    cout << itemWord << " 0" << endl;
  }
}

void InventoryTracker::PrintAllItemCounts() {
  for (auto const& item : this->inventoryMap) {
    cout << item.first << " " << item.second << endl;
  }
}

void InventoryTracker::PrintHistogram() {
  for (auto const& item : this->inventoryMap) {
    string stars(item.second, '*');
    cout << item.first << " " << stars << endl;
  }
}


// ---------- Private Member Functions -----------------------------------------
void InventoryTracker::ReadInputFileAndAddValueToInventoryMap() {
  fstream fs;
  string word;

  fs.open(this->INPUT_FILE_NAME);
  fs >> word;
  // counts the the words and adds them to the inventoryMap
  while (!fs.fail()) {
    if (this->inventoryMap.count(word) > 0) {
      this->inventoryMap.at(word) += 1;
    }
    else {
      this->inventoryMap.emplace(word, 1);
    }
    fs >> word;
  }
  fs.close();
}
void InventoryTracker::WriteBackupFile() {
  ofstream ofs;

  ofs.open(this->BACKUP_FILE_NAME);
  if (ofs.fail()) {
    cout << "Failed to open file: " << this->BACKUP_FILE_NAME << endl;
    return;
  }

  if (ofs.is_open()) {
    for (auto const& item : this->inventoryMap) {
      ofs << item.first << " " << item.second << endl;
    }
  }

  ofs.close();
}



void PrintMenu() {
  cout << "=================================================" << endl;
  cout << setw(30) << setfill(' ') << "Corner Grocery" << endl;
  cout << "=================================================" << endl;
  cout << "[1]. Look up Item Count" << endl;
  cout << "[2]. Print All Item Counts" << endl;
  cout << "[3]. Print Histogram" << endl;
  cout << "[4]. Exit" << endl;
  cout << "-------------------------------------------------" << endl;
}

void MenuLoop() {
  InventoryTracker inventoryTracker;
  int userChoice = 0;
  string itemWord;
  // Assuming inventoryTracker is an instance of your class

  while (userChoice != 4) {
    PrintMenu();
    // Validates the user input is in fact a number
    if (!(cin >> userChoice)) {
      cout << "Please enter a valid number." << endl;
      cin.clear(); // Clear error state
      cin.ignore(1000, '\n'); // Ignore invalid input
      continue; // Continue to the next iteration of the loop
    }

    switch (userChoice) {
    case 1:
      cout << "Enter the item you want to look up: ";
      cin >> itemWord;
      inventoryTracker.GetItemCount(itemWord);
      break;
    case 2:
      inventoryTracker.PrintAllItemCounts();
      break;
    case 3:
      inventoryTracker.PrintHistogram();
      break;
    case 4:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }

    cin.ignore(1000, '\n'); // Clear the buffer after each input
  }
}

int main() {
  MenuLoop();
  return 0;
}