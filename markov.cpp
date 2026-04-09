// Functions for generating markov chain text
#include <string>
#include <fstream>
#include "markov.h"
using namespace std;

// Takes an array of words and outputs a string of those words
// seperated by spaces.
string joinWords(const string words[], int startIndex, int count)
{
    string result;

    for (int i = 0; i < count - 1; i++)
    {
        result += words[startIndex + i] + " ";
    }
    result += words[startIndex + count - 1];

    return result;
}

// Reads words from a file to an array of size maxWords
// Outputs number of words read
int readWordsFromFile(string filename, string words[], int maxWords)
{
    ifstream inputFile;
    inputFile.open(filename);

    if (inputFile.is_open())
    {
        int count = 0;
        while (count < maxWords && inputFile >> words[count])
            count++;
        inputFile.close();
        return count;
    }
    else
        return -1;
}

// Fills two arrays, one of prefixes:
// strings of length order that appear in the text
// and suffixes:
// the word following the corresponding prefix
int buildMarkovChain(const string words[], int numWords, int order,
                     string prefixes[], string suffixes[],
                     int maxChainSize)
{
    int count = 0;
    for (int i = 0; i < numWords - order; i++)
    {
        prefixes[count] = joinWords(words, i, order);  
        suffixes[count] = words[i + order];

        count++;
        if (count == maxChainSize)
            break;
    }
    return count;
}

// Get a random suffix by counting the number of matching prefixes
// and looping through them, stopping on a random one
string getRandomSuffix(const string prefixes[], const string suffixes[],
                            int chainSize, string currentPrefix)
{
    int matchCount = 0;
    for (int i = 0; i < chainSize; i++)
    {
        if (prefixes[i] == currentPrefix)
            matchCount++;
    }

    if (matchCount == 0)
        return "";

    int pick = rand() % matchCount;

    matchCount = 0;
    for (int i = 0; i < chainSize; i++)
    {
        if (prefixes[i] == currentPrefix)
        {
            if (matchCount == pick)
                return suffixes[i];
            else
                matchCount++;
        }
    }
    return "";
}

// Chooses a random prefix
string getRandomPrefix(const string prefixes[], int chainSize)
{
    int index = rand() % chainSize;
    return prefixes[index];
}

// Generates the text by repeatedly finding random suffixes to the preceding
// prefix.
string generateText(const string prefixes[], const string suffixes[],
                         int chainSize, int order, int numWords)
{
    string currentPrefix = getRandomPrefix(prefixes, chainSize);
    string result = currentPrefix;

    string currentWords[10];
    int wordIndex = 0;                                                                                                                                                                 
    string temp = "";

    // Break the first prefix into an array.
    for (int i = 0; i < currentPrefix.length(); i++) 
    {                                                                                                                                 
        if (currentPrefix[i] == ' ') 
        {                                                                                                                                                 
            currentWords[wordIndex] = temp;                                                                                                                                            
            wordIndex++;                                                                                                                                                               
            temp = "";                 
        } 
        else 
        {                                                                                                                                                                       
            temp += currentPrefix[i];  
        }
    }
    currentWords[wordIndex] = temp;

    // Repeatedly generate random suffixes to current prefix
    // Last suffix gets added to the end of the current prefix
    for (int i = 0; i < numWords - order; i++)
    {
        string newWord = getRandomSuffix(prefixes, suffixes, chainSize, currentPrefix);

        if (newWord == "")
            break;

        result += " " + newWord;

        for (int j = 0; j < order - 1; j++)
            currentWords[j] = currentWords[j + 1];


        currentWords[order - 1] = newWord;

        currentPrefix = joinWords(currentWords, 0, order);
    }

    return result;
}



