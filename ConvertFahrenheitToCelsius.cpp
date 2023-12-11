#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Definition of a structure to store city temperature data.
struct CityTemp {
  string city;   // Name of the city.
  double tempF;  // Temperature in Fahrenheit.
  double tempC;  // Temperature in Celsius.

  // Constructor to initialize a CityTemp object.
  CityTemp(string city, double tempF) {
    this->city = city;
    this->tempF = tempF;
    this->tempC = FahrenheitToCelsius(tempF);
  };

  // Function to convert Fahrenheit to Celsius.
  double FahrenheitToCelsius(double tempF) {
    double temperatureC = (tempF - 32.0) * (5.0 / 9.0);
    return temperatureC;
  };

  // Function to format the city temperature data for output.
  string OutputCityTempC() {
    string outText = city + " " + to_string(tempC) + "\n";
    return outText;
  };
};

// Function to read city temperature data from a file.
int readFileTempF(string filename, vector<CityTemp>& cityTempVector) {
  ifstream fs;
  string file;

  fs.open(filename);
  if (!fs.is_open()) {
    return 1;  // Return 1 if file cannot be opened.
  }

  // Read city names and temperatures from file.
  while (!fs.fail()) {
    string city;
    double tempF;
    fs >> city >> tempF;

    CityTemp cityTemp(city, tempF);
    cityTempVector.push_back(cityTemp);
  }

  fs.close();
  return 0;
}

// Function to write city temperature data to a file in Celsius.
int writeFileTempC(string filename, vector<CityTemp>& cityTempVector) {
  ofstream outFS;
  outFS.open(filename);
  if (!outFS.is_open()) {
    return 1;  // Return 1 if file cannot be opened.
  }

  // Write the city temperatures in Celsius to the file.
  for (int i = 0; i < cityTempVector.size() - 1; i++) {
    outFS << cityTempVector.at(i).OutputCityTempC();
  }

  outFS.close();
  return 0;
}

// Main function.
int main() {
  int status;
  const string INPUT_FILE_NAME = "FahrenheitTemperature.txt";
  const string OUTPUT_FILE_NAME = "CelsiusTemperature.txt";
  vector<CityTemp> cityTempVector;

  // Read data from input file.
  status = readFileTempF(INPUT_FILE_NAME, cityTempVector);
  if (status >= 1) {
    cout << "Error opening file: " << INPUT_FILE_NAME << endl;
    return 1;  // Exit if there is an error opening the input file.
  }

  // Write data to output file.
  status = writeFileTempC(OUTPUT_FILE_NAME, cityTempVector);
  if (status >= 1) {
    cout << "Error: when opening file: " << OUTPUT_FILE_NAME << endl;
    return 1;  // Exit if there is an error opening the output file.
  }

  return 0;
}