#include <iostream>
#include <cstdlib>
#include <ctime>
#include "markov.h" 
using namespace std;

int main()
{   
    string words[1000];
    int count = readWordsFromFile("test.txt", words, 1000);
    cout << "Read " << count << " words" << endl;
    for (int i = 0; i < 10 && i < count; i++) 
    {
        cout << words[i] << endl;
    }
}