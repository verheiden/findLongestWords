//
//  main.cpp
//  trieSolution
//
//  Created by Jung on 5/18/16.
//  Copyright © 2016 Jung. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "trie.hpp"
#include <sys/stat.h>
#define filename "/Users/jung/Documents/workspace/aspera.txt"
#define MAX_ENTRY 200000
typedef struct Node{
    int len;
    char *word;
} Node, *pNode;

class NodeTbl{
    trie tree;
    Node  tbl[MAX_ENTRY];
    int shortest = ~0;
    int longestIndex = 0; 
    int secondLongestIndex = 0;
    int numWords = 0;
    int totalMatch = 0;

public:
    NodeTbl();
    NodeTbl(const char *ifile, int fileSize);

    ~NodeTbl(){
        
    }
    
    char *getLongest()
    {
        return (tbl[longestIndex].word );
    }
    char *getSecond()
    {
        return (tbl[secondLongestIndex].word );
    }
    int getTotals()
    {
        return totalMatch;
    }
    void searchLongest();
    bool wordMatch(char *s, int slen );
    
};
bool NodeTbl::wordMatch(char *s, int slen)
{
    int  remainLen = (int)strlen(s);
    
    while ( slen  >=shortest )
    {
        if ( tree.searchWord(s, slen))
        {
            if ( remainLen == slen )
                return true;
            else if ( wordMatch(s+slen, remainLen - slen))
                return true;
        }
        slen--;
    }
    return false;
}

void NodeTbl::searchLongest()
{
    int minLength = 2*shortest;
    for ( int i = 0; i < numWords; i++){
        if ( tbl[i].len >= minLength )
        {
            if ( wordMatch(tbl[i].word, tbl[i].len - shortest))
            {
                totalMatch++;
                if ( tbl[i].len > tbl[longestIndex].len  )
                {
                    secondLongestIndex = longestIndex;
                    longestIndex = i;                    
                }
                else if ( tbl[i].len > tbl[secondLongestIndex].len )
                {
                    secondLongestIndex = i;
                }
            }
        }
    }
}
NodeTbl::NodeTbl()
{
    FILE *fp;
    char *pBuffer;
    struct stat fileinfo;
    
    if ( stat(filename, &fileinfo) ==  -1 )
    {
        printf("Input file %s cannot be found\n",filename);
        exit(-1);
    }    if (!(fp = fopen(filename, "r")))
    {
        printf("opening input file %s failed", filename);
        exit(-1);
    }
    int filesize = (int) fileinfo.st_size;
    if (!(pBuffer = (char *)malloc(filesize + 10 )))
    {
        printf("allocating input memory  %i  bytes failed \n", (filesize + 10 ));
        exit(-1);
    }
    if ( fread( pBuffer, 1, filesize, fp) != filesize )
    {
        printf("reading in the input file failed\n");
        exit(-1);
    }
    int wordStart = 0;
    
    for(int i = 0; i < filesize; i++ )
    {
        char c = pBuffer[i];
        if ( c == '\r' || c == '\n')
        {
            pBuffer[i] = '\0';
            if ( c == '\n')
            {
                int length = i - wordStart -1;
                if ( length == 0  )
                {
                    wordStart = i + 1;
                    continue;
                }
                tbl[numWords].word = &pBuffer[wordStart];
                tbl[numWords].len =  length;
                if ( (tbl[numWords].len < shortest ) || ( shortest == ~0 ))
                    shortest = tbl[numWords].len;
                tree.insertWord(&pBuffer[wordStart]);
                wordStart = i + 1;
                numWords++;
            }                
        }
    }
}
int main(int argc, const char *argv[])
{

    NodeTbl *tbl;
    double time_consumed;
    clock_t start, end;
    start = clock();
    tbl = new NodeTbl();
    tbl->searchLongest();
    end = clock();
    std::cout << "Time consumed " << (end - start ) << std::endl;
    std::cout  << "Total number of matching words : " << tbl->getTotals() << std::endl;
    std::cout  << "The longest word is " << tbl->getLongest()<< std::endl;
    std::cout << "The second longest word is" << tbl->getSecond() << std::endl;
    exit(1); 
}
