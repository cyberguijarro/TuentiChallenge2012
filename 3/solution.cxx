#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>

#define TRADING_FREQUENCY 100

using namespace std;

struct entry { int value, position; };

int main() {
    string line;
    vector<entry> samples;
    int position = 0, sample;
    bool swap = true;

    while (cin.good()) {
        getline(cin, line);

        if (cin.good()) {
            istringstream(line) >> sample;
            samples.push_back(entry { sample, position++ });
        }
    }

    sort(samples.begin(), samples.end(), [](const entry& a, const entry& b) { return a.value < b.value; });
    auto _end = samples.end() - 1, _start = samples.begin();

    while (true) {
        if (_end->position > _start->position)
            break;
        else if (swap)
            _end--;
        else if (!swap)
            _start++;

        swap = !swap;
    }
    
    cout << _start->position*TRADING_FREQUENCY << " " << _end->position*TRADING_FREQUENCY << " " << _end->value - _start->value << endl;

    return 0;
}
