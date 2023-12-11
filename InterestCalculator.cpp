#include <iostream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;


class Report {
public:
  Report();
  Report(double initialInvestment, double monthlyDeposit, double annualInterest, int numYears);
  void DisplayReport(string title);
  double CalcMonthlyInterest(double balance, double PMT, double APR);
private:
  double initialInvestment;
  double monthlyDeposit;
  double annualInterest;
  int numYears;
  vector<ReportRow> reportRows;
  void InitReportRows();
};
// Constructor for the Report class with default values
Report::Report() {
  this->initialInvestment = 0.0;
  this->monthlyDeposit = 0.0;
  this->annualInterest = 0.0;
  this->numYears = 0;
  this->InitReportRows();  // Initialize the report rows
}

// Constructor for the Report class with custom values
Report::Report(double initialInvestment, double monthlyDeposit, double annualInterest, int numYears) {
  this->initialInvestment = initialInvestment;
  this->monthlyDeposit = monthlyDeposit;
  this->annualInterest = annualInterest;
  this->numYears = numYears;
  this->InitReportRows();  // Initialize the report rows
}

// Calculate monthly interest based on balance, monthly deposit, and annual interest rate
double Report::CalcMonthlyInterest(double balance, double PMT, double APR) {
  return (balance + PMT) * ((APR / 100.0) / 12.0);
}

// Initialize the report rows based on the provided parameters
void Report::InitReportRows() {
  double balance = this->initialInvestment;
  double accumulatedInterest = 0.0;

  // Loop through each year
  for (int i = 0; i < this->numYears; i++) {
    // Loop through each month in the year
    for (int j = 0; j < 12; j++) {
      // Calculate monthly interest and update balance and accumulated interest
      double interest = this->CalcMonthlyInterest(balance, this->monthlyDeposit, this->annualInterest);
      balance += this->monthlyDeposit + interest;
      accumulatedInterest += interest;
    }

    // Create a ReportRow object for the current year and add it to the reportRows vector
    ReportRow reportRow(i + 1, balance, accumulatedInterest);
    this->reportRows.push_back(reportRow);
    accumulatedInterest = 0.0;  // Reset accumulated interest for the next year
  }
}

// Display the financial report with a specified title
void Report::DisplayReport(string title) {
  cout << endl;

  // Display report title and header
  cout << setfill(' ') << setw(2) << ' ' << title << endl;
  cout << setfill('=') << setw(60) << '=' << endl;
  cout << setfill(' ');
  cout << setw(2) << "Year";
  cout << setw(20) << "Year End Balance";
  cout << setw(30) << "Year End Earned Interest" << endl;

  // Display a line of dashes as an underline
  cout << setfill('-') << setw(60) << '-' << endl;
  cout << setfill(' ');

  // Loop through each year and display the report data
  for (int i = 0; i < this->numYears; i++) {
    ReportRow currentRow = this->reportRows.at(i);
    double currentYearEndBalance = round(currentRow.GetYearEndBalance() * 100) / 100;
    double currentYearEndInterest = round(currentRow.GetYearEndInterest() * 100) / 100;
    stringstream ss;
    ss << fixed << setprecision(2) << currentYearEndBalance;

    string currentYearEndBalanceString = ss.str();
    int width = currentYearEndBalanceString.length();

    // Display year, year-end balance, and year-end interest for the current year
    cout << setw(2) << fixed << setprecision(2) << currentRow.GetYear();
    cout << setw(7) << fixed << setprecision(2) << '$' << currentYearEndBalance;
    cout << setw(22 - width) << fixed << setprecision(2) << '$' << currentYearEndInterest << endl;
    cout << endl;
  }

  // Display a line of dashes as a final underline
  cout << setfill('-') << setw(60) << '-' << endl;
}


class ReportRow {
public:
  ReportRow(int year, double yearEndBalance, double yearEndInterest);
  int GetYear() const;
  double GetYearEndBalance() const;
  double GetYearEndInterest() const;
private:
  int year;
  double yearEndBalance;
  double yearEndInterest;

};
// Constructor for the ReportRow class, initializes the year, yearEndBalance, and yearEndInterest
ReportRow::ReportRow(int year, double yearEndBalance, double yearEndInterest) {
  this->year = year;
  this->yearEndBalance = yearEndBalance;
  this->yearEndInterest = yearEndInterest;
}

// Get the year associated with this report row
int ReportRow::GetYear() const {
  return this->year;
}

// Get the year-end balance associated with this report row
double ReportRow::GetYearEndBalance() const {
  return this->yearEndBalance;
}

// Get the year-end interest associated with this report row
double ReportRow::GetYearEndInterest() const {
  return this->yearEndInterest;
}


class Application {
public:
  void start();
  int menu();
  void continueToReport();
private:
  Report reportWithMonthlyDeposits;
  Report reportWithoutMonthlyDeposits;
};
void Application::start() {
  char userInput;
  while (userInput != 'n') {
    int status = this->menu();
    if (status == 1) {
      continue;
    }
    this->continueToReport();

    // Display the menu and get user input
    cout << "Would you like to update the report? (y/n): ";
    cin >> (userInput);

    // Clear any remaining characters from the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();

    if (userInput != 'y') {
      break;
    }
  }
}

// Start function that collects user input and initializes report objects
int Application::menu() {
  double initialInvestment;
  double monthlyDeposit;
  double annualInterest;
  int numYears;

  // Display introductory messages for data input
  cout << "********************************\n";
  cout << "********** Data Input **********\n";

  // Prompt the user for initial investment amount
  cout << "Initial Investment Amount: ";
  if (!(cin >> initialInvestment)) {
    cout << "Invalid input. Please enter a numeric value." << endl;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return 1; // Return and ask for input again
  }

  // Prompt the user for monthly deposit amount
  cout << "Monthly Deposit: ";
  if (!(cin >> monthlyDeposit)) {
    cout << "Invalid input. Please enter a numeric value." << endl;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return 1; // Return and ask for input again
  }

  // Prompt the user for annual interest rate
  cout << "Annual Interest: ";
  if (!(cin >> annualInterest)) {
    cout << "Invalid input. Please enter a numeric value." << endl;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return 1; // Return and ask for input again
  }

  // Prompt the user for the number of years
  cout << "Number of years: ";
  if (!(cin >> numYears)) {
    cout << "Invalid input. Please enter a numeric value." << endl;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return 1; // Return and ask for input again
  }

  // Create Report objects with and without monthly deposits based on user input
  Report reportWithMonthlyDeposits(initialInvestment, monthlyDeposit, annualInterest, numYears);
  Report reportWithoutMonthlyDeposits(initialInvestment, 0, annualInterest, numYears);

  // Assign the created Report objects to the corresponding member variables of the Application class
  this->reportWithMonthlyDeposits = reportWithMonthlyDeposits;
  this->reportWithoutMonthlyDeposits = reportWithoutMonthlyDeposits;

  // Prompt the user to press any key to continue
  cout << "press any key to continue...\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
  cin.get(); // Wait for user input
  return 0;
}

// Function to continue to display financial reports and wait for user input
void Application::continueToReport() {
  // Display the financial reports for both scenarios
  this->reportWithoutMonthlyDeposits.DisplayReport("Balance and Interest Without Additional Monthly Deposits");
  this->reportWithMonthlyDeposits.DisplayReport("Balance and Interest With Additional Monthly Deposits");
}

int main() {
  Application app;
  app.start();

  return 0;
}
