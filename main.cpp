/************************************************************************
Title:        Silly Simple Math Tutor
Programmer:   Tsegay Gebremeskel (Betty)
Date:         2023.12.01
Replit:
https:https://replit.com/@Betlehemgebreme/Silly-simply-math-tutor-version-3#main.cpp
Description:  The user will input there name first
This code generates a random maths question to userName
Gives the user three attempts per question to get a question wrong and correct
If user gets three questions correct they will level up
They will level down if they get three questions wrong for three attempts.
It will keep looping until user say no.
New Feature: We addeed a new feature at the end of the program where it display
the percentage of questions correct and also displays the questions correct and
incorrect. And we used setw to align the questions and answers. The average
percentage of our score is also displayed by using average percentage formaula.
+New Update+ I Betty added Functions to my code puting them in a whole new file
and removing them from the main.cpp. *NEW UPDATE* I Put in unique name files so
that what ever the user put as their name is now a new file that can get saved
if the use wants it to be saved. *NEW STUFF* I add a new ability for the user to
save their game at the end so if they want to come back they can continue where
they left off.
***********************************************************************/

#include <cctype>  // required to use tolower
#include <cstdlib> // required for srand and rand functions
#include <ctime> //required for the time function that gets the current system time
#include <fstream>   // for file i/o
#include <iomanip>   // LETS US USE setw
#include <iostream>  // required for cin & cout plus left & right alignment
#include <limits>    // required for numeric_limits
#include <stdexcept> // for rumtime errors exceptions
#include <string>    // required for the string data type
#include <vector>    // required for vectors

#include "mathtutor.h" // math tutor function to make the game work

using namespace std;

const string FILE_NAME = "mathtutor.txt"; // the file name to save the game

int main() {

  vector<vector<int>> mathQuestions;
  string userInput = "?"; // the user input for the yes or no question
  string userName = "?";  // displays the user name

  int totalCorrect = 0;   // the total number of correct answers
  int totalIncorrect = 0; // the total number of incorrect answers
  int mathLevel = 1;      // keeps tracks of the level of the user

  bool isCorrect = false; // did the user answer the current question correctly

  srand(time(0));

  DisplayGameIntro();
  userName = GetUserName();

  try {
    mathLevel = LoadPreviousGame(userName, mathQuestions);
  } catch (runtime_error &excpt) {
    cout << endl;
    cout << excpt.what() << endl;
  }

  do { // keep looping until user wants to quit

    vector<int> currentQuestion = GenerateRandomQuestion(mathLevel);

    isCorrect = GiveThreeAttempts(userName, currentQuestion);

    // used for leveling up & down
    if (isCorrect) {
      totalCorrect++;
    } else {
      totalIncorrect++;
    }

    CheckForLevelChange(totalCorrect, totalIncorrect, mathLevel);

    mathQuestions.push_back(currentQuestion); // push the row to the 2D vector

    // clear out the new line that is still in the input buffer
    getline(cin, userInput); // cleaning input buffer
    cout << endl;

    userInput =
        YesNoQuestion(userName + ", do you want to play again (yes | n=no) : ");

  } while (userInput == "yes" || userInput == "y");

  DisplaySummaryReport(mathQuestions);

  try {
    SaveCurrentGame(userName, mathQuestions);
  } catch (runtime_error &excpt) {
    cout << endl;
    cout << excpt.what() << endl;
  }

  cout << "Thank you for playing this math game " << userName
       << ". Goodbye see you another time." << endl;

  return 0;
} // end of main
