/*
 * insultGenerator_15mxs1.h
 *
 *  Created on: Oct 3, 2018
 *      Author: monica
 */

#ifndef INSULTGENERATOR_15MXS1_H_
#define INSULTGENERATOR_15MXS1_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <set>
using namespace std;

class InsultGenerator {
public:
	//class constructor
	InsultGenerator();

	//opens insult source file and reads the data and stores it in the column vectors. No return type.
	void initialize();

	//returns a randomly generated insult in the form of a string
	string talkToMe();

	//generates 'n' number of insults and writes them to 'filename'
	void generateAndSave(const string& filename, int n);

	//generate 'n' number of insults and stores them in a vector that is returned as a vector string
	vector<string> generate(int n);

//private variables only accessibly to this functions of this class
private:

	//stores each column of insults from file to be read in separate vector string
	vector<string> c1;
	vector<string> c2;
	vector<string> c3;

	//stores all contents from file to be read
	vector<string> read;

	//stores unique insults generated
	set<string> insultSet;

	//stores unique insults generated that are to be written to a file
	set<string> saveInsultSet;
};

//if file cannot be read, FileException exception is thrown
class FileException {
public:
	FileException(const string& errorMessage);
	string& what();
private:
	string errorMessage;
};

//if the number of generate insults requested is greater than 10000 or less than 1, NumInsultsOutOfBounds exception is thrown
class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string& errorMessage);
	string& what();
private:
	string errorMessage;
};

#endif /* INSULTGENERATOR_15MXS1_H_ */
