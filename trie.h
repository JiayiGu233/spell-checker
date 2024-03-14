#include <string>
#include <fstream>  // For file handling
#include <iostream> // For standard I/O

class TrieNode
{
public:
    bool isEndOfWord;
    TrieNode *children[26];
    TrieNode();
    ~TrieNode();
    bool hasChildren() const;
};

class Trie
{
public:
    TrieNode *root;
    int size;
    Trie();
    ~Trie();

    void insert(const std::string &word);
    bool search(const std::string &word) const;
    void deleteWord(const std::string &word);
    void printWords() const;
    bool isEmpty() const;
    void clear();
    int countPrefix(const std::string &prefix) const;
    void spellcheck(const std::string &word) const;
    int sizeOfTrie() const;
    void loadWordsIntoTrie(Trie &trie, const std::string &filename);

private:
    void clearHelper(TrieNode *node);
    void printWordsHelper(TrieNode *node, const std::string &prefix) const;
    bool deleteHelper(TrieNode *&node, const std::string &word, int depth);
    int countWordsFromNode(TrieNode *node) const;
    void printWordsFromNode(TrieNode *node, const std::string &prefix) const;
};
