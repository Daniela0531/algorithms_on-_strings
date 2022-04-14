#include <bits/stdc++.h>

// size_t, потому что вектор длин

std::vector<size_t> PrefixFunction(const std::string string);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string string;
    std::cin >> string;
    for (size_t prev_prefix_length : PrefixFunction(string)) {
        std::cout << prev_prefix_length << " ";
    }
    std::cout << std::endl;
    return 0;
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
