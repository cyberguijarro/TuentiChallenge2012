#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
#include <unistd.h>

using namespace std;

typedef vector<string> subcode_vector;
typedef map<int, char> alphabet_map;
typedef map<char, int> inverse_alphabet_map;
typedef vector<int> positions_map;

class directed_graph : public vector<vector<bool>> {
public:
    directed_graph(int nodes) : vector<vector<bool>>(nodes) {
        for (int i = 0; i < nodes; i++)
            at(i).resize(nodes, false);
    }
    
    vector<int> get_incoming_dependencies(int node) const {
        vector<int> result;

        for (int i = 0; i < size(); i++)
            if (at(i).at(node))
                result.push_back(i);

        return result;
    }

    vector<int> get_outgoing_dependencies(int node) const {
        vector<int> result;

        for (int i = 0; i < size(); i++)
            if (at(node).at(i))
                result.push_back(i);

        return result;
    }

    int get_entry_node() const {
        int result = -1;

        for (int i = 0; i < size(); i++)
            if (get_incoming_dependencies(i).size() == 0) {
                result = i;
                break;
            }

        return result;
    }
    
    int get_exit_node() const {
        int result = -1;

        for (int i = 0; i < size(); i++)
            if (get_outgoing_dependencies(i).size() == 0) {
                result = i;
                break;
            }

        return result;
    }
};

positions_map compute_positions(const string& code) {
    positions_map result(256);

    for (int i = 0; i < code.length(); i++)
        result[code[i]] = i;

    return result;    
}

bool check(const directed_graph& graph, const string& combination, inverse_alphabet_map& inverse_alphabet, alphabet_map& alphabet) {
    positions_map positions = compute_positions(combination);

    for (int i = 0; i < combination.length(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (graph[inverse_alphabet[combination[i]]][j])
                if (positions[alphabet[j]] <= i)
                    return false;
        }
    }
    
    return true;
}

void compute_candidates(directed_graph& graph, alphabet_map& alphabet, inverse_alphabet_map& inverse_alphabet, int entry_node, int exit_node, string current, subcode_vector& results) {
    vector<int> candidates;

    // Select candidates and prune invalid paths
    for (int target : graph.get_outgoing_dependencies(entry_node)) {
        if (graph.get_incoming_dependencies(target).size() > 1)
            graph[entry_node][target] = false;
        else
            candidates.push_back(target);
    }

    switch (candidates.size()) {
    case 0: // End of the line, we have a candidate
        results.push_back(current);
        break;
    case 1: // There's only one way to go from here
        current += alphabet[candidates[0]];
        compute_candidates(graph, alphabet, inverse_alphabet, candidates[0], exit_node, current, results);
        break;
    default: // Multiple paths area available, check everyone of them assuming that each one is the only one possible
        for (int candidate : candidates) {
            directed_graph temp = graph;
           
            // Create artificial relations for the sake of simulation
            for (int _candidate : candidates) {
                if (_candidate != candidate)
                    temp[_candidate][candidate] = true;
            }
        
            compute_candidates(temp, alphabet, inverse_alphabet, entry_node, exit_node, current, results);
        }
        break;
    }
}


int main() {
    string line, combination;
    subcode_vector subcodes;
    alphabet_map alphabet;
    inverse_alphabet_map inverse_alphabet;
    ofstream logger("log.txt");

    while (cin.good()) {
        getline(cin, line);

        if (cin.good()) {
            subcodes.push_back(line);
            logger << line << endl;
        }
    }

    // Build alphabet lookup tables
    int i = 0;
    for (string subcode : subcodes) {
        for (char letter : subcode)
            if (!inverse_alphabet.count(letter)) {
                alphabet[i] = letter;
                inverse_alphabet[letter] = i++;
            }
    }

    // Generate relations graph
    directed_graph graph(inverse_alphabet.size());

    for (string subcode : subcodes) {
        for (int i = 0; i < subcode.size() - 1; i++)
            graph[inverse_alphabet[subcode[i]]][inverse_alphabet[subcode[i+1]]] = true;
    }

    string current(1, alphabet[graph.get_entry_node()]);
    subcode_vector results;

    compute_candidates(graph, alphabet, inverse_alphabet, graph.get_entry_node(), graph.get_exit_node(), current, results);
    sort(results.begin(), results.end());

    for (string result : results)
        if (check(graph, result, inverse_alphabet, alphabet)) {
            logger << "sending: " << result << endl;
            cout << result << endl;
        }
        else
            logger << "discarding: " << result << endl;

    return 0;
}
