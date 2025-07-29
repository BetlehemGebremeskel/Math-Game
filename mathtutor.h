/************************************************************************
Title:        Silly Simple Math Tutor 
Programmer:   Tsegay Gebremeskel (Betty)
Date:         2023.12.01
Replit:
https://replit.com/@Betlehemgebreme/Silly-simply-math-tutor-version-3#mathtutor.h
Description:  This file contains all the prototypes for the function that the
main function calls.
***********************************************************************/

#ifndef MATHTUTOR_H
#define MATHTUTOR_H

#include <string> // for string data types
#include <vector> // for storing the question in a 2D vector

using namespace std;

void DisplayGameIntro(); // this is the 
string GetUserName();
int LoadPreviousGame(string userName, vector<vector<int>> &mathQuestions);
vector<int> GenerateRandomQuestion(int mathLevel);
int GetNumericValue();
bool GiveThreeAttempts(string userName, vector<int> &currentQuestion);
void CheckForLevelChange(int &totalCorrect, int &totalIncorrect,
                         int &mathLevel);
string YesNoQuestion(string question);
void DisplaySummaryReport(const vector<vector<int>> &mathQuestions);
void SaveCurrentGame(string userName, const vector<vector<int>> &mathQuestions);


#endif
