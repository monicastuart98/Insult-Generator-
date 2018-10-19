/*
 * insultGenerator_15mxs1.cpp
 *
 *  Created on: Oct 3, 2018
 *      Author: monica
 */

#include "insultgenerator_15mxs1.h"

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;

InsultGenerator::InsultGenerator() {
	//so the same pattern of numbers are not randomly generated in generate function
	srand(time(0));
}

FileException::FileException(const string& errorMessage) :
		errorMessage(errorMessage) {
}
string& FileException::what() {
	return errorMessage;
}
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& errorMessage) :
		errorMessage(errorMessage) {
}
string& NumInsultsOutOfBounds::what() {
	return errorMessage;
}

void InsultGenerator::initialize() {

	ifstream inFile;
	inFile.open("InsultsSource.txt");
	string word;

	if (inFile.fail()) {
		throw FileException("[ERROR] cannot open file");
	}
	if (inFile.is_open()) {

		while (inFile >> word) {
			read.push_back(word);
		}
	}

	inFile.close();

	//iterate through 'read' vector and copy elements into column vectors
	for (int i = 0; i < 150; i += 3) {
		c1.push_back(read.at(i));
		c2.push_back(read.at(i + 1));
		c3.push_back(read.at(i + 2));
	}

}

string InsultGenerator::talkToMe() {

	string singleInsult;
	string firstWord;
	string secondWord;
	string thirdWord;

	//randomly choose indices between 0-49 and access the contents stored at this index of the respective column
	firstWord = c1[rand() % 50];
	secondWord = c2[rand() % 50];
	thirdWord = c3[rand() % 50];

	singleInsult = "Thou " + firstWord + " " + secondWord + " " + thirdWord
			+ "!";

	return singleInsult;

}

vector<string> InsultGenerator::generate(int n) {
	//reset insultSet if generate is called more than once
	insultSet.clear();
	string insult;
	vector<string> insultsReturn;

	if (n < 1) {
		throw NumInsultsOutOfBounds(
				"[ERROR] Choose a number greater or equal to 1");
	}
	if (n > 10000) {
		throw NumInsultsOutOfBounds(
				"[ERROR] Choose a number less than or equal to 10000");
	}

	//emplace() will only add the new insult generated to the insultSet if it as unique insult and will automatically sort the set alphabetically (emplace() is a c++11 feature)
	while (insultSet.size() < n) {

		insult = talkToMe();
		insultSet.emplace(insult);
	}

	//copies contents of insultSet into the vector insultsReturn
	copy(insultSet.begin(), insultSet.end(), back_inserter(insultsReturn));

	return insultsReturn;

}
void InsultGenerator::generateAndSave(const string& filename, int n) {

	if (n < 1) {
			throw NumInsultsOutOfBounds(
					"[ERROR] Choose a number greater or equal to 1");
		}
		if (n > 10000) {
			throw NumInsultsOutOfBounds(
					"[ERROR] Choose a number less than or equal to 10000");
		}
	//initialize iterator to iterate through set starting at the begining
	set<std::string>::iterator it = insultSet.begin();

	string insultGenerate;
	int lineCount(0);
	int lines(saveInsultSet.size());

	//reset saveInsultSet if generateAndSave is called more than once
	saveInsultSet.clear();

	while (saveInsultSet.size() < n) {
		insultGenerate = talkToMe();
		saveInsultSet.emplace(insultGenerate);
	}

	ofstream fileOut(filename.c_str());

	//write saved insults out to filename
	while (lineCount < lines) {

		for (it = saveInsultSet.begin(); it != saveInsultSet.end(); ++it) {
			fileOut << *it << endl;
			lineCount++;
		}

	}
	fileOut.close();
}
