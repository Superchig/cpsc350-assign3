#include "GenStack.h"
#include <fstream>
#include <iostream>

using namespace std;

// Gives the corresponding closing delimiter for a given opening delimiter
char calcCloseDelim(char openDelim)
{
  switch (openDelim) {
  case '(':
    return ')';
    break;
  case '{':
    return '}';
    break;
  case '[':
    return ']';
    break;
  default:
    cerr << "Error: Tried to find closing delimeter for non-opening delimeter "
         << openDelim << endl;
    return '\0';
    break;
  }
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    cerr << "Error: Must give only the location of a source code file to be "
            "analyzed."
         << endl;
    return 1;
  }

  string inputFileName = argv[1];

  //// Loop that runs like files are still being evaluated
  while (true) {
    ifstream inputFile{inputFileName};
    GenStack<char> openDelims;

    if (!inputFile.is_open()) {
      cerr << "Error: Could not open " << inputFileName << endl;
      return 1;
    }

    //// Travel through file character by character
    char ch;
    char prevCh = '\0';
    char nextCh = '\0';
    int line = 1;

    // Don't skip whitespace, so that newline characters can be counted to keep
    // track of the line number
    while (inputFile >> noskipws >> ch) {
      nextCh = inputFile.peek();

      // Checks if the current char is in quotes.
      // If the next character is EOF, then we are at the last character in the
      // file, so we are not in quotes.
      bool isQuoted = (nextCh != EOF) && ((prevCh == '\'' && nextCh == '\'') ||
                                          (prevCh == '"' && nextCh == '"'));

      // If the current character is an opening bracket
      if ((ch == '(' || ch == '{' || ch == '[') && !isQuoted) {
        // cout << ch << endl;

        openDelims.push(ch);
      }
      // If the current character is a closing bracket
      else if ((ch == ')' || ch == '}' || ch == ']') && !isQuoted) {
        char mostRecentOpen = openDelims.pop();
        char expectedDelim = calcCloseDelim(mostRecentOpen);

        if (ch != expectedDelim) {
          cout << "Line " << line << ": expected " << expectedDelim << endl;
          cout << "\tbut got " << ch << endl;

          inputFile.close();
          return 1;
        }

        // cout << "Found correct closing bracket." << endl;
      }
      else if (ch == '\n') {
        ++line;
      }

      // Update prevCh so that it can be used on the next iteration of the loop
      prevCh = ch;
    }

    //// Check if the file ends without the proper delimiters
    if (!openDelims.isEmpty()) {
      char missing = calcCloseDelim(openDelims.pop());
      cout << "Reached end of file: missing " << missing << endl;

      inputFile.close();
      return 1;
    }

    inputFile.close();

    //// Ask if another file should be analyzed
    cout << "That file had no errors." << endl;
    cout << "Do you want to analyze another file? (y/n) ";
    string choice;
    cin >> choice;

    if (choice == "y") {
      cout << "Input name of file: ";
      cin >> inputFileName;
    }
    else {
      cout << "Exiting..." << endl;
      break;
    }
  }

  return 0;
}
