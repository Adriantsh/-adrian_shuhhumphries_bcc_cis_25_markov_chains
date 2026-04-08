#include <iostream>
#include <cstdlib>
#include <ctime>
#include "markov.h" 
using namespace std;

int main()
{   
    srand(time(0));
    string testWords[] = {"the", "cat", "sat", "down"};
    cout << joinWords(testWords, 0, 2) << std::endl;  // Should print: the cat
    cout << joinWords(testWords, 1, 3) << std::endl;  // Should print: cat sat down
}