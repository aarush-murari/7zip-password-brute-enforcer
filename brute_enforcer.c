// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <process.h>
#include <direct.h>
#include <vector>



using namespace std;



void bruteForce(string file, string output, vector<char> passwordCharArray, int targetLength, int position) {

	char charList[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	string password;
	string commandString;
	
	
	commandString = "7z.exe x \"" + file + "\" -p\"" + password + "\" -o\"" + output + "\" -y";
	const char* commandCharArray = commandString.c_str();
	int zipExtractVal = system(commandCharArray);

	if (position == targetLength) {
		string currentPassword(passwordCharArray.begin(), passwordCharArray.end());

		if (zipExtractVal == 0) {
			cout << "Password found. Password is: " << currentPassword;
			ofstream passwordFile(output + "password.txt");
			if (passwordFile.is_open()) {
				passwordFile << currentPassword;
				passwordFile.close();
				
			}
			else {
				std::cerr << "Error opening file and saving password.\n";
				exit(1);
			}
			
		}
		cout << "Trying: " << currentPassword;
		return;
		
	}

	for (char c : charList) {
		passwordCharArray.push_back(c);
		bruteForce(file, output, passwordCharArray, targetLength, position + 1);
		passwordCharArray.erase(passwordCharArray.end());
	}
    
}

int main(int argc, char* argv[])
{
    cout << "Hello World!\n";



	string file;
	if (argv[1] == nullptr) {
		cout << "No file provided. Defualting to archive.tar" << endl;
		file = "archive.tar";
		//exit(1);
	}
	else {
		file = argv[1];
	}
	string output;
	if ((argv[2] == nullptr) || (argc < 2)) {
		char cwd[1024];
		if (_getcwd(cwd, sizeof(cwd)) != NULL) {
			cout << "No output folder. moving to " << cwd << "\\output\\" << endl;
			string outputFolder = "\\output\\";
			output = cwd + outputFolder;
		}
		//exit(1);
	}
	else {
		output = argv[2];
	}

	//int zipExtractVal2 = 1;
	

	if(!(ifstream(file))){
		cout << "Extraction file '" << file << "' does not exist or is invalid.";
		exit(1);
	}
    
    
    int maxLength = 50; // You may need to adjust this based on your use case
    for (int length = 1; length <= maxLength; length++) {
        
		vector<char> passwordCharArray = {};
        
        bruteForce(file, output, passwordCharArray, length, 0);
    }
    return 0;
}

