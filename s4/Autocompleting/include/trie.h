#ifndef TRIE_H
#define TRIE_H

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Trie {
public:
    Trie();
    ~Trie() = default;

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    bool insert(const std::string& word);
    bool contains(const std::string& word) const;
    bool erase(const std::string& word);
    std::vector<std::string> autocomplete(const std::string& prefix) const;
    std::size_t size() const;
    bool empty() const;
    void print() const;

private:
    struct Node {
        bool is_word = false;
        std::array<std::unique_ptr<Node>, 26> children{};
    };

    std::unique_ptr<Node> root_;
    std::size_t word_count_;

    static int index_of(char character);
    const Node* find_node(const std::string& text) const;
    bool erase(Node* node, const std::string& word, std::size_t depth);
    static bool has_children(const Node* node);
    void collect_words(const Node* node, std::string& current,
                       std::vector<std::string>& words) const;
    void print_node(const Node* node, const std::string& prefix) const;
};

#endif
