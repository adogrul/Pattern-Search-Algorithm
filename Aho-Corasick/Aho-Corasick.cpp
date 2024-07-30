#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "../../Headers/AhoCorasick.hpp"
//#include "../../Headers/Methods.hpp"
using namespace std;
namespace fs = std::filesystem;

  
int main() { 
    string csvPath;
    cout << "CSV dosyasının yolunu girin(Enter the CSV path): ";
    cin >> csvPath;

    string dirPath;
    cout << "Klasörün yolunu girin;(Enter the folder path): ";
    cin >> dirPath;

    vector<string> keywords;
    ifstream csvFile(csvPath);
    if (csvFile.is_open()) {
        string line;
        while (getline(csvFile, line)) {
            keywords.push_back(line);
        }
        csvFile.close();
    } else {
        cerr << "CSV dosyası açılamadı!(Can't open, check again)" << endl;
        return 1;
    }

    vector<string> directories = sub_dir_listFiles(dirPath);
    int k = keywords.size();

    for (const auto &entry : directories) {
        string filePath = entry;
        searchWords(keywords, k, filePath);
    }
  
    return 0; 
}
