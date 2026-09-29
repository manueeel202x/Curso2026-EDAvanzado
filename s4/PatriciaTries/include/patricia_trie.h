#ifndef PATRICIA_TRIE_H
#define PATRICIA_TRIE_H

#include <array>
#include <cstddef>
#include <memory>
#include <string>

class PatriciaTrie {
public:
    PatriciaTrie();
    ~PatriciaTrie() = default;

    PatriciaTrie(const PatriciaTrie&) = delete;
    PatriciaTrie& operator=(const PatriciaTrie&) = delete;

    bool insert(const std::string& word);
    bool contains(const std::string& word) const;
    std::size_t size() const;
    bool empty() const;
    void print() const;

private:
    struct Node;

    struct Edge {
        std::string label;
        std::unique_ptr<Node> child;
    };

    struct Node {
        bool is_word = false;
        std::array<std::unique_ptr<Edge>, 26> children{};
    };

    std::unique_ptr<Node> root_;
    std::size_t word_count_;

    static int index_of(char character);
    static bool valid_word(const std::string& word);
    static std::size_t common_prefix(const std::string& word,
                                     std::size_t position,
                                     const std::string& label);
    void print_node(const Node* node, const std::string& prefix) const;
};

#endif
