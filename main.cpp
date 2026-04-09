// Generate text using markov chains
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

    // The user inputs the filename, markov chain order, and number of words to generate
    cout << "Enter the file name: ";
    cin >> filename;
    cout << "Enter the order of the markov chain: (1, 2, or 3) ";
    cin >> order;
    cout << "Enter the number of words to generate: ";
    cin >> numWords;

    // Declare large arrays
    const int ARR_SIZE = 100000;
    string words[ARR_SIZE], 
           prefixes[ARR_SIZE],
           suffixes[ARR_SIZE];

    // Write words to file, build Markov chain, generate text       
    int count = readWordsFromFile(filename, words, ARR_SIZE);
    int chainSize = buildMarkovChain(words, count, order, prefixes, suffixes, ARR_SIZE);
    string output = generateText(prefixes, suffixes, chainSize, order, numWords);

    // Output generated text
    cout << "Generated text:\n" << output << endl;
    return 0;
}