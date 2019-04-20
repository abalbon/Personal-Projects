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
  string tt;
  string lexeme;
public:
  Token();
  Token(string tt, string lexeme);
  void printToken();
};

// Function that checks to see if a lexeme is a keyword
bool isKeyword(string keywordLex);
// Function that checks to see if a lexeme is an operator
bool isOperator(char operatorLex);
// Function that checks to see if a lexeme is a delimiter
bool isDelimiter(char delimiterLex);
// Functino that checks to see if a lexeme is a floating point
bool isFloat(string floatLex);
// Lexical Analyzer that returns a vector of tokens
vector<Token> lexer(vector<char> charsFromFile);

int main()
{
  vector<Token> vectorOfElements;       // Vector of Tokens and Lexemes
  vector<char> vectorOfCharFromFile;    // Vector of characters from the text
                                        // text file obtained from the user
  vector<char> vectorOfIgnoredComments; // Vector of characters that include all
                                        // ignored comments in the text file
  char currentChar;                     // indexer
  string userEntry = "";
  int ignoredIndex = 0;                 // indexer for ignored comments
  ifstream infile;

  // User input for a text file to do a lexical analysis
  do {
    cout << "Enter text file to enter: ";
    getline(cin, userEntry);
    infile.open(userEntry);

    if(!infile)
    {
      cout << "**Error, file could not be found, please re-enter**\n\n";
    }

  } while(!infile); // End of do...while


  // While loop that reads in all characters from a file
  while(!infile.eof())
  {
    infile.get(currentChar);

    // Various If statements to ignore comments in the text file
    if(currentChar == '!')
    {
      vectorOfIgnoredComments.push_back(currentChar);
      infile.get(currentChar);

      while(currentChar != '!')
      {
        vectorOfIgnoredComments.push_back(currentChar);
        infile.get(currentChar);
      }
    }

    // if statement that finds the end of the comment section
    if(currentChar == '!')
    {
        vectorOfIgnoredComments.push_back(currentChar);
    }
    else
    {
      vectorOfCharFromFile.push_back(currentChar);
    }
  }

  infile.close(); // closes the text file

  // Lexer function is called to a lexical analysis on the vector
  vectorOfElements = lexer(vectorOfCharFromFile);

  // Output Formatting
  cout << "\n----------------";
  cout << "\nLexical Analysis";
  cout << "\n----------------\n";
  cout <<  setw(15) << left << "Keyword" << "Lexeme\n";
  cout << "---------------------\n";

  // For loop that outputs all the analyzed lexemes that are in the vector
  for(int zi = 0; zi < vectorOfElements.size(); zi++)
  {
    vectorOfElements.at(zi).printToken();
    cout << endl;
  }

  return 0;
}

// Token Constructor
Token::Token(string tt, string lexeme)
{
  this->tt = tt;
  this->lexeme = lexeme;
}
// Class function that prints out a single element
void Token::printToken()
{
  cout << setw(15) << left << tt << lexeme;
}

// Function that checks to see if a lexeme is a keyword
bool isKeyword(string keywordLex)
{
  ifstream infile;
  string currentStr;
  bool isKeyword = false;
  infile.open("validKeywords.txt"); // opens text file of valid keywords


  if(!infile)
  {
    cout << "\n**Error, File not opened**\n";
  }
  else
  {
    // checks the file if the passed in string is a valid keyword
    while(!infile.eof())
    {
      getline(infile,currentStr);
      if(currentStr == keywordLex)
      {
        isKeyword = true;
        return isKeyword;
      }
    }
  }
  return isKeyword;
}

// Function that checks is a lexeme is an operator
bool isOperator(char operatorLex)
{
  ifstream infile;
  char currentChar;
  bool isOperator = false;
  infile.open("validOperators.txt"); // opens a file of valid operators

  if(!infile)
  {
    cout << "\n**Error, File not opened**\n";
  }
  else
  {
    // Checks the text file of valid operators to see if it is an operator
    while(!infile.eof())
    {
      infile.get(currentChar);
      if(currentChar == operatorLex)
      {
        isOperator = true;
        return isOperator;
      }
    }
  }

  return isOperator;
}

// Checks if a lexeme is a separator
bool isDelimiter(char delimiterLex)
{
  ifstream infile;
  char currentChar;
  bool isDelimiter = false;
  infile.open("validSeparators.txt"); // opens a file of valid separators

  if(!infile)
  {
    cout << "\n**Error, File not opened**\n";
  }
  else
  {
    // checks the text file to see if a lexeme is a valid separator
    while(!infile.eof())
    {
      infile.get(currentChar);
      if(currentChar == delimiterLex)
      {
        isDelimiter = true;
        return isOperator;
      }
    }
  }
  return isDelimiter;
}

// Checks if a number is a floating point
bool isFloat(string floatLex)
{
  int i = 0;

  // iterates through the string to check if it is a floating point or an int
  for(string::iterator it = floatLex.begin(); it != floatLex.end(); ++it)
  {
    if(*it == '.')
    {
      return true;
    }

  }

  return false;
}

// Lexer function
vector<Token> lexer(vector<char> charsFromFile)
{
  vector<Token> vectorOfElements;
  string element = "";
  int vi = 0;

  // while loop that iterates through every single character
   while(vi < charsFromFile.size())
   {
     // ignores if the character is a space
     if(isspace(charsFromFile.at(vi)))
     {
       vi++;
     }
     // checks if a character is an int or a floating point
     else if(isdigit(charsFromFile.at(vi)))
     {
       element = "";
       while(isdigit(charsFromFile.at(vi)) || charsFromFile.at(vi) == '.')
       {
         element += charsFromFile.at(vi);
         vi++;
       }

       // checks if it is floating point
       if(isFloat(element) == true)
       {
         Token newToken("Float", element);
         vectorOfElements.push_back(newToken);
         element = "";
       }
       else
       {
         Token newToken("Integer", element);
         vectorOfElements.push_back(newToken);
         element = "";
       }


     }
     // Checks if the character is an alphabetical character
     else if(isalpha(charsFromFile.at(vi)))
     {
       element = "";
       // add each character to the string as long as it is a valid character
       while(isalnum(charsFromFile.at(vi)) || charsFromFile.at(vi) == '$')
       {
         element += charsFromFile.at(vi);
         vi++;
       }

       // checks if it is a keyword
       if(isKeyword(element) == true)
       {
         Token newToken("Keyword",element);
         vectorOfElements.push_back(newToken);
         element = "";
       }
       else // otherwise it is considered an identifier
       {
         Token newToken("Identifier",element);
         vectorOfElements.push_back(newToken);
         element = "";
       }

     }
     // checks if the character is an operator
     else if(isOperator(charsFromFile.at(vi)) == true)
     {
       element = "";
       element += charsFromFile.at(vi);
       Token newToken("Operator", element);
       vectorOfElements.push_back(newToken);
       element = "";
       vi++;
     }
     // checks if the character is a separator
     else if (isDelimiter(charsFromFile.at(vi)) == true)
     {
       element = "";
       element += charsFromFile.at(vi);
       Token newToken("Separator", element);
       vectorOfElements.push_back(newToken);
       element = "";
       vi++;
     }
     // otherwise an error has occured and it is not a valid character
     else
     {
       vi++;
     }
 }

   return vectorOfElements;
}
