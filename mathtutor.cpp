/************************************************************************
Title:        Silly Simple Math Tutor 
Programmer:   Tsegay Gebremeskel (Betty)
Date:         2023.12.01
Replit:
https:https://replit.com/@Betlehemgebreme/Silly-simply-math-tutor-version-3#mathtutor.cpp
Description:  This file contains all the functions that the main function calls.
***********************************************************************/
#include <cstdlib>   // for srand and rand
#include <fstream>   // for file i/o
#include <iomanip>   // for report column alignment
#include <iostream>  // for cin and cout
#include <limits>    // for invalid numeric input
#include <stdexcept> // for rumtime errors exceptions
#include <string>    // for storing data types
#include <vector>    // for storing the questions in the 2D vector

using namespace std;

const int MAX_ATTEMPTS = 3; // how many attempts the user gets per question
const int LEVEL_CHANGE =
    10; // how much to increase or decrease the random number range per level

/************************************************************************
Display the Game Intro
*************************************************************************/

void DisplayGameIntro() {
  cout << "*******************************************" << endl;
  cout << "| Welcome to the Silly Simple Math tutor |" << endl;
  cout << "*******************************************" << endl;

  cout << " Welcome to the math game!" << endl;
  cout << "Fun fact:" << endl; // fun fact sign
  cout << "* The teathers have problems." << endl;
  cout << "* Math is the only subject that counts." << endl;
  cout << "* If it seems easy, you're doing it wrong." << endl;
  cout << "* It's all fun and games until someone divides bt zero!" << endl;
  cout << "*****************************************************************"
       << endl;
  cout << endl;

  return;
}

/************************************************************************
Get the user's name and welcome the user
Returns the user's name
*************************************************************************/

string GetUserName() {

  string userName = "?"; // displays the user name

  cout << "Hey there, please enter your Username: ";
  getline(cin, userName); // Gets entire line up to ENTER
  cout << "Welcome " << userName << " to the math game!" << endl;
  cout << endl;

  return userName;
}

/************************************************************************
Asking user to play again
Checks whether the input is writes valid inputs
*************************************************************************/

string YesNoQuestion(string question) {

  string userInput = "?"; // the user input for the yes or no question

  // validate y, yes, n, no
  while (true) {

    // cout << "Do you want to continue (y=yes | n=no)? ";
    cout << question;
    getline(cin, userInput);
    cout << endl;

    // lower case the users input
    for (int i = 0; i < userInput.size(); i++) {
      userInput.at(i) = tolower(userInput.at(i));
    } // endl of the loop to lower case user's input

    if (userInput == "y" || userInput == "yes" || userInput == "n" ||
        userInput == "no") {
      break; // break out of the inner while loop5

    } else {
      cout << "Invalid input! Please try again." << endl;
      cout << endl;
    } // end of if (y, yes, n , no)

  } // end of inner while loop to get valid y, yes, n , no

  return userInput;
} // end of new function

/************************************************************************
Asks user if they want to coninue the game if they have the same name as one of
last save data games
*************************************************************************/

int LoadPreviousGame(string userName, vector<vector<int>> &mathQuestions) {

  int correctAns = 0; // the correct answer is
  int leftNum = 0;  // random number between 1 -10 too keep it the question easy
  int rightNum = 0; // random number between 1 -10 too keep it the question easy
  int mathLevel = 1;      // keeps tracks of the level of the user
  int attempts = 0;       // the number of attempts the user has
  int mathSym = '?';      // +, -, *, /
  string userInput = "?"; // the user input for the yes or no question

  ifstream inFS; // input stream file handle

  inFS.open(userName + "txt"); // opens file
  if (!inFS.is_open()) {       // this checks if the file is there
    cout << "Looks like you have not played this game before." << endl;
  }

  else {
    userInput = YesNoQuestion(
        userName +
        " , it looks like you played this game before. Would you like "
        "to load your previous game (y = yes | n = no): ");

    if (userInput == "y" ||
        userInput ==
            "yes") { // if the user wants to load the file from previous game
      cout << "LOADING GAME PLEASE WAIT... " << endl;
      while (inFS >> mathLevel >> rightNum >> mathSym >> leftNum >>
             correctAns >> attempts) {
        mathQuestions.push_back(
            {mathLevel, rightNum, mathSym, leftNum, correctAns, attempts});
      }

      cout << mathQuestions.size() << " questions loaded from "
           << (userName + "txt") << endl;
      cout << "Previous game loaded successfully." << endl;
    }

    if (!inFS.eof()) { // if the file ever has an error with loading the
                       // previous game
      throw runtime_error("Something went wrong with the reading the " +
                          (userName + "txt") + " file.");
    }

    inFS.close(); // closes input file stream
  }
  
  return mathLevel;
}

