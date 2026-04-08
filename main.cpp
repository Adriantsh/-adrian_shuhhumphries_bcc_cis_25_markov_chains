#include <iostream>
#include <cstdlib>
#include <ctime>
#include "markov.h" 
using namespace std;

int main()
{   
    srand(time(0));

    string words[1000];
    int count = readWordsFromFile("test.txt", words, 1000);

    string prefixes[10000], suffixes[10000];
    int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 10000);

    string output = generateText(prefixes, suffixes, chainSize, 1, 20);
    cout << output << endl;


    return 0;
}