/*
file Name: decode.cpp
Coder: Sonia Friesen
Date: April 1, 2019
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;


int main(int argc, char * argv[])
{
	//validate command line args
	if (argc > 4)
	{
		cerr << "Error, too  many arguments\n";
		return EXIT_FAILURE;
	}
	if (argc < 4)
	{
		cerr << "Error, not enough arguments\n";
		return EXIT_FAILURE;
	}

	//validate the file stream
	ifstream bookFile;
	bookFile.open(argv[1], ios::binary);
	if (!bookFile)
	{
		cerr << "Error .....bookFile opening failed\n";
		return EXIT_FAILURE;
	}

	//create an ifstream object to hold the message file to be encoded
	ifstream codedFile;
	codedFile.open(argv[2], ios::binary);
	if (!codedFile)
	{
		cerr << "Error .....codedFile opening failed\n";
		return EXIT_FAILURE;
	}

	//create an ofstream object to hold the coded file
	ofstream decodedFile;
	decodedFile.open(argv[3], ios::binary);
	if (!decodedFile)
	{
		cerr << "Error .... decodedFile opening failed\n";
		return EXIT_FAILURE;
	}

	//start loading the files into the vectors		
	vector<vector<char>> book;
	vector<char> line;
	char ch;
	while (!bookFile.eof())
	{
		bookFile.get(ch);
		line.push_back(ch);

		if (ch == '\n')
		{
			book.push_back(line);
			line.clear();
		}
	}
	bookFile.close();

	vector<string> encodedBook;
	string word;
	while (!codedFile.eof())
	{		
		codedFile >> word;
		encodedBook.push_back(word);			
	}	
	/*for (auto x : encodedBook)
	{
		cout << x <<endl;
	}*/
	cout << "Please wait..... may take a while for long books\n";
	size_t s;
	string fsubstring;
	vector<string> frontStrings;	
	for (size_t i = 0; i < encodedBook.size(); ++i)
	{		
		for (size_t k = 0; k < encodedBook[i].size(); ++k);
		{
			s = encodedBook[i].find((char)44);			
			fsubstring = encodedBook[i].substr(0,s);			
			frontStrings.push_back(fsubstring);
		}
	}

	/*for (auto x : frontStrings)
	{
		cout << x <<" front string" << endl;
	}*/
	size_t s2;
	string esubstring;
	vector<string> endStrings;	
	for(size_t i = 0; i < encodedBook.size(); ++i)
	{			
		for (size_t k = 0; k < encodedBook[i].size(); ++k);
		{			
			s2 = encodedBook[i].find((char)44);				
			esubstring = encodedBook[i].substr(s2 +1);			
			endStrings.push_back(esubstring);			
		}		
	}
	/*for (auto x : endStrings)
	{
		cout << x << " end string" << endl;
	}*/
	size_t fronts;
	string finstring;
	vector<int>row;
	for (size_t i = 0; i < frontStrings.size(); ++i)
	{			
			fronts = atoi(frontStrings[i].c_str());			
			row.push_back(fronts);		
	}
	
	/*for (auto x : row)
	{
		cout << x << " row" << endl;
	}*/
	size_t ends;
	string einstring;
	vector<int>column;
	for (size_t i = 0; i < endStrings.size(); ++i)
	{	
			ends = atoi(endStrings[i].c_str());			
			column.push_back(ends);				
	}	
	/*for (auto x : column)
	{
		cout << x << " col" << endl;
	}*/	
	////decode message using the encodedBook and the book file
	//vector < vector<char>> decodedBook;
	pair<int, int> tempPair;
	vector<char>decodedBook;
	vector < pair<int, int>>ASCIIPairs;
	char letter;
	/*cout << row.size() << endl;
	cout << column.size() << endl;*/
	for (size_t i = 0; i < row.size(); i ++)
	{						
		letter = book[row[i]][column[i]];		
		decodedBook.push_back(letter);
	}

	for (auto x : decodedBook)
		 decodedFile << x;
	cout << "Program is done, exiting" << endl;
	return EXIT_SUCCESS;
}