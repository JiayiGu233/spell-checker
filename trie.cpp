#include "trie.h"
#include <string>
#include <iostream>

// void Trie::loadInsert(const std::string &word)
// {
//     TrieNode *current = root;
//     for (char ch : word)
//     {
//         int index = ch - 'a'; // Assumes lowercase letters
//         if (!current->children[index])
//         {
//             current->children[index] = new TrieNode();
//         }
//         current = current->children[index];
//     }
//     current->isEndOfWord = true;
// }

// void Trie::insert(TrieNode *root, std::string word)
// {
//     TrieNode *current = root;
//     for (char ch : word)
//     {
//         int index = ch - 'a';
//         if (current->children[index] == nullptr)
//         {
//             current->children[index] = new TrieNode();
//         }
//         current = current->children[index];
//     }
//     current->isEndOfWord = true;
// }

// bool Trie::search(TrieNode *root, std::string word)
// {
//     TrieNode *current = root;
//     for (char ch : word)
//     {
//         int index = ch - 'a';
//         if (current->children[index] == nullptr)
//         {
//             return false; // Character path does not exist
//         }
//         current = current->children[index];
//     }
//     return current != nullptr && current->isEndOfWord;
// }

// bool Trie::deleteHelper(TrieNode *&current, std::string word, int depth = 0)
// {
//     if (!current)
//         return false;

//     if (depth == word.size())
//     { // If last character of word is reached
//         if (!current->isEndOfWord)
//             return false;               // Word does not exist
//         current->isEndOfWord = false;   // Unmark end of word
//         return !current->hasChildren(); // If true, delete this node
//     }

//     int index = word[depth] - 'a';
//     if (deleteHelper(current->children[index], word, depth + 1) && !current->isEndOfWord)
//     {
//         delete current->children[index];
//         current->children[index] = nullptr;
//         return !current->hasChildren(); // Delete node if it has no children
//     }
//     return false;
// }

// void Trie::deleteWord(TrieNode *root, std::string word)
// {
//     TrieNode::deleteHelper(root, word);
// }

// void Trie::printWords(TrieNode *node, std::string word = "")
// {
//     if (node->isEndOfWord)
//     {
//         std::cout << word << std::endl; // Print the word at the end of a valid path
//     }
//     for (int i = 0; i < 26; i++)
//     {
//         if (node->children[i])
//         {
//             char ch = 'a' + i; // Find the character to add to the prefix
//             printWords(node->children[i], word + ch);
//         }
//     }
// }

TrieNode::TrieNode() : isEndOfWord(false)
{
    for (auto &child : children)
    {
        child = nullptr;
    }
}

TrieNode::~TrieNode()
{
    for (auto &child : children)
    {
        delete child;
    }
}

bool TrieNode::hasChildren() const
{
    for (int i = 0; i < 26; ++i)
    {
        if (children[i] != nullptr)
        {
            return true; // Found a child node, so this node does have children
        }
    }
    return false;
}

Trie::Trie() : root(new TrieNode()) {}

Trie::~Trie()
{
    clear();
}

void Trie::insert(const std::string &word)
{
    TrieNode *current = root;
    bool isNewWord = false; // Flag to track if a new node is created

    for (char ch : word)
    {
        int index = ch - 'a';
        if (current->children[index] == nullptr)
        {
            current->children[index] = new TrieNode(); // Create a new node if necessary
            isNewWord = true;                          // Mark as new word since a new node is created
        }
        current = current->children[index];
    }

    if (!current->isEndOfWord)
    {
        current->isEndOfWord = true; // Mark the end of the word
        if (isNewWord)
        {
            std::cout << "success" << std::endl; // New word successfully inserted
        }
        else
        {
            std::cout << "failure" << std::endl; // Word exists but wasn't previously marked as a word
        }
    }
    else
    {
        std::cout << "failure" << std::endl; // Word already exists
    }
}

bool Trie::search(const std::string &word) const
{
     TrieNode* current = root;
    for (char ch : word) {
        int index = ch - 'a'; // Assuming the word is in lowercase
        if (!current->children[index]) {
            return false; // Character not found, word doesn't exist in Trie
        }
        current = current->children[index];
    }
    return current != nullptr && current->isEndOfWord;
}

bool Trie::deleteWord(const std::string &word)
{
    if (deleteHelper(root, word, 0)) {
        std::cout << "success" << std::endl;
        return true;
    } else {
        std::cout << "failure" << std::endl;
        return false;
    }
}