/************************************************************************
Generate each random question
Returns the current question's data type as a in vector
returns{mathLevel, leftNum, mathSym, rightNum, correctAns}
*************************************************************************/

vector<int> GenerateRandomQuestion(int mathLevel) {

  enum MathType { MT_ADD = 1, MT_SUB = 2, MT_MUL = 3, MT_DIV = 4 };

  MathType mathType = MT_ADD;

  int correctAns = 0; // the correct answer is
  int leftNum = 0;  // random number between 1 -10 too keep it the question easy
  int rightNum = 0; // random number between 1 -10 too keep it the question easy
  int temNum = 0;   // used to store the leftNum and rightNum

  char mathSym = '?'; // +, -, *, /

  // random number between 1 -10 too keep it the question easy
  leftNum = (rand() % (mathLevel * LEVEL_CHANGE)) + 1;
  // random number between 1 -10 too keep it the question easy
  rightNum = (rand() % (mathLevel * LEVEL_CHANGE)) + 1;
  // random number between 1 - 4 [1=add,2=sub, 3=multi, 4=div]
  mathType = static_cast<MathType>(rand() % 4 + 1);

  // always make the left number greater than the right number
  if (leftNum < rightNum) {
    temNum = leftNum;
    leftNum = rightNum;
    rightNum = temNum;
  }

  switch (mathType) {
  case MT_ADD: // Addition
    correctAns = leftNum + rightNum;
    mathSym = '+';
    break;

  case MT_SUB: // Subtraction
    correctAns = leftNum - rightNum;
    mathSym = '-';
    break;

  case MT_MUL: // Multiplication
    correctAns = leftNum * rightNum;
    mathSym = '*';
    break;

  case MT_DIV: // Division is different to avoid fractions
    correctAns = leftNum;
    leftNum *= rightNum;
    mathSym = '/';
    break;

  default:
    cout << "Invaild question type:" << mathType << endl;
    cout << "Program ended with an error -1" << endl;
    cout << "Please report this error to Betty" << endl;
    exit(-1);

  } // end of the switch

  return {mathLevel, leftNum, mathSym, rightNum, correctAns};
}
/******************************************************************************
It makes the user type a number and if is correct it will return true and if not
it will tell them it is invalid
******************************************************************************/
int GetNumericValue() {

  int userAnswer = 0; // whatever the user inputs

  // loop until the user enters numeric data
  while (!(cin >> userAnswer)) {
    cin.clear(); // clear the cin error flag
    // need to include the limits library to use numeric_limits
    cin.ignore(numeric_limits<streamsize>::max(),
               '\n'); // ignore the max input, up to '\n'
    cout << "Invalid input!" << endl;
    cout << "Please enter a number: ";
  } // end of get userAnswer while loop

  return userAnswer;
}

/************************************************************************
Give the user 3 attempts to answer the question correctly
Returns true if they answered it correctly otherwise false
*************************************************************************/

bool GiveThreeAttempts(string userName, vector<int> &currentQuestion) {

  int userAnswer = 0; // whatever the user inputs
  bool isCorrect = false;

  int mathLevel = currentQuestion.at(0);
  int leftNum = currentQuestion.at(1);
  char mathSym = static_cast<char>(currentQuestion.at(2));
  int rightNum = currentQuestion.at(3);
  int correctAns = currentQuestion.at(4);

  for (int i = MAX_ATTEMPTS; i > 0; i--) {

    cout << "["
         << "Level #" << mathLevel << "] " << userName << " what is " << leftNum
         << " " << mathSym << " " << rightNum << " = ";

    userAnswer = GetNumericValue();

    if (userAnswer == correctAns) { // this gives the user a sentence that
                                    // says they are correct
      currentQuestion.push_back(MAX_ATTEMPTS - i +
                                1); // push the attempts to the end
      cout << "  Congrats! You got it right." << endl;
      isCorrect = true;
      break;
    } // end of if statemnet

    else {
      cout << "Bummer, "
           << "your answer is incorrect." << endl;
      cout << "You have " << i - 1 << " attempt (s) left." << endl;
      isCorrect = false;
      if (i == 1) { // beginning of the if statement
        cout << "Sorry you are out of attempts." << endl;
        cout << "The correct answer is " << correctAns << endl;
        currentQuestion.push_back(
            0); // Tells us if the above code has been
                // it tells us if the above code initialized

      } // end of if statment
    }   // end of the else statement
  }
  return isCorrect;
}

/************************************************************************
It changes the level of the question if three answesrs are correct
Levels down if the user gets three attempts wrong
*************************************************************************/

