#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <algorithm>

using namespace std;

unsigned char image[972][972*3];

int main() {
    ifstream file("image.raw", ios_base::in|ios_base::binary);
    ofstream fiddled("CANTTF.bit", ios_base::out|ios_base::binary);
    int bit = 0, byte = 0;
    
    for (int i = 972-1; i >= 0; i--)
        file.read((char*)image[i], 972*3);

    for (int i = 0; i < 972; i++)
        swap(image[0][i*3], image[0][i*3 + 2]);
    
    bit = 7;
    byte = 0;
    for (int i = 0; i < 972*3; i++) {
        byte = byte | ((image[0][i] & 1) << bit--);

        if (bit < 0) {
            //cout << (int)byte << " " << (char)byte << endl;
            cout << (char)byte;
            byte = 0;
            bit = 7;
        }
    }
    
    cout << endl;

    return 0;
}
