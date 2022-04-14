#include <bits/stdc++.h>

std::vector<size_t> PrefixFunction(const std::string string);
std::vector<size_t> SearchForSubstringInString(std::string string, std::string substring);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string substring1;
    std::string substring2;
    int number = 0;
    std::cin >> number >> substring1 >> substring2;
    std::string tmp(substring1);
    if (substring1 == substring2) {
        std::cout << "Random\n";
    } else {
        std::string string;
        string += substring1;
        string.push_back('0');
        string += substring1;
        string.push_back('%');
        string += substring1;
        string.push_back('1');
        string += substring1;

        std::vector<size_t> index_array = SearchForSubstringInString(string, substring2);
        if (!index_array.empty()) {
            if (index_array.size() > 1) {
                std::cout << "Random\n";
            } else if (string[index_array[0] - 1] == '1') {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else {
            std::cout << "Random\n";
        }
    }
    return 0;
}

std::vector<size_t> SearchForSubstringInString(std::string string, std::string substring) {
    size_t substring_length = substring.length();
    substring.push_back('#');
    substring += string;
    std::vector<size_t> prefixes_string = PrefixFunction(substring);
    std::vector<size_t> array_of_index;
    for (size_t i = 0; i < prefixes_string.size(); ++i) {
        if (prefixes_string[i] == substring_length) {
            array_of_index.push_back(i - 2 * substring_length);
        }
    }
    return array_of_index;
}

// O(n)
std::vector<size_t> PrefixFunction(const std::string string) {
    std::vector<size_t> prefixes_array(string.length(), 0);
    for (size_t ind_of_last_substring_elem = 1; ind_of_last_substring_elem < string.length();
         ++ind_of_last_substring_elem) {
        size_t prev_prefix_length = prefixes_array[ind_of_last_substring_elem - 1];
        while (string[prev_prefix_length] != string[ind_of_last_substring_elem] && prev_prefix_length != 0) {
            prev_prefix_length = prefixes_array[prev_prefix_length - 1];
        }
        if (string[prev_prefix_length] == string[ind_of_last_substring_elem]) {
            prev_prefix_length += 1;
        }
        prefixes_array[ind_of_last_substring_elem] = prev_prefix_length;
    }
    return prefixes_array;
}
