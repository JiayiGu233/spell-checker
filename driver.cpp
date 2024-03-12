// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"


int main(){
    
    // your code goes here...  
    Trie theTrie;

    while (!std::cin.eof())
    {
        std::string command;
        getline(std::cin, command);
        if (command[0] == 'l')
        {
           theTrie.loadWordsIntoTrie(theTrie, "corpus.txt");
        }
        if (command[0] == 'i')
        {
            std::string d = command.substr(4);

            theTrie.insert()

        }
        if (command[0] == 'c')
        {
                    

            theLinkedlist.countPlayers();
        }
         if (command[0] == 'e')
        {   
                      

            theLinkedlist.removeClosest();
            theLinkedlist.countPlayers();
        }
        if (command[0] == 'p')
        {
                    

            std::string d = command.substr(4);
            double distance=std::stod(d);
            theLinkedlist.printPlayers(distance);
        }
        if (command[0] == 's')
        {
            
        }
    }
    return 0;

    }