void CheckForLevelChange(int &totalCorrect, int &totalIncorrect,
                         int &mathLevel) {

  if (totalCorrect ==
      3) { // this loop does the ending sentence if the user gets 3 correct
           // answers right and then it will level them up
    mathLevel++;
    totalCorrect = 0;
    totalIncorrect = 0;
    cout << endl;
    cout << "Hurrayyyyyyyyyyyyy! Leveling you UP to " << mathLevel << endl;
    cout << "The numbers are now between 1 and " << (mathLevel * LEVEL_CHANGE)
         << endl;

  } else if (totalIncorrect == 3 &&
             mathLevel > 1) { // this loop does the ending sentence if the user
                              // gets 3 wrong and level then level down
    mathLevel--;
    totalIncorrect = 0;
    totalCorrect = 0;
    cout << endl;
    cout << "BooHoo - Leveling you DOWN to " << mathLevel << endl;
    cout << "The numbers are now between 1 and " << (mathLevel * LEVEL_CHANGE)
         << endl;
  }
  return;
}

/************************************************************************
Displays the summary reports
Returns the total correct and total incorrect
Returns the average of the questions answered correctly
*************************************************************************/

void DisplaySummaryReport(const vector<vector<int>> &mathQuestions) {
  int correctAns = 0; // the correct answer is
  int leftNum = 0;  // random number between 1 -10 too keep it the question easy
  int rightNum = 0; // random number between 1 -10 too keep it the question easy
  int totalCorrect = 0;   // the total number of correct answers
  int totalIncorrect = 0; // the total number of incorrect answers
  int mathLevel = 1;      // keeps tracks of the level of the user
  int attempts = 0;       // the number of attempts the user has

  char mathSym = '?'; // +, -, *, /

  totalCorrect = 0;
  totalIncorrect = 0;

  cout << "=====================================" << endl;
  cout << "          "
       << "Summary Report" << endl;
  cout << "=====================================" << endl;
  cout << "Level"
       << "      "
       << "Question"
       << "        "
       << "Attempts" << endl;
  cout << "-----  -------------------  ---------" << endl;

  for (int i = 0; i < mathQuestions.size(); i++) {
    // pull the current rows data out into more readable variables

    mathLevel = mathQuestions.at(i).at(0); // grabs the level from the 2D vector
    leftNum =
        mathQuestions.at(i).at(1); // grabs the left number from the 2D vector
    mathSym = static_cast<char>(mathQuestions.at(i).at(
        2)); // convert the numeric values for +, -, *, / bacl to a char
    rightNum =
        mathQuestions.at(i).at(3); // grabs the right number from the 2D vector
    correctAns = mathQuestions.at(i).at(
        4); // grabs the correct answer from the 2D vector
    attempts =
        mathQuestions.at(i).at(5); // grabs the attempts from the 2D vector

    cout << right << setw(4) << mathLevel << "  " << setw(4) << leftNum << " "
         << mathSym << " " << left << setw(3) << rightNum << " =  " << right
         << setw(5) << correctAns;

    if (attempts != 0) {
      cout << "       " << attempts << endl;
      totalCorrect++;
    } else {
      cout << "   Incorrect" << endl;
      totalIncorrect++;
    } // end of if (attempts != 0)
  }   // end of for loop

  cout << endl;
  cout << "Total Questions: " << setw(3) << mathQuestions.size()
       << endl; // displays the total questions
  cout << "Total Correct:   " << setw(3) << totalCorrect
       << endl; // displays the total correct
  cout << "Total Incorrect: " << setw(3) << totalIncorrect
       << endl; // displays the total incorrect
  cout << "Average:         " << setw(3)
       << (totalCorrect * 100) / mathQuestions.size() << "%"
       << endl; // // displays the average correct percentage
  cout << endl;

  return;
} // end DisplaySummaryReport function

/************************************************************************
The function saves the current game to a file
************************************************************************/

void SaveCurrentGame(string userName,
                     const vector<vector<int>> &mathQuestions) {

  string userInput = "?"; // the user input for the yes or no question

  ofstream outFS; // output file stream hanlde

  userInput = YesNoQuestion(
      userName + " , do you want to save your game (y=yes | n=no): ");

  if (userInput == "y" || userInput == "yes") { // beginning of the if statement
    cout << "Saving game please wait" << endl;
    outFS.open((userName + "txt"));
    if (!outFS.is_open()) {
      throw runtime_error("Could not open file " + (userName + "txt") +
                          " for writing");
    }                                                // end of if statement
    for (int i = 0; i < mathQuestions.size(); i++) { // begining of for loop
      outFS << mathQuestions.at(i).at(0) << " " << mathQuestions.at(i).at(1)
            << " " << mathQuestions.at(i).at(2) << " "
            << mathQuestions.at(i).at(3) << " " << mathQuestions.at(i).at(4)
            << " " << mathQuestions.at(i).at(5) << " " << endl;
    }              // end of the for loop
    outFS.close(); // closes the output file steam

    cout << mathQuestions.size() << " Game saved successfully."
         << (userName + "txt") << endl;
  }

  return;
}
