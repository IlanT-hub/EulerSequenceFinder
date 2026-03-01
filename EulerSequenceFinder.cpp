#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void computeLPS(string pattern, m, int lps[]){
    int len = 0
    lps[0] = 0; // lps[0] is always 0
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
 
int KMPSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) return 0;

    int* lps = new int[m]; 
    computeLPS(pattern, m, lps);

    int i = 0, j = 0;
    int result = -1;
    while (i < n) {
        if (pattern[j] == text[i]) { i++; j++; }
        if (j == m) {
            result = i - j;
            break; 
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    delete[] lps; 
    return result;
}

int main() {
    ifstream file("e_digits.txt");
    string e_digits;
    if (file.is_open()) {
        getline(file, e_digits);
        file.close();
    } else {
        cout << "Error: Place e_digits.txt in the project folder." << endl;
        return 1;
    }

    string name = "Ilan Tchachoua";
    string bday = "01011997"; // Your birthday [cite: 5]

    cout << "--- Euler Sequence Finder ---" << endl;
    
    // Birthday Search
    int bdayIndex = KMPSearch(e_digits, bday);
    if(bdayIndex != -1)
        cout << "In Euler's number, your birthday is located here: " << bdayIndex << endl;
    else
        cout << "Birthday not found in this digit set." << endl;

    // ASCII Transversion [cite: 4]
    string asciiName = "";
    for (char c : name) {
        asciiName += to_string((int)c);
    }
    
    int nameIndex = KMPSearch(e_digits, asciiName);
    cout << "For name in ASCII transversion, your name is: " << asciiName << endl;
    if(nameIndex != -1)
        cout << "Your name is located here: " << nameIndex << endl;

    return 0;
}