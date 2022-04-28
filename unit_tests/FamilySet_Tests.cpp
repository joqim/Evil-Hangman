//
// Created by Varick Erickson on 4/11/2021.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <vector>
#include <set>
#include <stdlib.h>
#include "../FamilySet.h"

TEST_CASE("FamilySet Tests") {
    SECTION("Default Constructor - 3pt") {

        ifstream famFile;
        famFile.open("test_data/family_sizes.txt");
        if (famFile.fail()) {
            INFO("family_sizes.txt did not open.");
            INFO("Did you set the working directory?");
            INFO("Did you move the file?");
            FAIL();
        }

        vector<int> famSizes;
        int sz;
        while(famFile >> sz) {
            famSizes.push_back(sz);
        }

        for (int wordLen = 0; wordLen < 30; wordLen++) {
            FamilySet testSet("dictionary.txt", wordLen);
            REQUIRE(testSet.numWords() == famSizes[wordLen]);
        }

    }

    SECTION("filterFamilies no pattern - 15pt") {

        for (char letter = 'a' ; letter <= 'b'; letter++) {
            for (int wordLen = 10; wordLen <= 20; wordLen++) {
                ifstream famFile;
                string outName = "test_data/family_" + to_string(wordLen) + "_"+letter+"_no_pattern.txt";
                famFile.open(outName);
                set<string> families;
                string line = " ";
                while (famFile >> line) {
                    families.insert(line);
                }

                FamilySet testSet("dictionary.txt", wordLen);

                string pattern = "";
                for (int i = 0; i < wordLen; i++) {
                    pattern += "*";
                }
                line = " ";
                line[0] = letter;
                cout << line << "\t" << pattern << endl;
                testSet.filterFamilies(line, pattern);

                testSet.resetFamilyIter();
                for (int i = 0; i < testSet.numFamilies(); i++) {
                    string family = testSet.getNextFamily();
                    REQUIRE(families.count(family) == 1);
                }
                famFile.close();
            }
        }
    }

    SECTION("setFamily - 2pt") {

        FamilySet testSet("dictionary.txt", 5);

        testSet.filterFamilies("a", "*****");   // First filter
        testSet.setFamily("*****");

        vector<string> words = testSet.getWords();

        ifstream famFile;
        string outName = "test_data/setfamily_words_a_no_pattern.txt";
        famFile.open(outName);

        string word;
        int i = 0;
        while (famFile >> word) {
            REQUIRE(word == words[i++]);
        }
    }

    SECTION("filterFamiles with pattern - 15pt") {

        FamilySet testSet("dictionary.txt", 5);

        testSet.filterFamilies("a", "*****");   // First filter
        testSet.setFamily("a***a");

        testSet.filterFamilies("b", "a***a");   // Second filter

        vector<string> words = testSet.getWords();

        ifstream famFile;
        string outName = "test_data/setfamily_words_b_with_pattern.txt";
        famFile.open(outName);

        string word;
        int i = 0;
        while (famFile >> word) {
            REQUIRE(word == words[i++]);
        }
        famFile.close();

//        testSet.resetFamilyIter();
//        for (int i = 0; i < testSet.numFamilies(); i++) {
//            cout << testSet.getNextFamily() << endl;
//        }
    }

}