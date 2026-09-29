#include "patricia_trie.h"

#include <iostream>

PatriciaTrie::PatriciaTrie()
    : root_(std::make_unique<Node>()), word_count_(0) {}

int PatriciaTrie::index_of(char character) {
    if (character < 'a' || character > 'z') {
        return -1;
    }
    return character - 'a';
}

bool PatriciaTrie::valid_word(const std::string& word) {
    if (word.empty()) {
        return false;
    }

    for (char character : word) {
        if (index_of(character) < 0) {
            return false;
        }
    }
    return true;
}

std::size_t PatriciaTrie::common_prefix(const std::string& word,
                                       std::size_t position,
                                       const std::string& label) {
    std::size_t length = 0;
    while (position + length < word.size() && length < label.size()
           && word[position + length] == label[length]) {
        ++length;
    }
    return length;
}

bool PatriciaTrie::insert(const std::string& word) {
    if (!valid_word(word)) {
        return false;
    }

    Node* current = root_.get();
    std::size_t position = 0;

    while (position < word.size()) {
        int index = index_of(word[position]);
        std::unique_ptr<Edge>& edge = current->children[index];

        if (!edge) {
            edge = std::make_unique<Edge>();
            edge->label = word.substr(position);
            edge->child = std::make_unique<Node>();
            edge->child->is_word = true;
            ++word_count_;
            return true;
        }

        std::size_t shared = common_prefix(word, position, edge->label);
        if (shared == edge->label.size()) {
            position += shared;
            current = edge->child.get();
            continue;
        }

        std::unique_ptr<Edge> old_edge = std::move(edge);
        auto split_node = std::make_unique<Node>();

        old_edge->label = old_edge->label.substr(shared);
        int old_index = index_of(old_edge->label[0]);
        split_node->children[old_index] = std::move(old_edge);

        auto split_edge = std::make_unique<Edge>();
        split_edge->label = word.substr(position, shared);
        split_edge->child = std::move(split_node);
        edge = std::move(split_edge);

        Node* new_parent = edge->child.get();
        position += shared;
        if (position == word.size()) {
            new_parent->is_word = true;
        } else {
            auto new_edge = std::make_unique<Edge>();
            new_edge->label = word.substr(position);
            new_edge->child = std::make_unique<Node>();
            new_edge->child->is_word = true;
            int new_index = index_of(new_edge->label[0]);
            new_parent->children[new_index] = std::move(new_edge);
        }

        ++word_count_;
        return true;
    }

    if (current->is_word) {
        return false;
    }

    current->is_word = true;
    ++word_count_;
    return true;
}

bool PatriciaTrie::contains(const std::string& word) const {
    if (!valid_word(word)) {
        return false;
    }

    const Node* current = root_.get();
    std::size_t position = 0;

    while (position < word.size()) {
        int index = index_of(word[position]);
        const std::unique_ptr<Edge>& edge = current->children[index];
        if (!edge || common_prefix(word, position, edge->label) != edge->label.size()) {
            return false;
        }

        position += edge->label.size();
        current = edge->child.get();
    }

    return current->is_word;
}

std::size_t PatriciaTrie::size() const {
    return word_count_;
}

bool PatriciaTrie::empty() const {
    return word_count_ == 0;
}

void PatriciaTrie::print_node(const Node* node, const std::string& prefix) const {
    int child_count = 0;
    for (const auto& child : node->children) {
        if (child) {
            ++child_count;
        }
    }

    int child_number = 0;
    for (const auto& child : node->children) {
        if (!child) {
            continue;
        }

        ++child_number;
        bool is_last = child_number == child_count;
        std::cout << prefix << (is_last ? "\\-- " : "|-- ")
                  << child->label
                  << (child->child->is_word ? " *" : "") << '\n';
        print_node(child->child.get(), prefix + (is_last ? "    " : "|   "));
    }
}

void PatriciaTrie::print() const {
    std::cout << "(raiz)" << '\n';
    if (empty()) {
        std::cout << "(vacio)" << '\n';
        return;
    }
    print_node(root_.get(), "");
}
