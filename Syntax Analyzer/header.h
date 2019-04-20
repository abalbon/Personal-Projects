#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

// Token Class that contains the token and the lexeme
class Token
{
private:
  string tt;      // Token type
  string lexeme;  // actual lexeme
public:
  // Token default constructor
  Token(){}
  // Token Constructor
  Token(string tt, string lexeme)
  {
    this->tt = tt;
    this->lexeme = lexeme;
  }
  // Class function that prints out a single element
  void printToken()
  {
    cout << setw(15) << left << tt << lexeme << endl;
  }
  // Get token type
  string getTokenType()
  {
    return tt;
  }
  // Get Lexeme
  string getLex()
  {
    return lexeme;
  }
};

// Recursive Decent Parser class
class RDP
{
private:
  vector<Token> listOfTokens;             // List of tokens from the lexer
  int tokenIndex;                         // indexer for the listOfTokens vector
  vector<string> listOfProductionRules;   // container for the list of
                                          //  production rules
public:
  // Default Constructor
  RDP(){}
  // Alternate Constructor
  RDP(vector<Token> listOfTokens)
  {
    this->listOfTokens = listOfTokens;
    tokenIndex = 0;
  }
  // Retrieves the current index
  int getIndex()
  {
    return tokenIndex;
  }
  // Prints all the production rules that was used
  void printProductionRules()
  {
    for(int i = listOfProductionRules.size() - 1; i != -1; i--)
    {
      cout << listOfProductionRules.at(i) << endl;
    }
  }
  // function call that will parse the expression
  void parse()
  {
    // While loop so that it will continue to parse as long as it is not out
    // of range
    while(tokenIndex < listOfTokens.size())
    {
      // Checks to see if E() is false since it will signify an error
      if(E() == false)
      {
        // clears the list of production rules vector
        listOfProductionRules.clear();

        // output statement for the error
        cout << "\n\nFailure\n";

        // shows where the error occured and at which lexeme
        cout << "There was no production rule for: "
             << listOfTokens.at(tokenIndex).getLex() << endl;
        break;
      }
      else
      {
        // prints the current lexem being processed
        listOfTokens.at(tokenIndex).printToken();
        // outputs all the production rules
        printProductionRules();
        cout << "--------------------------------------" << endl;
        listOfProductionRules.clear();
        // goes to the next lexeme
        tokenIndex++;
      }
    }
  }

  //Production Rules loosely based of the CPSC 323 book
  bool E()
  {
    bool e = false;

    if(T())
    {
      listOfProductionRules.push_back("E --> TQ");
      e = true;
    }
    if(Q())
    {
      listOfProductionRules.push_back("E --> TQ");
      e = true;
    }
    return e;
  }

  bool Q()
  {
    bool q = false;

    if(listOfTokens.at(tokenIndex).getLex() == "+")
    {
        listOfProductionRules.push_back("Q --> +TQ");
        q = true;
    }
    if(listOfTokens.at(tokenIndex).getLex() == "-")
    {
        listOfProductionRules.push_back("Q --> -TQ");
        q = true;
    }
    return q;

  }

  bool T()
  {
    bool t = false;

    if(F())
    {
      listOfProductionRules.push_back("T --> FR");
      t = true;
    }
    if(R())
    {
      listOfProductionRules.push_back("T --> FR");
      t = true;
    }
    return t;
  }

  bool R()
  {
    bool r = false;

    if(listOfTokens.at(tokenIndex).getLex() == "*")
    {
      listOfProductionRules.push_back("R --> *FR");
      r = true;
    }
    if(listOfTokens.at(tokenIndex).getLex() == "/")
    {
      listOfProductionRules.push_back("R --> /FR");
      r = true;
    }
    return r;
  }

  bool F()
  {
    bool f = false;
    if(listOfTokens.at(tokenIndex).getTokenType() == "Identifier")
    {
      listOfProductionRules.push_back("F --> id");
      f = true;
    }
    if(listOfTokens.at(tokenIndex).getLex() == "(" ||
       listOfTokens.at(tokenIndex).getLex() == ")")
    {
      listOfProductionRules.push_back("F --> (E)");
      f = true;
    }
    return f;
  }
};

#endif
