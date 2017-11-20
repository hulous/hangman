//============================================================================//
//                                                                            //
//  main.cpp                                                                  //
//  hangman                                                                   //
//                                                                            //
//  Created by Fabien BENARIAC on 11/11/2017.                                 //
//  Copyright © 2017 Fabien BENARIAC. All rights reserved.                    //
//                                                                            //
//  This is a simpliest hungman to restart C++ programming. ;-)               //
//                                                                            //
//============================================================================//

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int IGNORE_CHARS = 256;
const char * INPUT_ERROR_STRING = "Input error! Please try again.";

void playGame();

int getSecretPhrase(char secretPhrase[], int maxLength);
char * makeHiddenPhrase(const char * secretPhrase, int secretPhraseLength);

void drawBoard(int numberOfGuessesLeft, const char * optrHiddenPhrase);

bool wantToPlayAgain();

bool isGameOver(int numberOfGuessesLeft, const char * noptrHiddenPhrase, int secretPhraseLength);
char getGuess();
void updateBoard(char guess, char * noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & numberOfGuessesLeft);

void displayResult(const char * secretPhrase, int numberOfGuessesLeft);

void clearScreen();
void waitForKeyPress();

int main(int argc, const char * argv[]) {

  do {
    playGame();
  } while(wantToPlayAgain());

  return 0;
}

void playGame() {
  const int MAX_LENGTH_OF_SECRET_PHRASE = 256;
  const int MAX_NUMBER_OF_GUESSES = 6;

  char secretPhrase[MAX_LENGTH_OF_SECRET_PHRASE];
  char * optrHiddenPhrase = nullptr;

  int numberOfGuessesLeft = MAX_NUMBER_OF_GUESSES;
  int secretPhraseLength  = getSecretPhrase(secretPhrase, MAX_LENGTH_OF_SECRET_PHRASE);

  optrHiddenPhrase = makeHiddenPhrase(secretPhrase, secretPhraseLength);

  drawBoard(numberOfGuessesLeft, optrHiddenPhrase);

  char guess;

  do {

    guess = getGuess();
    updateBoard(guess, optrHiddenPhrase, secretPhrase, secretPhraseLength, numberOfGuessesLeft);
    drawBoard(numberOfGuessesLeft, optrHiddenPhrase);

  } while(!isGameOver(numberOfGuessesLeft, optrHiddenPhrase, secretPhraseLength));

  displayResult(secretPhrase, numberOfGuessesLeft);

  delete [] optrHiddenPhrase;

}

void drawBoard(int numberOfGuessesLeft, const char * optrHiddenPhrase) {
  clearScreen();

  switch(numberOfGuessesLeft) {
    case 0: {
      cout << " +---+"   << endl;
      cout << " |   |"   << endl;
      cout << " |   o"   << endl;
      cout << " |  /|\\" << endl;
      cout << " |  / \\" << endl;
      cout << " | "      << endl;
      cout << "-+-"      << endl << endl;
    }
    break;
    case 1: {
      cout << " +---+"   << endl;
      cout << " |   |"   << endl;
      cout << " |   o"   << endl;
      cout << " |  /|\\" << endl;
      cout << " |  / "   << endl;
      cout << " | "      << endl;
      cout << "-+-"      << endl << endl;
    }
    break;
    case 2: {
      cout << " +---+"   << endl;
      cout << " |   |"   << endl;
      cout << " |   o"   << endl;
      cout << " |  /|\\" << endl;
      cout << " | "      << endl;
      cout << " | "      << endl;
      cout << "-+-"      << endl << endl;
    }
    break;
    case 3: {
      cout << " +---+" << endl;
      cout << " |   |" << endl;
      cout << " |   o" << endl;
      cout << " |  /|" << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << "-+-"    << endl << endl;
    }
    break;
    case 4: {
      cout << " +---+" << endl;
      cout << " |   |" << endl;
      cout << " |   o" << endl;
      cout << " |   |" << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << "-+-"    << endl << endl;
    }
    break;
    case 5: {
      cout << " +---+" << endl;
      cout << " |   |" << endl;
      cout << " |   o" << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << "-+-"    << endl << endl;
    }
    break;
    case 6: {
      cout << " +---+" << endl;
      cout << " |   |" << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << " | "    << endl;
      cout << "-+-"    << endl << endl;
    }
    break;
    default:
       break;
  }

  cout << "Secret phrase: " << optrHiddenPhrase << endl << endl;
}


