#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    uint32_t cases;
    string line;
    ofstream logger("log.txt");

    cin >> cases;
    logger << cases << endl;

    while (cases--) {
        uint32_t races_per_day, kart_count, group_count, fuel = 0U, queue_head = 0U, driver_count;
        vector<uint32_t> groups;

        cin >> races_per_day >> kart_count >> group_count;
        logger << races_per_day << " " << kart_count << " " << group_count << endl;
        
        while (group_count--) {
            uint32_t group_size;

            cin >> group_size;
            logger << group_size << " ";
            groups.push_back(group_size);
        }

        driver_count = accumulate(groups.begin(), groups.end(), 0U);
        
        logger << endl;

        while (races_per_day--) {

            if (driver_count < kart_count)
                fuel += driver_count;
            else {
                uint32_t current_occupation = 0U, i = queue_head;
                
                while (current_occupation + groups[i] <= kart_count) {
                    current_occupation += groups[i];

                    i = (i + 1) % groups.size();

                    if (i == queue_head)
                        break;
                }
            
                queue_head = i;
                fuel += current_occupation;
            }
        }
        
        cout << fuel << endl;
    }

    return 0;
}
