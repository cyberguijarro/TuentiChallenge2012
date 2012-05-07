#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>
#include <map>
#include <vector>
#include <openssl/md5.h>

using namespace std;

typedef map<char, string> transformations_map;
typedef vector<transformations_map> series_vector;

string evolve(char a, const series_vector& series) {
    string current(1, a);

    for (const transformations_map& transformations : series) {
        string result;

        for (char letter : current)
            if (transformations.count(letter))
                result += transformations.at(letter);
            else
                result += letter;

        current.swap(result);
    }

    return current;
}

int main() {
    string line, people_queue;
    series_vector series;
    ofstream logger("log.txt"); 
    MD5_CTX md5_context;
    unsigned char hash[MD5_DIGEST_LENGTH];
    
    getline(cin, people_queue);
    assert(people_queue.length() <= 100000);
    logger << people_queue << endl;

    while (cin.good()) { // Read each transformation sequence
        transformations_map transformations;
        string transformation;
        
        getline(cin, line);
        logger << line << endl;

        // Read each transfomation
        istringstream stream(line);

        while (stream.good()) {
            getline(stream, transformation, ',');
            
            if (!transformation.empty()) {
                transformations[transformation[0]] = transformation.substr(3, string::npos);
                assert(transformations[transformation[0]].length() <= 10);
                logger << transformation[0] << "->" << transformation.substr(3, string::npos) << endl;
            }
        }
        
        assert(transformations.size() <= 52);
        series.push_back(transformations);
        assert(series.size() <= 15);
    }

    MD5_Init(&md5_context);
    
    for (int i = 0; i < people_queue.length(); i++) {
        string chunk = evolve(people_queue[i], series);
        
        MD5_Update(&md5_context, chunk.c_str(), chunk.length());

        if (i % 1000 == 0)
            logger << i << endl;
    }
    
    MD5_Final(hash, &md5_context);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);

    return 0;
}
