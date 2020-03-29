#include "GenStack.h"
#include <fstream>
#include <iostream>

using namespace std;

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
  }

  ifstream inputFile{argv[1]};
  GenStack<char> openDelims;

  //// Travel through file character by character
  char ch;
  int line = 1;
  // Don't skip whitespace, so that newline characters can be counted to keep track
  // of the line number
  while (inputFile >> noskipws >> ch) {
    // If the current character is an opening bracket
    if (ch == '(' || ch == '{' || ch == '[') {
      // cout << ch << endl;

      openDelims.push(ch);
    }
    // If the current character is a closing bracket
    else if (ch == ')' || ch == '}' || ch == ']') {
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
  }

  //// Check if the file ends without the proper delimiters
  if (!openDelims.isEmpty()) {
    char missing = calcCloseDelim(openDelims.pop());
    cout << "Reached end of file: missing " << missing << endl;

    inputFile.close();
    return 1;
  }

  inputFile.close();

  return 0;
}