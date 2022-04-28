#include <iostream>
#include "FamilySet.h"
#include <fstream>
using namespace std;

string FamilySet::getRandomWord()
{
    int ind = rand() % wordlist->size();
    return wordlist->at(ind);
}

int FamilySet::numWords()
{
    // This should return the number of words in the master list
    return wordlist->size();
}

int FamilySet::numFamilies()
{
    return dictionaries.size();
}

vector<string> FamilySet::getWords() {
    return *wordlist;
}

FamilySet::FamilySet(string dictFile, int len) {
    cout<<"\n Inside FamilySet constructor";
    cout<<"\n length"<<len;

    wordlist = new vector<string>;
    ifstream myFile(dictFile);

    //myFile.open();
    //myFile.open(dictFile);
    if(!myFile)
    {
        cout << "Could not find file!\n";
        exit(0);
    }
    else
    {
        while(!myFile.eof())
        {
            string word;
            myFile >> word;
            if(word.size() == len) {
                wordlist->push_back(word);
            }
        }
    }
    //cout << wordlist->size() << " words were found.\n";
    myFile.close();
}

FamilySet::~FamilySet() {

}

void FamilySet::filterFamilies(string letter, string guessPattern) {
    dictionaries.clear();
    for( auto it = wordlist->begin(); it != wordlist->end(); ++it ){

        string MasterWord = *it;
        string NewPattern = guessPattern;
        vector<string>* NewVector = new vector<string>();

        int f = 0;
        while(f < NewPattern.length()){
            if(MasterWord[f] == letter[0]){
                NewPattern[f] = letter[0];
            }
            f++;
        }

        if(dictionaries.find(NewPattern) != dictionaries.end()){
            dictionaries[NewPattern]->push_back(MasterWord);
        }
        else{
            dictionaries[NewPattern] = NewVector;
            //dictionaries[NewPattern]->push_back(MasterWord);
        }
    }
}

void FamilySet::setFamily(string family) {
    resetFamilyIter();
    wordlist = getFamily(family);
    //famIter = familySize(family);

    // This updates the master list.  The new master list
    // should contain the words within the dictionary for family.
    // dictionaries should be cleared after updating the master list.
}

vector<string>* FamilySet::getFamily(string family) {
    vector<string>* dictionary = dictionaries[family];
    return dictionary;
}

int FamilySet::familySize(string family) {
    // Returns the size of the dictionary of family
    int FamSize = dictionaries[family]->size();
    return FamSize;
}

void FamilySet::resetFamilyIter() {
    wordlist->clear();
    famIter = dictionaries.begin();
}

string FamilySet::getNextFamily() {
    int TopFamily = 0;
    string TopFamString;

    for ( pair<string, vector <string>*> elem :dictionaries){

        if(familySize(elem.first)> TopFamily){

            TopFamily = familySize(elem.first);
            TopFamString = elem.first;

        }

    }

    return TopFamString;
}

bool FamilySet::hasNext() {
    return false;
}
