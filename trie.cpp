#include "trie.h"
#include <string>
#include <iostream>

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

Trie::Trie() : root(new TrieNode()), size(0) {}

Trie::~Trie()
{
    // std::cout << "enter \n";
    clear();
    // std::cout << "survive \n";
}

void Trie::insert(const std::string &word)
{
    TrieNode *current = root;

    for (char ch : word)
    {
        int index = ch - 'A';
        if (current->children[index] == nullptr)
        {
            current->children[index] = new TrieNode(); // Create a new node if necessary
        }
        current = current->children[index];
    }

    current->isEndOfWord = true; // Mark the end of the word
    size +=1;
    return; // New word successfully inserted
}


bool Trie::search(const std::string &word) const
{
    TrieNode *current = root;
    for (char ch : word)
    {
        int index = ch - 'A'; 
        if (!current->children[index])
        {
            return false; // Character not found, word doesn't exist in Trie
        }
        current = current->children[index];
    }
    return current != nullptr && current->isEndOfWord;
}

void Trie::deleteWord(const std::string &word)
{   
    if (search(word))
    {
        std::cout << "success" << std::endl;
        deleteHelper(root, word, 0);
        size-=1;
    }
    else
    {
        std::cout << "failure" << std::endl;
    }
    return;
}

bool Trie::deleteHelper(TrieNode*& node, const std::string& word, int depth) {
    if (!node) return false; // Base case: node is null.

    // If at the end of the word, unmark the endOfWord and check if node can be deleted.
    if (depth == word.size()) {
        if (!node->isEndOfWord) return false; // The word wasn't in the Trie.

        node->isEndOfWord = false; // Unmark the node as end of a word.

        // If node has no children, it can be deleted.
        if (!node->hasChildren()) {
            delete node;
            node = nullptr;
            return true; // Indicate the node was deleted.
        }
        return false; // Node wasn't deleted because it has children.
    }

    // Not at the end, recurse deeper for the next character.
    char ch = word[depth];
    int index = ch - 'A';
    if (!node->children[index]) return false; // Character path does not exist, word not found.

    // Recurse and delete child node if it's no longer needed.
    bool childDeleted = deleteHelper(node->children[index], word, depth + 1);

    // After trying to delete the child, check if the current node should also be deleted.
    if (childDeleted && !node->isEndOfWord && !node->hasChildren()) {
        delete node; // Delete current node as it's no longer needed.
        node = nullptr;
        return true; // Indicate this node was also deleted.
    }

    return false; // No deletion happened at this node.
}

void Trie::printWords() const
{   
    if(isEmpty()){
        return;
    }
    printWordsHelper(root, "");
    std::cout<<std::endl;
}

void Trie::printWordsHelper(TrieNode *node, const std::string &word) const
{
    if (node == nullptr)
    {
        return; // Base case: reached a null node
    }

    if (node->isEndOfWord)
    {
        std::cout << word << " "; // Print the word when a leaf node is reached
    }

    for (int i = 0; i < 26; ++i)
    { // Iterate through all possible children
        if (node->children[i] != nullptr)
        {
            // Recurse with the next character added to the current word
            char nextChar = 'A' + i; // Convert the child index back to a character
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
            node->children[i] = nullptr;
        }
    }

    auto temp = node;
    node = nullptr;
    delete temp; // Delete the current node after its children have been deleted
    
}

void Trie::clear()
{
    clearHelper(root);
    root = new TrieNode();
    size = 0;
}

int Trie::countPrefix(const std::string &prefix) const
{
    TrieNode *current = root;
    // Traverse to the end of the prefix
    for (char ch : prefix)
    {
        int index = ch - 'A'; 
        if (current->children[index] == nullptr)
        {
            return 0; // Prefix not found, no words start with this prefix
        }
        current = current->children[index];
    }
    // Now count all words that are descendants of the current node
    return countWordsFromNode(current);
}

int Trie::countWordsFromNode(TrieNode *node) const
{
    if (node == nullptr)
    {
        return 0; // Base case
    }
    int count = node->isEndOfWord ? 1 : 0; // If this node marks the end of a word, count it
    // Recurse for all children
    for (int i = 0; i < 26; ++i)
    {
        count += countWordsFromNode(node->children[i]);
    }
    return count;
}

void Trie::printWordsFromNode(TrieNode *node, const std::string &prefix) const
{
    if (node == nullptr)
    {
        return;
    }
    if (node->isEndOfWord)
    {
        std::cout << prefix << " ";
    }
    for (int i = 0; i < 26; ++i)
    {
        if (node->children[i] != nullptr)
        {
            char nextChar = 'A' + i;
            printWordsFromNode(node->children[i], prefix + nextChar);
        }
    }
}

void Trie::loadWordsIntoTrie(Trie &trie, const std::string &filename)
{
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {   
        if(!trie.search(word)){
            trie.insert(word);
        }
        
    }
}

void Trie::spellcheck(const std::string &word) const
{
    TrieNode *current = root;
    std::string commonPrefix;
   // bool isCompleteMatch = true;
    
    // Search for the word and determine the longest common prefix
    for (char ch : word)
    {
        int index = ch - 'A'; 
        if (current->children[index] == nullptr)
        {
   //         isCompleteMatch = false; // The complete word or part of it doesn't exist
            break;                   // Stop searching further
        }
        commonPrefix += ch; // Add to the common prefix
        current = current->children[index];
    }

    // If a complete match is found, print "correct"
    
    
        // If not a complete match, print all words with the common prefix
        if (current != nullptr && !commonPrefix.empty())
        {
            printWordsFromNode(current, commonPrefix);
            std::cout<<std::endl;
        }
        else
        {
            std::cout << std::endl; // Print a newline for no match at all
        }
    
}

int Trie::sizeOfTrie() const
{
    return size;
}

