// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"

int main()
{

    // your code goes here...
    Trie theTrie;

    while (!std::cin.eof())
    {
        std::string command;
        getline(std::cin, command);
        if (command[0] == 'l')
        {
            theTrie.loadWordsIntoTrie(theTrie, "corpus.txt");
            std::cout << "success" << std::endl;
        }
        if (command[0] == 'i')
        {
            std::string word = command.substr(2);
            if (!theTrie.search(word))
            {
                std::cout << "success" << std::endl;
                theTrie.insert(word);
            }
            else
            {
                std::cout << "failure" << std::endl;
            }
            
        }
        if (command[0] == 'c' && command[1] == 'l')
        {
            theTrie.clear();
            std::cout << "success" << std::endl;
        }
        else if (command[0] == 'c')
        {
            std::string prefix = command.substr(2);
            if(theTrie.countPrefix(prefix)==0){
                std::cout<<"not found"<<std::endl;
            }else{
            std::cout<<"count is "<<theTrie.countPrefix(prefix)<<std::endl;
            }
        }
        if (command[0] == 'e' && command[1] == 'm')
        {
            if (theTrie.isEmpty())
            {
                std::cout << "empty 1" << std::endl;
            }
            else
            {
                std::cout << "empty 0" << std::endl;
            }
        }
        else if (command[0] == 'e' && command[1] == 'x')
        {
            theTrie.clear();
            return 0;
        } 
        else if (command[0] == 'e')
        {
            std::string word = command.substr(2);

            theTrie.deleteWord(word);
        }
        if (command[0] == 'p')
        {
            theTrie.printWords();
        }
        if (command[0] == 's' && command[1] == 'p')
        {
            std::string word = command.substr(11);
            if(theTrie.search(word)){
                std::cout << "correct" << std::endl;
            }else{
            theTrie.spellcheck(word);}
        }
        else if (command[0] == 's')
        {
            std::cout<<"number of words is "<<theTrie.sizeOfTrie()<<std::endl;;
        }
    }
}
