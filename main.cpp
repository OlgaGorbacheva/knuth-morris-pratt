#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <vector>

void prefix_function(std::string const text, std::vector<unsigned int> &pi) {
    pi.resize(text.length(), 0);
    for (unsigned int i = 1; i < text.length(); i++) {
        unsigned int j = pi[i - 1];
        while ((j > 0) && (text[i] != text[j]))
            j = pi[j - 1];
        if (text[i] == text[j])
            j++;
        pi[i] = j;
    }
}

std::istream & algo(std::istream &cin, std::string sample, std::vector<int> &position) {
    char current_char;
    int current_value;
    std::vector<unsigned int> pi;
    prefix_function(sample, pi);
    sample.append("\0");
    unsigned int dead_char = sample.length();
    pi.push_back(0);
    current_value = 0;
    int k = 0; //просто счетчик позиции в тексте
    current_char = cin.get();
    while(!cin.eof()) {
        unsigned int j = current_value;
        while ((j > 0) && (current_char != sample[j] || j == dead_char))
            j = pi[j - 1];
        if (current_char == sample[j])
            j++;
        current_value = j;
        if (j == sample.length())
            position.push_back(k - sample.length() + 1);
        k++;
        current_char = cin.get();
    }
    return cin;
}

int main() {
    std::ifstream fin("input.txt");
    if (!fin.is_open()) {
        std::cerr << "Файла нет" << std::endl;
        return 1;
    }
    std::string sample;
    std::getline(fin, sample);
    std::vector<int> position;
    algo(fin, sample, position);
    for (unsigned int i = 0; i < position.size(); i++) {
        std::cout << position[i] << std::endl;
    }
    return 0;
}
