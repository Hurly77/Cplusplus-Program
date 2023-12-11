/*
 Author: Cameron Leverett
 Course: CS-210
 Date: 11/11/2023
*/
// Including necessary libraries for the functions to be used
#include <iostream> // For input and output operations
#include <iomanip> // Provides facilities to manipulate output formatting
#include <chrono> // For dealing with time
#include <thread> // This include might not be necessary unless you're using threads in the implementations
#include <limits> // Include this for std::numeric_limits, used for input validation
#include <ctime> // For dealing with time mktime and localtime

// It is generally not recommended to use namespace in header files as it can lead to name conflicts in large projects
using namespace std; // Make all standard library names available
using namespace chrono; // Make all chrono library names available

// Function to update the current time based on user's choice
void ChangeTime(int choice, system_clock::time_point& currentTime) {
  switch (choice) {
  case 1:
    currentTime += hours(1); // Add one hour
    break;
  case 2:
    currentTime += minutes(1); // Add one minute
    break;
  case 3:
    currentTime += seconds(1); // Add one second
    break;
  case 4:
    cout << "Exiting program..." << endl; // Exit the program
    break;
  default:
    cout << "Invalid choice. Please try again." << endl; // Handle invalid input
  }
}

// Function to print the user menu
void PrintMenu() {
  cout << "**************************\n";
  cout << "* 1 - Add One Hour       *\n";
  cout << "* 2 - Add One Minute     *\n";
  cout << "* 3 - Add One Second     *\n";
  cout << "* 4 - Exit Program       *\n";
  cout << "**************************\n";
}

// Function to display the current time in both 12-hour and 24-hour formats
void DisplayTime(chrono::system_clock::time_point currentTime) {
  time_t rawTime = chrono::system_clock::to_time_t(currentTime);

  // Using localtime_r for thread-safe conversion on UNIX-based systems
  struct tm timeInfo;
  localtime_r(&rawTime, &timeInfo); // Convert to tm struct in a thread-safe way

  cout << "\n\n\n";
  cout << "**************************  **************************\n";
  cout << "*     12-Hour Clock      *  *      24-Hour Clock     *\n";
  cout << "*       " << put_time(&timeInfo, "%I:%M:%S %p") << "      *  *         " << put_time(&timeInfo, "%H:%M:%S") << "       *\n";
  cout << "**************************  **************************\n";
}

// Main loop for getting user input and updating the time accordingly
void FeedbackLoop() {
  system_clock::time_point currentTime = system_clock::now(); // Get the current system time
  time_t rawTime;
  int hh, mm, ss; // Variables to store user input for time
  bool inputValid = false; // Flag to check if user input is valid

  int choice = 0; // Variable to store user menu choice

  // Loop to get valid initial time from user
  while (!inputValid) {
    cout << "Enter the current time in 24-hour format (HH MM SS): ";
    cin >> hh >> mm >> ss;

    // Input validation
    if (cin.fail()) {
      cout << "Invalid input. Please try again." << endl;
      cin.clear(); // Clear the error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to next newline
    }
    else if (hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 59) {
      cout << "Invalid input. Please try again." << endl;
    }
    else {
      inputValid = true; // Set flag to true if input is valid
    }
  }

  // Set the initial time based on user input
  struct tm timeInfo = { 0 };
  timeInfo.tm_hour = hh;
  timeInfo.tm_min = mm;
  timeInfo.tm_sec = ss;
  rawTime = mktime(&timeInfo); // Convert to time_t
  currentTime = system_clock::from_time_t(rawTime); // Convert to time_point

  // Loop to display menu and get user choice for updating the time
  do {
    DisplayTime(currentTime); // Display the current time
    PrintMenu(); // Display the menu options

    cout << "Enter your choice: ";
    cin >> choice;
    // Validate user choice and handle invalid input
    if (cin.fail() || choice < 1 || choice > 4) {
      cout << "Invalid choice. Please enter a number between 1 and 4" << endl;
      cin.clear(); // Clear the error flags
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip to next newline
      continue; // Skip the rest of the loop iteration
    }

    ChangeTime(choice, currentTime); // Update time based on choice
  } while (choice != 4); // Continue until user chooses to exit
}

int main() {
  FeedbackLoop();
  return 0;
}
