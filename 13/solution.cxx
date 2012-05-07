#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <cstdint>
#include <cassert>

using namespace std;

uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return (a * b) / gcd(a, b);
}

uint64_t new_position(uint64_t x, uint64_t deck_size, uint64_t cut_point, uint64_t residual_area_start, uint64_t residual_area_end, int balance) {
    if ((x >= residual_area_start) && (x < residual_area_end)) {
        if (balance < 0)
            return (deck_size - cut_point) * 2 + (residual_area_end - x - 1);
        else if (balance > 0)
            return cut_point * 2 + residual_area_end - x - 1;
    } else {
        if (x >= cut_point)
            return (deck_size - x)*2 - 1;
        else if (x < cut_point)
            return (cut_point - x - 1)*2;
    }
}

int main() {
    ofstream logger("log.txt");
    string line;
    int cases;

    getline(cin, line);
    istringstream(line) >> cases;
    assert((1 <= cases) && (cases <= 100));

    for (int c = 1; c <= cases; c++) {
        uint64_t deck_size, cut_point, residual_area_start, residual_area_end, balance;

        getline(cin, line);
        istringstream(line) >> deck_size >> cut_point;
        assert((1 <= deck_size) && (deck_size <= 1000000));
        assert((1 <= cut_point) && (cut_point <= deck_size));

        if (cut_point > (deck_size / 2)) {
            residual_area_start = 0;
            residual_area_end = deck_size - ((deck_size - cut_point)*2);
            balance = -1;
        }
        else if (cut_point < (deck_size / 2)) {
            residual_area_start = cut_point;
            residual_area_end = deck_size - cut_point;
            balance = 1;
        }
        else {
            residual_area_start = 0;
            residual_area_end = 0;
            balance = 0;
        }

        logger << deck_size << endl;
        logger << cut_point << endl;
        logger << residual_area_start << endl;
        logger << residual_area_end << endl;

        set<uint64_t> cycled;
        uint64_t result = 1;

        for (uint64_t i = 0; i < deck_size; i++) {
            uint64_t current = i, length = 0;

            if (cycled.count(i) == 0) {
                do {
                    cycled.insert(current);

                    current = new_position(current, deck_size, cut_point, residual_area_start, residual_area_end, balance);
                    length++;
                } while(i != current);
            
                logger << "Cycle for: " << i << ": " << length << endl;
                result = lcm(result, length);
            }
        }

        cout << "Case #" << c << ": " << result << endl; 
    }

    return 0;
}
