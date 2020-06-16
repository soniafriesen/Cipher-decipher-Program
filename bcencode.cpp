/*
file Name: becode.cpp
Coder: Sonia Friesen
Date: April 1, 2019
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility> 
#include <random>
#include <ctime>
#include<sstream>

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
		cerr << "Error, not enough aruments\n";
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
	ifstream messageFile;
	messageFile.open(argv[2], ios::binary);
	if (!messageFile)
	{
		cerr << "Error .....messageFile opening failed\n";
		return EXIT_FAILURE;
	}

	//create an ofstream object to hold the coded file
	ofstream codedFile;
	codedFile.open(argv[3], ios::binary);
	if (!codedFile)
	{
		cerr << "Error .... codedFile opening failed\n";
		return EXIT_FAILURE;
	}

	//start loading the files into the vectors
	cout << "Please wait..... may take a while for long books\n";
	vector<vector<char>> cipherBook;
	vector<char> line;
	char ch;
	while (!bookFile.eof())
	{
		bookFile.get(ch);
		line.push_back(ch);

		if (ch == '\n')
		{
			cipherBook.push_back(line);
			line.clear();
		}
	}
	bookFile.close();
	
	vector<char>message;
	char thisline;
	while (messageFile.get(thisline))
	{
		message.push_back(thisline);
	}
	messageFile.close();

	//find letters and pairs in the bookfile and message file.
	pair<int, int> location;
	vector < pair<int, int>> pairTemp;
	size_t counter = 0;

	int index;	
	for (size_t k = 0; k < message.size(); ++k)
	{
		counter = 0;
		for (size_t i = 0; i < cipherBook.size(); ++i)
		{
			vector<char>::iterator it;
			it = find(cipherBook[i].begin(), cipherBook[i].end(), message[k]);
			if (it != cipherBook[i].end())
			{
				index = distance(cipherBook[i].begin(), it);
				location = make_pair(i, index);
				pairTemp.push_back(location);

			}//endif
			else
			{
				++counter;

			}//end else					

			if (counter >= cipherBook.size())
			{
				cerr << "\nMissing Letter" << " " << message[k];
				exit(1);
			}//end failure if			
		}//end book loop				
	}//end message loop

	 //start loading the pairs into the ASCII vector
	vector<vector<pair<int, int>>> ASCII(256);//256 represents the ASCII CODE
	size_t row;
	size_t col;
	int letter;	
	for (int i = 0; i < pairTemp.size(); ++i)
	{
		row = pairTemp[i].first;
		col = pairTemp[i].second;	
		letter = (int)cipherBook[row][col];
		ASCII[letter].push_back(pairTemp[i]);

	}
	
	//do random selection
	vector <pair<int, int>> encodedBook;
	pair<int, int> encodePair;
	vector<pair<int, int>> usedPair;
	int character;
	int random;
	int total;	

	default_random_engine generator(time(0));
	uniform_int_distribution<int> distribution(0, total);
	for (size_t i = 0; i < message.size(); ++i)
	{
		character = (int)message[i];
		cout << "char is " << character << endl;
		total = (int)ASCII[character].size(); //the size of the column
		//create generator 
				
		random = distribution(generator);	
		cout << "in fro loop counter "<<i << " random is  " << random << endl;
		
		vector<pair<int, int>>::iterator it;
		it = find(usedPair.begin(), usedPair.end(), ASCII[character][random]);
		if (it != usedPair.end())
		{
			random_shuffle(ASCII[i].begin(), ASCII[i].end());
			random = distribution(generator);
			cout << "find loop counter "  << random << endl;			
			encodePair = ASCII[character][random];
			encodedBook.push_back(encodePair);
			usedPair.push_back(encodePair);
						
		}
		else
		{
			encodePair = ASCII[character][random];
			encodedBook.push_back(encodePair);
			usedPair.push_back(encodePair);			
		}
	}
		
	//write thepairs to the outFile	
	for (auto x : encodedBook)
	{
		codedFile << x.first << "," << x.second << " ";

	}
	cout << "Program is done, exiting" << endl;
	return EXIT_SUCCESS;
}