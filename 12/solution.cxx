#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

string add_mod(const string& a, const string& b, const string& c, const string& d) {
    map<char, int> values;
    map<int, char> inverse;
    string result;

    values['0'] = 0; values['1'] = 1; values['2'] = 2; values['3'] = 3;
    values['4'] = 4; values['5'] = 5; values['6'] = 6; values['7'] = 7;
    values['8'] = 8; values['9'] = 9; values['a'] = 10; values['b'] = 11;
    values['c'] = 12; values['d'] = 13; values['e'] = 14; values['f'] = 15;
    values['A'] = 10; values['B'] = 11;
    values['C'] = 12; values['D'] = 13; values['E'] = 14; values['F'] = 15;
    
    inverse[0] = '0'; inverse[1] = '1'; inverse[2] = '2'; inverse[3] = '3';
    inverse[4] = '4'; inverse[5] = '5'; inverse[6] = '6'; inverse[7] = '7';
    inverse[8] = '8'; inverse[9] = '9'; inverse[10] = 'a'; inverse[11] = 'b';
    inverse[12] = 'c'; inverse[13] = 'd'; inverse[14] = 'e'; inverse[15] = 'f';

    for (int i = a.length() - 1; i >= 0; i--) {
        int r = values[a[i]] + values[b[i]] + values[c[i]] + values[d[i]];
        
        result.insert(result.begin(), inverse[r % 16]);
    }

    return result;
}

int main() {
    const string key1("a541714a17804ac281e6ddda5b707952"); // Embedded in comments section
    const string key2("ed8ce15da9b7b5e2ee70634cc235e363"); // QR code
    const string key3("62cd275989e78ee56a81f0265a87562e"); // LSB of the first line bytes (RGB order)
    string input;

    cin >> input;
    cout << add_mod(key1, key2, key3, input) << endl;

    return 0;
}
