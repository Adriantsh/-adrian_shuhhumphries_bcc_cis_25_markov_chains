#include <iostream>
#include <cstdlib>
#include <ctime>
#include "markov.h" 
using namespace std;

int main()
{   
    srand(time(0));

    string filename;
    int order, numWords;

    cout << "Enter the file name: ";
    cin >> filename;
    cout << "Enter the order of the markov chain: (1, 2, or 3) ";
    cin >> order;
    cout << "Enter the number of words to generate: ";
    cin >> numWords;

    const int ARR_SIZE = 100000;
    string words[ARR_SIZE], 
           prefixes[ARR_SIZE],
           suffixes[ARR_SIZE];

    int count = readWordsFromFile(filename, words, ARR_SIZE);
    int chainSize = buildMarkovChain(words, count, order, prefixes, suffixes, ARR_SIZE);
    string output = generateText(prefixes, suffixes, chainSize, order, numWords);

    cout << "Generated text:\n" << output << endl;
    return 0;
}