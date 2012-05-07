#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <array>

#define NUM_KEYS 11
#define INF 100000
#define VER 300
#define HOR 200
#define NOP 0
#define DIA 350
#define CAPS 10
#define HIT 100
#define TIMEOUT 500

using namespace std;

typedef int key;
typedef array<string, NUM_KEYS-1> key_associations_array;
typedef map<char, pair<key, int>> letter_associations_map;

template<int N>
void floyd(int weights[N][N]) {
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                weights[i][j] = min(weights[i][j], weights[i][k] + weights[k][j]);
}

void compute_letter_associations(const key_associations_array& key_associations, letter_associations_map& letter_associations) {
    for (int i = 0; i < key_associations.size(); i++)
        for (int j = 0; j < key_associations[i].size(); j++) {
            letter_associations[static_cast<char>(tolower(key_associations[i][j]))] = pair<key, int>(i, j + 1);
            letter_associations[static_cast<char>(toupper(key_associations[i][j]))] = pair<key, int>(i, j + 1);
        }
}

int main() {
    int cases;
    string line;
    letter_associations_map letter_associations;
    key_associations_array key_associations = {"0", " 1", "ABC2", "DEF3", "GHI4", "JKL5", "MNO6", "PQRS7", "TUV8", "WXYZ9"};
    int access_times[NUM_KEYS][NUM_KEYS] = {
        //        0    1    2    3    4    5    6    7    8    9    ^
        /*0*/   { NOP, INF, INF, INF, INF, INF, INF, DIA, VER, DIA, HOR },
        /*1*/   { INF, NOP, HOR, INF, VER, DIA, INF, INF, INF, INF, INF },
        /*2*/   { INF, HOR, NOP, HOR, DIA, VER, DIA, INF, INF, INF, INF },
        /*3*/   { INF, INF, HOR, NOP, INF, DIA, VER, INF, INF, INF, INF },
        /*4*/   { INF, VER, DIA, INF, NOP, HOR, INF, VER, DIA, INF, INF },
        /*5*/   { INF, DIA, VER, DIA, HOR, NOP, HOR, DIA, VER, DIA, INF },
        /*6*/   { INF, INF, DIA, VER, INF, HOR, NOP, INF, DIA, VER, INF },
        /*7*/   { DIA, INF, INF, INF, VER, DIA, INF, NOP, HOR, INF, INF },
        /*8*/   { VER, INF, INF, INF, DIA, VER, DIA, HOR, NOP, HOR, DIA },
        /*9*/   { DIA, INF, INF, INF, INF, DIA, VER, INF, HOR, NOP, VER },
        /*^*/   { HOR, INF, INF, INF, INF, INF, INF, INF, DIA, VER, NOP },
    };

    // Compute lookup tables
    floyd<NUM_KEYS>(access_times);
    compute_letter_associations(key_associations, letter_associations);

    getline(cin, line);
    istringstream(line) >> cases;

    while (cases--) {
        getline(cin, line);
        istringstream stream(line);
        int total = 0;
        bool uppercase = false;
        key current_key = 0, target_key;
       
        for (char letter : line) {
            // Handle upper/lowe case
            if (isalpha(letter)) {
                if ((isupper(letter) && !uppercase) || (islower(letter) && uppercase)) {
                    total += access_times[current_key][CAPS] + HIT;
                    current_key = CAPS;
                    uppercase = !uppercase;
                }
            }

            // Add finger movement time
            target_key = letter_associations[letter].first;
            
            if (target_key == current_key)
                total += TIMEOUT;
            else
                total += access_times[current_key][target_key];
            
            // Add hit count
            total += HIT*letter_associations[letter].second;
            current_key = target_key;
        }

        cout << total << endl;
    }

    return 0;
}
