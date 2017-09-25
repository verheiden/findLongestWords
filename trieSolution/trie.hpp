//
//  trie.hpp
//  trieSolution
//
//  Created by Jung on 5/18/16.
//  Copyright © 2016 Jung. All rights reserved.
//

#ifndef trie_hpp
#define trie_hpp
#ifndef FULL_ASCII 
#define MAX_CHAR 26
#define INDEX(c) c - 'a'
#else
#define MAX_CHAR 256
#define INDEX(c) c
#endif

#include <stdio.h>
class trie
{
  public:
    struct  trieNode
    {
        int prefixes;
        bool eow;
        char theChar;
        trieNode *edge[MAX_CHAR];
    } *root;
    trie();
    ~trie();
    void insertWord(char *);
    bool searchWord(char *, int);
    void truncateNode(trieNode *);
    void deleteWord(char *);
};
#endif /* trie_hpp */
