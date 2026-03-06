#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// Preprocessing: O(m) time and space
void computeLPS(const string& pattern, vector<int>& lps) {
    int m = pattern.length();
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) len = lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
}

// Searching: O(n) time
int KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) return 0;

    vector<int> lps(m);
    computeLPS(pattern, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) { i++; j++; }
        if (j == m) return i - j;
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return -1;
}

int main() {
    ifstream file("e_digits.txt");
    string e_digits;
    
    cout << "Loading 100 million digits... Please wait." << endl;
    if (file >> e_digits) {
        file.close();
    } else {
        cout << "Error: Place e_digits.txt in the project folder." << endl;
        return 1;
    }

    string query;
    cout << "\n--- Euler Sequence Search UI ---" << endl;
    cout << "Enter the sequence to find (e.g., 01012005): ";
    cin >> query;

    // Start Search
    auto start = high_resolution_clock::now();
    int index = KMPSearch(e_digits, query);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\n--- Search Results ---" << endl;
    if(index != -1)
        cout << "Sequence " << query << " found at index: " << index << endl;
    else
        cout << "Sequence not found in the first 100M digits." << endl;

    cout << "Search completed in " << duration.count() << " microseconds." << endl;


    string name;
    cout << "Enter your full name: ";
    cin.ignore(); // Clear the buffer from previous cin
    getline(cin, name);

    string asciiName = "";
    for (char c : name) {
    
        asciiName += to_string((int)c);
    }
    
    cout << "\n--- ASCII Conversion ---" << endl;
    cout << "Your name in ASCII is: " << asciiName << endl;

    auto startName = high_resolution_clock::now();
    int nameIndex = KMPSearch(e_digits, asciiName);
    auto stopName = high_resolution_clock::now();
    auto durationName = duration_cast<microseconds>(stopName - startName);

    if(nameIndex != -1)
        cout << "Sequence located at index: " << nameIndex << endl;
    else
        cout << "Sequence not found in the first 1M digits." << endl;

    cout << "Search Time: " << durationName.count() << " microseconds" << endl;

    return 0;
 }
