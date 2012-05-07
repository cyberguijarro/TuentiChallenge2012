#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>

#define BIT(x, i) (x & (1ULL << i))
#define SET(x, i) x |= (1ULL << i)
#define CLR(x, i) x &= ~(1ULL << i)

using namespace std;

int population_count (uint64_t x) {
    int count = 0;

    for (int i = 0; i < 64; i++, x >>= 1)
        count += x & 1ULL;
    
    return count;
}

bool compute(uint64_t target, uint64_t& a, uint64_t& b, uint64_t position, bool carry, uint64_t limit) {
    bool result = false, allow_carry = (position != limit);

    if (position > limit)
        return true;

    if (BIT(target, position)) {
        if (carry) {
            SET(a, position);
            SET(b, position);

            if (allow_carry && compute(target, a, b, position+1, true, limit))
                result = true;
            else {
                CLR(a, position);
                CLR(b, position);

                if (compute(target, a, b, position+1, false, limit))
                    result = true;
            }
        }
        else {
            SET(a, position);
            CLR(b, position);

            if (compute(target, a, b, position+1, false, limit))
                result = true;
            else {
                CLR(a, position);
                SET(b, position);

                if (compute(target, a, b, position+1, false, limit))
                    result = true;
            }
        }
    }
    else {
        if (allow_carry && carry) {
            SET(a, position);
            CLR(b, position);

            if (compute(target, a, b, position+1, true, limit))
                result = true;
            else {
                CLR(a, position);
                SET(b, position);

                if (compute(target, a, b, position+1, true, limit))
                    result = true;
            }
        }
        else {
            SET(a, position);
            SET(b, position);

            if (allow_carry && compute(target, a, b, position+1, true, limit))
                result = true;
            else {
                CLR(a, position);
                CLR(b, position);

                if (compute(target, a, b, position+1, false, limit))
                    result = true;
            }
        }
    }
    
    return result;
}

int main() {
    int cases;
    string line;

    getline(cin, line);
    istringstream(line) >> cases;

    assert((1 <= cases) && (cases <= 2000));

    for (int i = 0; i < cases; i++) {
        getline(cin, line);
        uint64_t target, a = 0, b = 0, limit;

        istringstream(line) >> target;
        limit = log(target) / log(2);
        compute(target, a, b, 0, false, limit);
        cout << "Case #" << i+1 << ": " << population_count(a) + population_count(b) << endl;
    }

    return 0;
}
