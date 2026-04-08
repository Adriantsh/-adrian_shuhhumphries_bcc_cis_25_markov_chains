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
    cout << "Read " << count << " words" << endl;
    for (int i = 0; i < 10 && i < count; i++) 
    {
        cout << words[i] << endl;
    }

    string prefixes[10000], suffixes[10000];
    int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, 10000);
    for (int i = 0; i < 20 && i < chainSize; i++) 
    {
        cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << endl;
    }

    // Pick a prefix you saw in your chain printout. Call getRandomSuffix 10 times:
    for (int i = 0; i < 10; i++)
    {
        cout << getRandomSuffix(prefixes, suffixes, chainSize, "has") << endl;
    }

    return 0;
}