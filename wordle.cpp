#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<string>
#include<cctype>
#include<cstdlib>
using namespace std;
struct Words
{
    string word;
};
bool checkGuess(char userGuess[], char correctWord[], char letterPool[27], bool guessBool);
void makeGuess(int randomNumber);

int main()
{
    srand(time(nullptr));
    int randomNumber = (rand() % (2673 - 1) + 1);
    makeGuess(randomNumber);
    return 0;
}
void makeGuess(int randomNumber)
{
    char correctWord[6], userGuess[6], letterPool[27] = "abcdefghijklmnopqrstuvwxyz";;
    Words wordArr[2673];
    bool guessBool = false;
    int guesses = 1;
    ifstream myIn;
    myIn.open("wordleWords.txt"); // absolute pathname needed
    if (!myIn)
    {
        cout<<"Unable to open file"<<endl;
    }
    else
    {
        while (guesses < 7 && guessBool == false)
        {
            bool wordFound = false;
            cout<<"Enter your guess: "<<endl;
            cin.getline(userGuess, 6);
            string string1 = userGuess;
            for (int i = 0; i < 2673; i++)
            {
                getline(myIn, wordArr[i].word);
                if (i == randomNumber)
                {
                    strcpy(correctWord, (wordArr[i].word).c_str()); // copying the internal c-string of the string object word in the textfile into the correctWord if the index matches the random number, this is how i randomly generate the word
                }
                if (wordArr[i].word == string1)
                {
                    wordFound = true;
                }
            }
            if (wordFound == true)
            {
                guessBool = checkGuess(userGuess, correctWord, letterPool, guessBool);
                cout<<"Guesses: "<<guesses<<"/6"<<endl;
                guesses+=1;
            }
            else
            {
                cout<<"Not in word list."<<endl;
            }
        }
        if (guessBool == false)
        {
            cout<<"Nice try! The word was: "<<correctWord<<endl;
        }
    }
}
bool checkGuess(char userGuess[], char correctWord[], char letterPool[27], bool guessBool)
{
    char guessData[6] = "_____";
    int wrongLetter = 0, rightLetter = 0;
    for (int i = 0; i < 5; i++) // traverses the userGuess character array
    {
        for (int j = 0; j < 5; j++) // traverses the correctWord character array
        {
            if (userGuess[i] == correctWord[j] && i == j) // if the two letters match and are in the same place
            {
                guessData[i] = toupper(userGuess[i]);
                rightLetter++;
            }
            else if (userGuess[i] == correctWord[j] && i != j) // if the two letters match but are not in the same place
            {
                guessData[i] = tolower(userGuess[i]);
            }
            else if (userGuess[i] != correctWord[j]) // if the letter doesn't equal the one in the correctWord list (figuring out if it exists)
            {
                wrongLetter++;
            }
        }
        if (wrongLetter == 5)
        {
            for (int k = 0; k < 26; k++)
            {
                if (letterPool[k] == userGuess[i])
                {
                    letterPool[k] = '.';
                }
            }
        }
        if (rightLetter >= 5)
        {
            guessBool = true;
            cout<<"Correct Word!"<<endl;
        }
        wrongLetter = 0;
    }
    rightLetter = 0;
    cout<<"Letter Pool: ";
    for (int i = 0; i < 26; i++)
    {
        cout<<letterPool[i]<<" ";
    }
    cout<<endl;
    cout<<"Guess Data: ";
    for (int i = 0; i < 5; i++)
    {
        cout<<guessData[i]<<" ";
    }
    cout<<endl;
    return guessBool;
}