char * makeHiddenPhrase(const char * secretPhrase, int secretPhraseLength) {
  char* hiddenPhrase = new char[secretPhraseLength + 1];
  for (int i = 0; i < secretPhraseLength; i++) {
    if (secretPhrase[i] != ' ') {
      hiddenPhrase[i] = '-';
    } else {
      hiddenPhrase[i] = ' ';
    }
  }
  hiddenPhrase[secretPhraseLength] = '\n';
  return hiddenPhrase;
}

int getSecretPhrase(char secretPhrase[], int maxLength){
  bool failure;
  int length;

  do {
    failure = false;
    cout << "Please enter the secret phrase : ";
    cin.get(secretPhrase, maxLength);

    if (cin.fail()) {
      cin.clear();
      cin.ignore(IGNORE_CHARS, '\n');
      cout << "Input error! Please try again or report us a bug." << endl;
      failure = true;
    } else {

      length = strlen(secretPhrase);

      if (length == 0) {
        cout << "You must enter a world that is longer than 0 characters. Please try again.";
        failure = true;
      }

    }

  } while(failure);

  return length;

}

char getCharacter(const char * prompt, const char * error) { //, const char validInput[], int validInputLength) {
  char input;
  bool failure;

  do {
    failure = false;
    cout << prompt;
    cin >> input;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(IGNORE_CHARS, '\n');
      cout << error << endl;
      failure = true;
    } else {

      cin.ignore(IGNORE_CHARS, '\n');
      if (isalpha(input)) {
        input = tolower(input);
      } else {
        cout << error << endl;
        failure = true;
      }

    }

  } while(failure);

  return input;

}

char getCharacter(const char * prompt, const char * error, const char validInput[], int validInputLength) {
  char input;
  bool failure;

  do {
    failure = false;
    cout << prompt;
    cin >> input;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(IGNORE_CHARS, '\n');
      cout << error << endl;
      failure = true;
    } else {

      cin.ignore(IGNORE_CHARS, '\n');

      if (isalpha(input)) {

        input = tolower(input);
        for (int i = 0; i < validInputLength; i++) {
          if (input == validInput[i]) {
            return input;
          }
        }

      } else {
        cout << error << endl;
        failure = true;
      }

    }

  } while(failure);

  return input;
}

bool wantToPlayAgain() {
  const char validInputs[] = {'y', 'n'};
  char response = getCharacter(
    "Would you like to play again? (y/n) ",
    INPUT_ERROR_STRING,
    validInputs,
    2
  );

  return response == 'y';
}

char getGuess() {
  return getCharacter("Please input your guess: ", INPUT_ERROR_STRING);
}

void updateBoard(char guess, char * noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & numberOfGuessesLeft) {
  bool found = false;

  for (int i = 0; i < secretPhraseLength; i++) {
    if (tolower(secretPhrase[i]) == guess) {
      noptrHiddenPhrase[i] = secretPhrase[i];
      found = true;
    }
  }

  if (!found) {
    numberOfGuessesLeft--;
  }
}

bool isGameOver(int numberOfGuessesLeft, const char * noptrHiddenPhrase, int secretPhraseLength) {
  bool hasDash = false;

  for (int i = 0; i < secretPhraseLength; i++) {
    if (noptrHiddenPhrase[i] == '-') {
      hasDash = true;
      break;
    }
  }

  return numberOfGuessesLeft == 0 || !hasDash;
}

void displayResult(const char * secretPhrase, int numberOfGuessesLeft) {
  if (numberOfGuessesLeft > 0) {
    cout << "You got it! The phrase was: " << secretPhrase << endl;
  } else {
    cout << "You did not get it... The phrase was: " << secretPhrase << endl;
  }
}

void clearScreen() {
  // system("cls"); // windows
  system("clear");
}

void waitForKeyPress() {
  // system("pause"); // Windows
  system("read -n 1 -s -p \"Press any key to continue...\";echo");
}
