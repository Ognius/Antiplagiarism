#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

#define ZERO       0
#define THREE      3
#define THIRTY_TWO 32
#define HUNDRED    100
#define CHARACTERS 1024

using namespace std;
using namespace cgicc;

char* getCharArrayFromString(string text);
void setNormalizeText(char* text);
bool isCapitalLetter(char letter);
void splitString(char* text, int startWordPosition = 0, int count = 1);
bool isMatchString(char* originalText, char* fragment);
void getResult(char* fragment, char* originalText, int matchCount, double& unique);
void strCopy(char firstString[], char secondString[]);
int strLength(char string[]);
int countWords(char* text);
double getUniquePercent(double match, double iterations);

string getDB();

int main()
{
    Cgicc form;
    string name;
    double unique = 0.0;
    
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Ggi Server</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<p>";
    
    name = form("name");
    getResult(getCharArrayFromString(name), getCharArrayFromString(getDB()), 3, unique);
    if (!name.empty()) {
    	cout << unique << "\n";
    } else {
    	cout << "Text is not provided!\n";
    }	
    cout << "</p>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}

char* getCharArrayFromString(string text){
	char* textArray = new char[text.length()];
	for(int i = 0; i < text.length(); i++){
		textArray[i] = text[i];
	}
	return textArray;
}

string getDB(){
	std::ifstream in("db.txt");

    string dbText = "", s1;
    while (getline(in, s1))
    	dbText += s1;
  
    in.close();
    
    return dbText;
}

void setNormalizeText(char* text) {
	for (int i = 0; text[i] != '\0'; i++) {
		if ((text[i] >= 'A' and text[i] <= 'Z') or (text[i] >= 'a' and text[i] <= 'z')) {
			if (isCapitalLetter(text[i]))
				text[i] += THIRTY_TWO;
		}
		else
			text[i] = ' ';
	}
}

bool isCapitalLetter(char letter) {
	if (letter >= 'A' and letter <= 'Z')
		return true;
	return false;
}

void getResult(char* fragment, char* originalText, int matchCount, double& unique) {
	int i = 0, j = 0, iterationCount = 0, numberWord = 0;
	double result = 0.0;

	setNormalizeText(originalText);	
	setNormalizeText(fragment);

	char copyFragment[CHARACTERS];
	char copyFragmentIteration[CHARACTERS];
	char copyOriginalText[CHARACTERS];
	char copyOriginalTextIteration[CHARACTERS];	

	strCopy(copyFragment, fragment);	
	strCopy(copyFragmentIteration, fragment);	
	strCopy(copyOriginalText, originalText);
	splitString(copyOriginalTextIteration);
	
	while (strLength(copyFragmentIteration) > 0) {
		iterationCount++;
		splitString(copyFragment, i, matchCount);
		strCopy(copyOriginalTextIteration, originalText);
		splitString(copyOriginalTextIteration);	
		while (strLength(copyOriginalTextIteration) > 0) {
			splitString(copyOriginalText, j, matchCount);
			if (isMatchString(copyOriginalText, copyFragment))
				result++;
			strCopy(copyOriginalText, originalText);
			strCopy(copyOriginalTextIteration, originalText);
			j++;
			splitString(copyOriginalTextIteration, j);
			numberWord = countWords(originalText) - j;
            if (numberWord < THREE)
                break;
		}
		strCopy(copyFragment, fragment);
		strCopy(copyFragmentIteration, fragment);
		i++;
		j = 0;
		splitString(copyFragmentIteration, i);
		numberWord = countWords(fragment) - i;
		if (numberWord < THREE)
		    break;
	}
	unique = getUniquePercent(result, iterationCount);	
}

void splitString(char* text, int startWordPosition, int count) {
	char buf[CHARACTERS];
	int length = 0, word = 0, i = 0, j = 0;
	bool flag = false;

	count += startWordPosition;	
	while (text[i] != '\0') {
		while (text[i] == ' ') {
			if (!flag)
				word++;
			flag = true;
			i++;
		}
		flag = false;
		if (count == word)
			break;
		if (startWordPosition <= word) {
			buf[j] = text[i];			
			length++;
			j++;
		}
		i++;
	}
	for (i = 0; text[i] != '\0'; i++)	{
		if (i < length)
			text[i] = buf[i];
		else
			text[i] = '\0';
	}
}

int countWords(char* text) {
	int word = 0;
	bool flag = false; 
		
  	for (int i = 0; text[i] != '\0'; i++) {
  		if (text[i] != ' ' and flag == false) {
  			word++;
  			flag = true;
  		}
  		else {
  			if (text[i] == ' ')
  				flag = false;
  		}  			
  	}
  	return word;
}

bool isMatchString(char* originalText, char* fragment) {
	if (strLength(originalText) != strLength(fragment))
		return false;
		
	for (int i = 0; originalText[i] != '\0'; i++) {
		if (originalText[i] != fragment[i])
			return false;
	}
	return true;
}

void strCopy(char firstString[], char secondString[]) {
	int length = strLength(secondString);

	for (int i = 0; i <= length; i++) {
		if (i == length)
			firstString[i] = '\0';
		firstString[i] = secondString[i];
	}
}

int strLength(char string[]) {
	int counter = 0;

	while (string[counter] != '\0')
		counter++;

	return counter;
}

double getUniquePercent(double match, double iteration) {
	double result = 0.0;

	if (!match)
		return HUNDRED;
	if (match > iteration)
	    return ZERO;

	result = (iteration - match) / iteration * HUNDRED;
	return result;
}
