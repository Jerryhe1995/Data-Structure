#ifndef __FREQTABLE_H__
#define __FREQTABLE_H__

#include <stdbool.h>
#include <string>

#ifndef NULL
#define NULL nullptr  // adopts C++11 notation
#endif

class BSTNode {
    private:
        // word should always be stored in lowercase
        std::string word;
        // count how many occurrences of this word we have
        unsigned int count;

        BSTNode *left;
        BSTNode *right;

    public:
        BSTNode(const char *str) {
            count = 1;
            word = str;
            left = right = NULL;
        }
        ~BSTNode() {
        }

    friend class FreqTable;
};

class FreqTable {
    private:
        BSTNode *root;
        unsigned int n_elem;
        void inserthelper( char *str, BSTNode *p);
        int containshelper(char *str,BSTNode *p);
        void erasehelper( char *str, BSTNode *p);
        void sizehelper(BSTNode *p, int *count);
        void clearhelper(BSTNode *p);
        void print_allhelper( BSTNode *p);
        void  convert(char *str);
        
        // here you can add helper private methods

    public:
        // do not change any of the public methods
        // they should remain intact, so the autograder can grade your work

        // Q1 -- 5 pts
        // constructor of the tree
        FreqTable();

        // Q2 -- 5 pts
        // destructor of the tree
        ~FreqTable();

        // Q3 -- 20 pts
        // if the word already exists in the tree, just update the counter
        // otherwise make an insertion of a new word
        void insert(const char *str);

        // Q4 -- 10 pts
        // returns true if the word exists in the tree
        // false otherwise
        bool contains(const char *str);

        // Q5 -- 20 pts
        // if there is more than one occurrence of the word in the tree
        // decrease the counter, otherwise delete the node
        void erase(const char *str);

        // Q6 -- 5 pts
        // returns true if the tree is empty, false otherwise
        bool empty();

        // Q7 -- 5 pts
        // returns how many different words are in the tree
        unsigned int size();

        // Q8 -- 15 pts
        // remove all words from the tree and sets n_elem to zero
        void clear();

        // Q9 -- 15 pts
        // print (to the standard output) the frequency table in lexicographical
        // order using this format:
        // one word should be printed per line, followed by one whitespace, followed
        // by the number of occcurrences of this word in the tree
        void print_all();
};

#endif