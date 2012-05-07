#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

typedef map<int, vector<string>> word_rank_map;
typedef map<char, int> letter_rank_map;

int word_rank(const string& word, const letter_rank_map& letter_ranks) {
    int result = 0;

    for (char letter : word)
        result += letter_ranks.at(letter);

    return result;
}

bool are_words_equivalent(const string& a, const string& b) {
    bool result = true;
    
    if (a.length() == b.length()) {
        for (char letter : a)
            if (b.find(letter) == string::npos) {
                result = false;
                break;
            }

        if (result) {
            for (char letter : b)
                if (a.find(letter) == string::npos) {
                    result = false;
                    break;
                }
        }
    }
    else
        result = false;

    return result;
}

void compute_subsets(string input, vector<string>& result, int minimum_length) {
    if (input.length() > minimum_length) {
        for (int i = 0; i < input.length(); i++) {
            string temp = input;
            
            temp.erase(i, 1);

            if (find(result.begin(), result.end(), temp) == result.end())
                result.push_back(temp);

            compute_subsets(temp, result, minimum_length);
        }
    }
    else if (find(result.begin(), result.end(), input) == result.end())
        result.push_back(input);
}

int main() {
    string line, token;
    int cases;
    ifstream words("descrambler_wordlist.txt");
    ofstream logger("log.txt"); 
    word_rank_map word_ranks;
    letter_rank_map letter_ranks;

    letter_ranks['A'] = letter_ranks['E'] = letter_ranks['I'] = letter_ranks['L'] = 
    letter_ranks['N'] = letter_ranks['O'] = letter_ranks['R'] = letter_ranks['S'] = 
    letter_ranks['T'] = letter_ranks['U'] = 1;
    letter_ranks['D'] = letter_ranks['G'] = 2;
    letter_ranks['B'] = letter_ranks['C'] = letter_ranks['M'] = letter_ranks['P'] = 3;
    letter_ranks['F'] = letter_ranks['H'] = letter_ranks['V'] = letter_ranks['W'] = 
    letter_ranks['Y'] = 4;
    letter_ranks['K'] = 5;
    letter_ranks['J'] = letter_ranks['X'] = 8;
    letter_ranks['Q'] = letter_ranks['Z'] = 10;

    // Load words list
    while (words.good()) {
        string word;

        words >> word;
        word_ranks[word_rank(word, letter_ranks)].push_back(word);
    }

    cin >> cases;
    logger << cases << endl;

    for (int i = 0; i < cases; i++) {
        string rack, board;
        int max_rank = -1;

        cin >> rack >> board;
        logger << rack << " " << board << endl;

        assert((1 <= rack.length()) && (rack.length() <= 25));
        assert((1 <= board.length()) && (board.length() <= 25));

        word_rank_map candidates;

        for (int j = rack.length(); j > 1; j--) {
            vector<string> subsets;
            int subsets_max_rank = 0;

            logger << "generating subsets (" << j << ")... "; 
            compute_subsets(rack, subsets, j); // Compute all valid rack subsets
            logger << "done (" << subsets.size() << ")" << endl; 

            for (const string& subset : subsets) {
                for (char letter : board) { // Check all rack subsets in combination with each board word letter
                    string candidate = subset + letter;

                    for (const string& word : word_ranks[word_rank(candidate, letter_ranks)])
                        if (are_words_equivalent(word, candidate)) {
                            candidates[word_rank(word, letter_ranks)].push_back(word);
                            subsets_max_rank = max(subsets_max_rank, word_rank(word, letter_ranks));
                        }
                }
            }

            logger << "max subsets rank " << subsets_max_rank << endl;

            if (subsets_max_rank < max_rank)
                break;
            else
                max_rank = subsets_max_rank;
        }

        vector<string> top_rank_words = candidates.rbegin()->second;
        sort(top_rank_words.begin(), top_rank_words.end());
        cout << top_rank_words[0] << " " << word_rank(top_rank_words[0], letter_ranks) << endl;
    }

    return 0;
}
