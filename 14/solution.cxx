#include <iostream>
#include <string>
#include <bitset>
#include <map>

using namespace std;

int main() {
    map<unsigned long, unsigned char> translations;

    translations[1] = 0;
    translations[2] = 0;
    translations[3] = 3;
    translations[4] = 0;
    translations[5] = 5;
    translations[6] = 14;
    translations[7] = 7;
    translations[8] = 0;
    translations[9] = 9;
    translations[10] = 2;
    translations[11] = 7;
    translations[12] = 4;
    translations[13] = 7;
    translations[14] = 7;
    translations[15] = 7;
    translations[16] = 0;
    translations[17] = 9;
    translations[18] = 14;
    translations[19] = 11;
    translations[20] = 14;
    translations[21] = 13;
    translations[22] = 14;
    translations[23] = 14;
    translations[24] = 9;
    translations[25] = 9;
    translations[26] = 10;
    translations[27] = 9;
    translations[28] = 12;
    translations[29] = 9;
    translations[30] = 14;
    translations[31] = 7;
    translations[32] = 0;
    translations[33] = 5;
    translations[34] = 2;
    translations[35] = 11;
    translations[36] = 5;
    translations[37] = 5;
    translations[38] = 6;
    translations[39] = 5;
    translations[40] = 2;
    translations[41] = 1;
    translations[42] = 2;
    translations[43] = 2;
    translations[44] = 12;
    translations[45] = 5;
    translations[46] = 2;
    translations[47] = 7;
    translations[48] = 8;
    translations[49] = 11;
    translations[50] = 11;
    translations[51] = 11;
    translations[52] = 12;
    translations[53] = 5;
    translations[54] = 14;
    translations[55] = 11;
    translations[56] = 12;
    translations[57] = 9;
    translations[58] = 2;
    translations[59] = 11;
    translations[60] = 12;
    translations[61] = 12;
    translations[62] = 12;
    translations[63] = 15;
    translations[64] = 0;
    translations[65] = 3;
    translations[66] = 3;
    translations[67] = 3;
    translations[68] = 4;
    translations[69] = 13;
    translations[70] = 6;
    translations[71] = 3;
    translations[72] = 4;
    translations[73] = 1;
    translations[74] = 10;
    translations[75] = 3;
    translations[76] = 8;
    translations[77] = 4;
    translations[78] = 4;
    translations[79] = 7;
    translations[80] = 8;
    translations[81] = 11;
    translations[82] = 10;
    translations[83] = 3;
    translations[84] = 11;
    translations[85] = 11;
    translations[86] = 14;
    translations[87] = 13;
    translations[88] = 10;
    translations[89] = 9;
    translations[90] = 10;
    translations[91] = 10;
    translations[92] = 4;
    translations[93] = 13;
    translations[94] = 10;
    translations[95] = 15;
    translations[96] = 8;
    translations[97] = 1;
    translations[98] = 6;
    translations[99] = 3;
    translations[100] = 6;
    translations[101] = 5;
    translations[102] = 6;
    translations[103] = 6;
    translations[104] = 1;
    translations[105] = 1;
    translations[106] = 2;
    translations[107] = 1;
    translations[108] = 4;
    translations[109] = 1;
    translations[110] = 6;
    translations[111] = 15;
    translations[112] = 8;
    translations[113] = 8;
    translations[114] = 8;
    translations[115] = 11;
    translations[116] = 8;
    translations[117] = 13;
    translations[118] = 6;
    translations[119] = 15;
    translations[120] = 8;
    translations[121] = 1;
    translations[123] = 15;
    translations[124] = 12;
    translations[126] = 15;
    translations[127] = 15;

    while (cin.good()) {
        string line;

        getline(cin, line);

        if (cin.good()) {
            bitset<7> code;
            unsigned char letter;

            if ((line.length() % 7) != 0)
                cout << "Error!" << endl;
            else {
                string result;

                for (int i = 0; i < line.length(); i += 7) {
                    for (int j = 0; j < 7; j++)
                        code[6-j] = (line[i+j] == '1');

                    if (translations.count(code.to_ulong()) == 0) {
                        cout << endl << endl << code.to_ulong() << endl << endl;
                    }

                    if ((i % 2) == 0)
                        letter = translations[code.to_ulong()] << 4;
                    else {
                        letter |= translations[code.to_ulong()];
                        
                        if (!isprint(letter)) {
                            result.clear();
                            break;
                        }
                        else
                            result += letter;
                    }
                }

                if (result.empty())
                    cout << "Error!" << endl;
                else
                    cout << result << endl;
            }
        }
    }

    return 0;
}
