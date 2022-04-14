#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <queue>

const int64_t kPowerOfAlphabet = 26;
const int64_t kPoison = -1;

class PrefixTree {
    struct Node {
        std::vector<int64_t> next;
        int64_t suffix_link = kPoison;
        int64_t exit_link = kPoison;
        int64_t terminal_id = kPoison;

        Node() {
            next.resize(kPowerOfAlphabet, kPoison);
        }
    };
    struct Tripple {
        int64_t child_id;
        int64_t parent_id;
        char symbol;
    };

    std::vector<Node> prefix_tree_{Node()};
    int64_t size_ = 0;

public:
    void SetExitLinks();
    void SetSuffixLinks();
    void SetLinks();
    void AddString(const std::string& string) {
        int64_t current_node = 0;
        for (const auto& symbol : string) {
            if (prefix_tree_[current_node].next[symbol - 'a'] == kPoison) {
                prefix_tree_.emplace_back();
                auto new_symbol = prefix_tree_.size() - 1;
                prefix_tree_[current_node].next[symbol - 'a'] = new_symbol;
            }
            current_node = prefix_tree_[current_node].next[symbol - 'a'];
        }
        prefix_tree_[current_node].terminal_id = size_++;
    }
    bool FindString(const std::string& string) const {
        int64_t current_node = 0;
        for (auto& symbol : string) {
            if (prefix_tree_[current_node].next[symbol - 'a'] == kPoison) {
                return false;
            }
            current_node = prefix_tree_[current_node].next[symbol - 'a'];
        }
        return true;
    }
    std::vector<std::vector<int64_t>> AhoCorasick(const std::string& string,
                                                  const std::vector<std::string>& substrings) {
        std::vector<std::vector<int64_t>> occurances_of_substrings(substrings.size());
        for (const std::string& substring : substrings) {
            AddString(substring);
        }
        SetLinks();
        int64_t node_id = 0;
        for (size_t i = 0; i < string.size(); ++i) {
            int64_t tmp_node_id = node_id;
            while (tmp_node_id != kPoison && prefix_tree_[tmp_node_id].next[string[i] - 'a'] == kPoison) {
                tmp_node_id = prefix_tree_[tmp_node_id].suffix_link;
            }
            if (tmp_node_id == kPoison) {
                node_id = 0;
            } else {
                node_id = prefix_tree_[tmp_node_id].next[string[i] - 'a'];
            }
            tmp_node_id = node_id;
            if (prefix_tree_[tmp_node_id].terminal_id == kPoison) {
                tmp_node_id = prefix_tree_[tmp_node_id].exit_link;
            }
            while (tmp_node_id != kPoison) {
                occurances_of_substrings[prefix_tree_[tmp_node_id].terminal_id].emplace_back(
                    i - substrings[prefix_tree_[tmp_node_id].terminal_id].size() + 2);
                tmp_node_id = prefix_tree_[tmp_node_id].exit_link;
            }
        }
        return occurances_of_substrings;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string string;
    std::cin >> string;

    int64_t number_of_substring = 0;
    std::cin >> number_of_substring;

    std::vector<std::string> substrings;
    std::string substring;
    for (int64_t i = 0; i < number_of_substring; ++i) {
        std::cin >> substring;
        substrings.emplace_back(substring);
    }

    PrefixTree prefix_tree;
    std::vector<std::vector<int64_t>> occurances_of_substrings = prefix_tree.AhoCorasick(string, substrings);

    for (auto substrings : occurances_of_substrings) {
        std::cout << substrings.size() << " ";
        for (auto substring : substrings) {
            std::cout << substring << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

void PrefixTree::SetExitLinks() {
    prefix_tree_[0].exit_link = kPoison;
    std::queue<int64_t> queue;
    for (int64_t i = 0; i < kPowerOfAlphabet; ++i) {
        if (prefix_tree_[0].next[i] != kPoison) {
            queue.push(prefix_tree_[0].next[i]);
        }
    }
    while (!queue.empty()) {
        int64_t node_id = queue.front();
        int64_t suffix = prefix_tree_[node_id].suffix_link;
        if (suffix != 0) {
            if (prefix_tree_[suffix].terminal_id == kPoison) {
                prefix_tree_[node_id].exit_link = prefix_tree_[suffix].exit_link;
            } else {
                prefix_tree_[node_id].exit_link = suffix;
            }
        }
        for (int64_t i = 0; i < kPowerOfAlphabet; ++i) {
            if (prefix_tree_[node_id].next[i] != kPoison) {
                queue.push(prefix_tree_[node_id].next[i]);
            }
        }
        queue.pop();
    }
}

void PrefixTree::SetSuffixLinks() {
    prefix_tree_[0].suffix_link = kPoison;
    std::queue<Tripple> queue;
    for (int64_t i = 0; i < kPowerOfAlphabet; ++i) {
        if (prefix_tree_[0].next[i] != kPoison) {
            queue.push(Tripple{prefix_tree_[0].next[i], 0, static_cast<char>(i)});
        }
    }
    while (!queue.empty()) {
        Tripple cur_tripple = queue.front();
        int64_t symbol = cur_tripple.symbol;
        int64_t parent_id = cur_tripple.parent_id;
        int64_t node_id = cur_tripple.child_id;
        int64_t suffix = prefix_tree_[parent_id].suffix_link;
        while (suffix != kPoison && prefix_tree_[suffix].next[symbol] == kPoison) {
            suffix = prefix_tree_[suffix].suffix_link;
        }
        if (suffix == kPoison) {
            prefix_tree_[node_id].suffix_link = 0;
        } else {
            prefix_tree_[node_id].suffix_link = prefix_tree_[suffix].next[symbol];
        }
        for (int64_t i = 0; i < kPowerOfAlphabet; ++i) {
            if (prefix_tree_[node_id].next[i] != kPoison) {
                queue.push(Tripple{prefix_tree_[node_id].next[i], node_id, static_cast<char>(i)});
            }
        }
        queue.pop();
    }
}

void PrefixTree::SetLinks() {
    SetSuffixLinks();
    SetExitLinks();
}
