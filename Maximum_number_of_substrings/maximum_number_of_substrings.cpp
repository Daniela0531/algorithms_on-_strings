#include <bits/stdc++.h>

std::vector<size_t> PrefixFunction(const std::string string);
size_t MaxNumberOfSubstring(const std::string string);

int main() {
    std::string string;
    std::cin >> string;
    std::cout << MaxNumberOfSubstring(string) + 1 << std::endl;
}

size_t MaxNumberOfSubstring(const std::string string) {
    size_t counter = 0;
    for (size_t len_of_string_for_sezrching_substring = 2; len_of_string_for_sezrching_substring <= string.size();
         ++len_of_string_for_sezrching_substring) {
        std::string tmp = string;
        tmp.resize(len_of_string_for_sezrching_substring);
        std::reverse(tmp.begin(), tmp.end());
        size_t max_substring_length_of_cur_string = 0;
        for (auto prefix_length : PrefixFunction(tmp)) {
            if (prefix_length > max_substring_length_of_cur_string) {
                max_substring_length_of_cur_string = prefix_length;
            }
        }
        counter += len_of_string_for_sezrching_substring - max_substring_length_of_cur_string;
    }
    return counter;
}

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
