// #include <string>
// #include <fstream>  // For file handling
// #include <iostream> // For standard I/O

// class TrieNode
// {
// public:
//     bool isEndOfWord;       // Flag to indicate the end of a word
//     TrieNode *children[26]; // Array of pointers to child nodes

//     TrieNode() : isEndOfWord(false)
//     {
//         for (auto &child : children)
//         {
//             child = nullptr;
//         }
//     }

//     ~TrieNode()
//     {
//         for (auto &child : children)
//         {
//             delete child;
//         }
//     }

//     bool hasChildren() const
//     {
//         for (const auto &child : children)
//         {
//             if (child != nullptr)
//             {
//                 return true;
//             }
//         }
//         return false;
//     }
// };

// class Trie
// {
// public:
//     TrieNode *root;

//     Trie() : root(new TrieNode()) {}

//     ~Trie()
//     {
//         delete root; // Add a recursive delete function in real use to properly clean up
//     }
//     void insert(const std::string& word);
//     bool search(const std::string& word) const;
//     bool deleteWord(const std::string& word);
//     void printWords() const;
//     bool isEmpty() const;
//     void clear();
//     int countPrefix(const std::string& prefix) const;
//     void spellcheck(const std::string& word) const;
//     int size() const;

//     // void loadInsert(const std::string &word);
//     // void insert(TrieNode *root, std::string word);
//     // bool search(TrieNode *root, std::string word);
//     // bool deleteHelper(TrieNode *&current, std::string word, int depth = 0);
//     // void deleteWord(TrieNode *root, std::string word);
//     // void printWords(TrieNode *node, std::string word = "");
//     // void loadWordsIntoTrie(Trie &trie, const std::string &filename)
//     {
//         std::ifstream file(filename);
//         std::string word;
//         while (file >> word)
//         {
//             trie.loadInsert(word);
//         }
//     }

// private:
//     void deleteAllNodes(TrieNode *node)
//     {
//         if (!node)
//             return;
//         for (int i = 0; i < 26; i++)
//         {
//             if (node->children[i])
//             {
//                 deleteAllNodes(node->children[i]);
//             }
//         }
//         delete node;
//     }
// };

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
    Trie();
    ~Trie();
    void insert(const std::string &word);
    bool search(const std::string &word) const;
    bool deleteWord(const std::string &word);
    void printWords() const;
    bool isEmpty() const;
    void clear();
    int countPrefix(const std::string &prefix) const;
    void spellcheck(const std::string &word) const;
    int size() const;

private:
    void clearHelper(TrieNode *node);
    void printWordsHelper(TrieNode *node, const std::string &prefix) const;
    bool deleteHelper(TrieNode *&node, const std::string &word, int depth);
    int sizeHelper(TrieNode *node) const;
    int countWordsFromNode(TrieNode *node) const;
    void printWordsFromNode(TrieNode *node, const std::string &prefix) const
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
                char nextChar = 'a' + i;
                printWordsFromNode(node->children[i], prefix + nextChar);
            }
        }
    }
};

#endif
