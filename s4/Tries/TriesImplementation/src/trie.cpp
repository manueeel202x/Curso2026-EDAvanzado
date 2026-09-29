#include "trie.h"

#include <iostream>

Trie::Trie() : root_(std::make_unique<Node>()), word_count_(0) {}

int Trie::index_of(char character) {
    if (character < 'a' || character > 'z') {
        return -1;
    }
    return character - 'a';
}

bool Trie::insert(const std::string& word) {
    if (word.empty()) {
        return false;
    }

    Node* current = root_.get();
    for (char character : word) {
        int index = index_of(character);
        if (index < 0) {
            return false;
        }

        if (!current->children[index]) {
            current->children[index] = std::make_unique<Node>();
        }
        current = current->children[index].get();
    }

    if (current->is_word) {
        return false;
    }

    current->is_word = true;
    ++word_count_;
    return true;
}

const Trie::Node* Trie::find_node(const std::string& text) const {
    const Node* current = root_.get();
    for (char character : text) {
        int index = index_of(character);
        if (index < 0 || !current->children[index]) {
            return nullptr;
        }
        current = current->children[index].get();
    }
    return current;
}

bool Trie::contains(const std::string& word) const {
    const Node* node = find_node(word);
    return node != nullptr && node->is_word;
}

bool Trie::starts_with(const std::string& prefix) const {
    return find_node(prefix) != nullptr;
}

bool Trie::has_children(const Node* node) {
    for (const auto& child : node->children) {
        if (child) {
            return true;
        }
    }
    return false;
}

bool Trie::erase(Node* node, const std::string& word, std::size_t depth) {
    if (depth == word.size()) {
        if (!node->is_word) {
            return false;
        }
        node->is_word = false;
        return true;
    }

    int index = index_of(word[depth]);
    if (index < 0 || !node->children[index]) {
        return false;
    }

    Node* child = node->children[index].get();
    if (!erase(child, word, depth + 1)) {
        return false;
    }

    if (!child->is_word && !has_children(child)) {
        node->children[index].reset();
    }
    return true;
}

bool Trie::erase(const std::string& word) {
    if (!contains(word)) {
        return false;
    }

    erase(root_.get(), word, 0);
    --word_count_;
    return true;
}

std::size_t Trie::size() const {
    return word_count_;
}

bool Trie::empty() const {
    return word_count_ == 0;
}

void Trie::print_node(const Node* node, const std::string& prefix) const {
    int child_count = 0;
    for (const auto& child : node->children) {
        if (child) {
            ++child_count;
        }
    }

    int child_number = 0;
    for (int index = 0; index < static_cast<int>(node->children.size()); ++index) {
        const auto& child = node->children[index];
        if (!child) {
            continue;
        }

        ++child_number;
        bool is_last = child_number == child_count;
        std::cout << prefix << (is_last ? "\\-- " : "|-- ")
                  << static_cast<char>('a' + index)
                  << (child->is_word ? " *" : "") << '\n';

        print_node(child.get(), prefix + (is_last ? "    " : "|   "));
    }
}

void Trie::print() const {
    std::cout << "(raiz)" << '\n';
    if (empty()) {
        std::cout << "(vacio)" << '\n';
        return;
    }

    print_node(root_.get(), "");
}
