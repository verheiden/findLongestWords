//
//  trie.cpp
//  trieSolution
//
//  Created by Jung on 5/18/16.
//  Copyright © 2016 Jung. All rights reserved.
//

#include "trie.hpp"
trie::trie(){
    root = new trieNode();
    root->prefixes = 0;
    root->eow = false;
    root->theChar = '\0';
    for ( int i = 0; i < MAX_CHAR; i++)
    {
        root->edge[i] = NULL;
    }
}
trie::~trie()
{
    if ( root != NULL ){
        truncateNode(root);
        root = NULL;
    }
}
void trie::insertWord(char *word){
    trieNode *t = root;
    while(*word){
        char c = INDEX(*word);
        if ( t->edge[c] == NULL )
        {
            trieNode *n  = new trieNode();
            n->prefixes = 0;
            n->eow = false;
            n->theChar = *word;
            t->edge[c] = n;
            for (int i = 0; i < MAX_CHAR; i++)
                n->edge[i] = NULL;
        }
        t->prefixes++;
        t = t->edge[c];
        word++;
    }
    t->eow = true;
}
void trie::deleteWord(char *word)
{
    trieNode *t = root;
    while(*word)
    {
        char c = INDEX(*word++);
        if ( t->edge[c] == NULL )
            return;
        t->edge[c]->prefixes--;
        if ( t->edge[c]->prefixes ==  0 )
        {
            truncateNode(t->edge[c]);
            t->edge[c] = NULL;
        }
    }
    if ( t->eow )
        t->eow = false;
}
bool trie::searchWord(char *word, int len)
{
    trieNode *t = root;
    for ( int i = 0; i < len; i++)
    {
       if ( t->edge[INDEX(word[i])] == NULL )
       {
           return false;
       }
        else
        {
            t = t->edge[INDEX(word[i])];
        }
    }
    if ( t->eow )
        return true;
    else
        return false;
}
void trie::truncateNode(trieNode *t){
    for (int i = 0; i < MAX_CHAR; i++)
    {
        if ( t->edge[i] != null )
            truncateNode(t->edge[i]);
    }
    delete t;
}
