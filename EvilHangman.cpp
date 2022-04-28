// EvilHangman2.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include "FamilySet.h"
//#include "TreeMap.h"
using namespace std;

bool debug;

bool PromptYesNoMessage(string msg) {
	while (true) {
		cout << msg << " (y/n) ";
		string response;
		cin >> response;
		if (response == "y")
			return true;
		if (response == "n")
			return false;
		cout << "Please enter y or n." << endl;
	}
}

int PromptGuesses() 
{
	while (true) {
		int len;
		cout << "Please enter how many guesses: ";
		cin >> len;
		if (len > 0)
			return len;
	}
}

int PromptWordLength()
{
    int len;

    // Your code here...
    while (true)
    {
        cout << "Please enter word length: ";
        cin >> len;
        if(len > 0 && len < 29)
            return len;
    }
}

string PromptGuess(string& guessedLetters)
{
    string guess = "";
    while(true)
    {
        cout << "Enter Guess: ";
        cin >> guess;

        bool letterGuessed = false;
        for(int i=0; i<guessedLetters.size(); i++)
        {
            if(guess[0] == guessedLetters[i])
            {
                letterGuessed = true;
            }
        }
        if(guess.size() == 1 && !letterGuessed)
        {
            guessedLetters += guess;
            return guess;
        }
    }
}

string ChooseFamily(string guess, string guessProgress, FamilySet& set) 
{
    // filter families by guess and guessProgress/guessPattern
    set.filterFamilies( guess, guessProgress );     // make families for the guess and guess progress

    string maxFamily;
    maxFamily = set.getNextFamily();        // get the family with most word
    return maxFamily;                   // return family with most words
}

bool isWin(string guessedProgress)
{
	return guessedProgress.find('*') == string::npos;
}

void PlayEvilHangman(string file) 
{
    int len = PromptWordLength();           // number of letters in word
    int guessesLeft = PromptGuesses();  //number of guesses

    cout << "Loading dictionary..." << endl << endl;

    FamilySet families( file, len );

    string guessProgress;
    string guessedLetters = "";
    string correctlyGuessed = "";	// correctly guessed positions
    string guess;

    for ( int i = 0; i < len; i++ )
        guessProgress += "*";           // make it visual for user to see the letters  not found


    // Actual game loop...
    while ( true ) {

        cout << "The Word now: " << guessProgress << endl;
        cout << "Number of guesses left: " << guessesLeft << endl;
        cout << "Guessed letters:" << guessedLetters << endl;

        if( PromptYesNoMessage( "Reveal the number of words left? " ) ){

            cout << "Number of words left: " << families.numWords() << endl;       // print number of words found remaining

        }


        // user guesses letter
        guessProgress = ChooseFamily( PromptGuess( guessedLetters ), guessProgress, families );                 // gets the new guess prgress
        families.setFamily( guessProgress );
        guessesLeft-=1;                                              // decrement guesses left



        if ( isWin( guessProgress ) ) {

            cout << "Wow! You won!" << endl;
            cout << "The word is " << guessProgress << endl;        //reveal word
            break;

        }

        if ( guessesLeft <= 0 ) {

            cout << "Wow... you are a really bad guesser..." << endl;
            cout << "The mystery word was " << families.getRandomWord() << endl;    // get random word from list left
            break;

        }

    }
}

int main()
{
    string file;
    cout << "Enter file: ";
    //cin >> file;				// Can comment out this line and include the following while developing
    file = "dictionary.txt";  // Convenient to hard code while developing
	
	while (true) {
		debug = PromptYesNoMessage("Turn debugging on?");
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again? "))
			break;
	}
}

