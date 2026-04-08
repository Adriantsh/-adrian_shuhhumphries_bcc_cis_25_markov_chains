#include <string>
#include <fstream>
#include "markov.h"
using namespace std;

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

int readWordsFromFile(string filename, string words[], int maxWords)
{
    ifstream = inputFile;
    inputFile.open(filename)

    if (inputFile.is_open())
    {
        int count = 0;
        while (count < maxWords && inputFile >> words[count])
            count++;
        inupFile.close();
        return count;
    }
    else
        return -1;
}

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

    int matchCount = 0;
    for (int i = 0; i < chainSize; i++)
    {
        if (prefixes[i] == currentPrefix)
            matchCount++;
        if (matchCount == pick)
            return suffixes[i];
    }
    return "";
}

string getRandomPrefix(const string prefixes[], int chainSize)
{
    int index = rand() % chainSize;
    return prefixes[index];
}

string generateText(const string prefixes[], const string suffixes[],
                         int chainSize, int order, int numWords)
{
    string currentPrefix = getRandomPrefix(prefixes, chainSize);
    string result = currentPrefix;

    string currentWords[10];
    int wordIndex = 0;                                                                                                                                                                 
    string temp = "";

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



