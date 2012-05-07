#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int cases;
    string line;

    getline(cin, line);
    istringstream(line) >> cases;

    assert((1 <= cases) && (cases <= 30));

    for (int i = 0; i < cases; i++) {
        float width, height /*in inches*/, count, total_area, font_size /*in stitches*/, stitches = 0.0f;
        float horizontal_resolution, vertical_resolution /*in stitches*/;
        vector<string> words;
        string text;
        
        getline(cin, line);

        istringstream(line) >> width >> height >> count;
        assert((1 <= width) && (width <= 5000));
        assert((1 <= height) && (height <= 5000));
        assert((1 <= count) && (count <= 100));
        horizontal_resolution = width*count;
        vertical_resolution = height*count;
        font_size = max(horizontal_resolution, vertical_resolution); // Set biggest possible font size

        getline(cin, text);
        assert((1 <= text.length()) && (text.length() <= 5000));

        total_area = horizontal_resolution*vertical_resolution;

        // Split message into words
        istringstream tokenizer(text);

        while (tokenizer.good()) {
            string word;

            tokenizer >> word;
            words.push_back(word);
        }

        // Check word for invalid characters
        for (string word : words) {
            for (char letter : word)
                if (!isalnum(letter) && !ispunct(letter)) {
                    font_size = 0.0f;
                    break;
                }
        }

        while (font_size > 0.0f) {
            const float stitches_per_character = pow(font_size, 2.0f) / 2.0f;
            float required_area = 0.0f;

            stitches = 0.0f;

            // Compute a lower bound for required area, spaces not considered (inaccurate but fast)
            // Also compute required stitches
            for (string word : words) {
                required_area += static_cast<float>(word.length()) * font_size * font_size; 
                stitches += static_cast<float>(word.length()) * stitches_per_character;
            }

            // If the lower bound fits, then refine space calculation
            if (required_area <= total_area) {
                const float line_space = width*count;
                float line_space_used = 0.0f, vertical_space_used = font_size, horizontal_space_used = 0.0f;
                int line_words = 0;

                for (int i = 0; i < words.size(); i++) {
                    float word_width = (static_cast<float>(words[i].length()) * font_size);
                    float space_width = (i == (words.size() - 1)) ? 0.0f : font_size;
                    
                    if (line_space_used + word_width + space_width > line_space) { // Fits with a trailing space?
                        if (line_space_used + word_width > line_space) { // Fits without a trailing space?
                            vertical_space_used += font_size;
                            horizontal_space_used = max(line_space_used, horizontal_space_used);
                            
                            if (line_space_used == 0.0f) { // Bail out if a single word does not fit in a line
                                horizontal_space_used = horizontal_resolution + 1;
                                vertical_space_used = vertical_resolution + 1;
                                break;
                            }
                            else
                                i--;

                            line_space_used = 0.0f;
                        }
                        else {
                            line_space_used += word_width;
                        }
                    }
                    else {
                        line_space_used += word_width + space_width;
                    }
                }

                if ((horizontal_space_used <= horizontal_resolution) && (vertical_space_used <= vertical_resolution))
                    break;
            }
            
            font_size -= 1.0f;
        }

        cout << "Case #" << i + 1 << ": " << ceil(stitches / count) << endl;
    }

    return 0;
}
