#include <iostream>
#include <vector>
#include <cstring>

template <class T>
std::vector<size_t> ZFunction(const T string);

int main() {
    size_t number_of_cubes = 0;
    size_t number_of_colors = 0;
    std::cin >> number_of_cubes >> number_of_colors;

    std::vector<size_t> string(number_of_cubes * 2);

    for (size_t i = 0; i < number_of_cubes; ++i) {
        std::cin >> string[i];
    }

    for (size_t i = 0; i < number_of_cubes; ++i) {
        string[string.size() - i - 1] = string[i];
    }

    std::vector<size_t> z_array = ZFunction(string);

    for (size_t i = number_of_cubes; i < z_array.size(); ++i) {
        if (!(z_array[i] % 2) && z_array[i] + i == z_array.size()) {
            std::cout << number_of_cubes - z_array[i] / 2 << " ";
        }
    }
    std::cout << number_of_cubes << std::endl;
    return 0;
}

template <class T>
std::vector<size_t> ZFunction(const T string) {
    std::vector<size_t> prefixes(string.size(), 0);
    size_t left_ind = 0;
    size_t right_ind = 0;
    prefixes[0] = string.size();
    for (size_t substring_length = 1; substring_length < string.size(); ++substring_length) {
        if (substring_length <= right_ind) {
            prefixes[substring_length] =
                std::min(prefixes[substring_length - left_ind], right_ind - substring_length + 1);
        }
        while ((substring_length + prefixes[substring_length] < string.size()) &&
               (string[prefixes[substring_length]] == string[substring_length + prefixes[substring_length]])) {
            prefixes[substring_length] += 1;
        }
        if (prefixes[substring_length] + substring_length - 1 > right_ind) {
            right_ind = prefixes[substring_length] + substring_length - 1;
            left_ind = substring_length;
        }
    }
    return prefixes;
}