bool Trie::deleteHelper(TrieNode*& node, const std::string& word, int depth) {
   if (!node) return false; // Base case: node is null.

    bool shouldDeleteNode = false;

    if (depth == word.size()) { // End of the word reached.
        if (!node->isEndOfWord) return false; // Word does not exist.
        node->isEndOfWord = false; // Unmark end of word.
        shouldDeleteNode = !node->hasChildren(); // Node can be deleted if it has no children.
    } else {
        int index = word[depth] - 'a';
        if (node->children[index]) {
            bool childDeleted = deleteHelper(node->children[index], word, depth + 1);
            shouldDeleteNode = childDeleted && !node->isEndOfWord && !node->hasChildren();
        }
    }

    if (shouldDeleteNode) {
        delete node;
        node = nullptr;
    }

    return shouldDeleteNode || depth == word.size() && !node->isEndOfWord; // Successfully deleted or unmarked a word
}

void Trie::printWords() const
{
    printWordsHelper(root, "");
}

void Trie::printWordsHelper(TrieNode* node, const std::string& word) const {
    if (node == nullptr) {
        return; // Base case: reached a null node
    }

    if (node->isEndOfWord) {
        std::cout << word << " "; // Print the word when a leaf node is reached
    }

    for (int i = 0; i < 26; ++i) { // Iterate through all possible children
        if (node->children[i] != nullptr) {
            // Recurse with the next character added to the current word
            char nextChar = 'a' + i; // Convert the child index back to a character
            printWordsHelper(node->children[i], word + nextChar);
        }
    }
}

bool Trie::isEmpty() const
{
    return !root->hasChildren();
}

void Trie::clearHelper(TrieNode *node)
{
    if (node == nullptr)
        return; // Base case: node is null

    // Recursively delete all children
    for (int i = 0; i < 26; ++i)
    {
        if (node->children[i] != nullptr)
        {
            clearHelper(node->children[i]);
        }
    }

    delete node; // Delete the current node after its children have been deleted
}

void Trie::clear()
{
    clearHelper(root);
    root = nullptr;
}

int Trie::countPrefix(const std::string &prefix) const
{
   TrieNode* current = root;
    // Traverse to the end of the prefix
    for (char ch : prefix) {
        int index = ch - 'a'; // Assumes lowercase
        if (current->children[index] == nullptr) {
            return 0; // Prefix not found, no words start with this prefix
        }
        current = current->children[index];
    }
    // Now count all words that are descendants of the current node
    return countWordsFromNode(current);
}

int Trie::countWordsFromNode(TrieNode* node) const {
    if (node == nullptr) {
        return 0; // Base case
    }
    int count = node->isEndOfWord ? 1 : 0; // If this node marks the end of a word, count it
    // Recurse for all children
    for (int i = 0; i < 26; ++i) {
        count += countWordsFromNode(node->children[i]);
    }
    return count;
}

void Trie::spellcheck(const std::string &word) const
{
    TrieNode* current = root;
    std::string commonPrefix;
    bool isCompleteMatch = true;

    // Search for the word and determine the longest common prefix
    for (char ch : word) {
        int index = ch - 'a'; // Assumes lowercase
        if (current->children[index] == nullptr) {
            isCompleteMatch = false; // The complete word or part of it doesn't exist
            break; // Stop searching further
        }
        commonPrefix += ch; // Add to the common prefix
        current = current->children[index];
    }

    // If a complete match is found, print "correct"
    if (isCompleteMatch && current->isEndOfWord) {
        std::cout << "correct" << std::endl;
    } else {
        // If not a complete match, print all words with the common prefix
        if (current != nullptr && !commonPrefix.empty()) {
            printWordsFromNode(current, commonPrefix);
        } else {
            std::cout << std::endl; // Print a newline for no match at all
        }
    }
}

int Trie::size() const
{
    return sizeHelper(root);
}

int Trie::sizeHelper(TrieNode* node) const {
    if (node == nullptr) {
        return 0; // Base case: if node is null, contribute 0 to the count
    }
    int count = node->isEndOfWord ? 1 : 0; // If this node marks the end of a word, count it

    // Recursively count words for all children of this node
    for (int i = 0; i < 26; ++i) {
        count += sizeHelper(node->children[i]);
    }
    return count;
}