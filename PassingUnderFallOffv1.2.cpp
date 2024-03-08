#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <filesystem>
namespace fs = std::filesystem;

// Function to parse INI file
std::unordered_map<std::string, int> parseIniFile(const std::string& filename) {
    std::unordered_map<std::string, int> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string valueStr;
            if (std::getline(iss, valueStr)) {
                try {
                    int value = std::stoi(valueStr);
                    data[key] = value;
                } catch (...) {
                    std::cerr << "Error parsing value: " << valueStr << std::endl;
                }
            }
        }
    }

    file.close();
    return data;
}

int main() {
    while (true) {
        // List variables
        int LF_scuff, LR_scuff, RF_scuff, RR_scuff;
        int LF_tread_remaining, LR_tread_remaining, RF_tread_remaining, RR_tread_remaining;
        int tread_start, laps;
        float LF_wear_rate, LR_wear_rate, RF_wear_rate, RR_wear_rate;

        // Starting tread for all tires
        tread_start = 100;

        // Ask user for desired age of tires in laps
        std::cout << "Enter laps: ";
        std::cin >> laps;

        // Ask user for the name of the .ini file
        std::string dataFile;
        std::cout << "Enter the name of the .ini file: ";
        std::cin >> dataFile;

        // Read data from INI file
        std::unordered_map<std::string, int> iniData = parseIniFile(dataFile);

        // Extract values from the INI data
        LF_scuff = iniData["LF_scuff"];
        LR_scuff = iniData["LR_scuff"];
        RF_scuff = iniData["RF_scuff"];
        RR_scuff = iniData["RR_scuff"];

        // Calculate tire wear rate for each tire
        LF_wear_rate = static_cast<float>(tread_start - LF_scuff) / 20;
        LR_wear_rate = static_cast<float>(tread_start - LR_scuff) / 20;
        RF_wear_rate = static_cast<float>(tread_start - RF_scuff) / 20;
        RR_wear_rate = static_cast<float>(tread_start - RR_scuff) / 20;

        // Tread remaining estimate based on inputs
        LF_tread_remaining = 100 - (LF_wear_rate * laps);
        LR_tread_remaining = 100 - (LR_wear_rate * laps);
        RF_tread_remaining = 100 - (RF_wear_rate * laps);
        RR_tread_remaining = 100 - (RR_wear_rate * laps);

        // Print output
        std::cout << "LF: " << LF_tread_remaining << std::endl;
        std::cout << "LR: " << LR_tread_remaining << std::endl;
        std::cout << "RF: " << RF_tread_remaining << std::endl;
        std::cout << "RR: " << RR_tread_remaining << std::endl;

        // Ask user to continue
        std::cout << "Continue? y/n: ";
        char user;
        std::cin >> user;

        if (user != 'y' && user != 'Y') {
            std::cout << "Exiting... " << std::endl;
            break;
        }
    }

    return 0;
}

