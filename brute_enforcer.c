#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <process.h>
#include <direct.h>
#include <vector>
#include <source_location>


using namespace std;



void bruteForce(string file, string output, vector<char> passwordCharArray, int targetLength, int position) {

	char charList[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	string password = "";
	string commandString;
	string commandIntegrityString;
	string nullString;
	
	
	
	

	if (position == targetLength) {
		string currentPassword(passwordCharArray.begin(), passwordCharArray.end());
		commandString = "7z.exe x \"" + file + "\" -p\"" + password + "\" -o\"" + output + "\" -y";
		commandIntegrityString = "7z.exe t \"" + file + "\" -p\"" + password;
		const char* commandCharArray = commandString.c_str();
		const char* commandIntegrityCharArray = commandIntegrityString.c_str();
		int zipExtractVal = system(commandIntegrityCharArray);

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
			cout << "extracting file with password '" + output << "'" << endl;
			int zipFIleExtractVal = system(commandCharArray);
			
		}
		cout << "Trying: '" << currentPassword << "'";

		return;
		
	}

	for (char c : charList) {
		passwordCharArray.push_back(c);
		bruteForce(file, output, passwordCharArray, targetLength, position + 1);
		passwordCharArray.erase(passwordCharArray.end() - 1);
	}
    
}

int main(int argc, char* argv[])
{
	
	



	string file;
	//FIXME: '-h' not working
	if (argv[1] == "-h") {
		cout << "Usage:" << endl;
		cout << argv[0] << " \"path\\to\\file.archive\" \"path\\to\\output\\folder\"" << endl << endl;
		exit(0);
	}
	else if (argv[1] == nullptr) {
		cout << "No file provided. Defualting to \"archive.rar\"" << endl;
		file = "archive.rar";
		//exit(1);
	}
	else {
		file = argv[1];
	}
	string output;
	if ((argv[2] == nullptr) || (argc < 2)) {
		char cwd[1024];
		if (_getcwd(cwd, sizeof(cwd)) != NULL) {
			cout << "No output folder. Moving to \"" << cwd << "\\output\\\"" << endl;
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
		cout << "ERROR: Extraction file '" << file << "' does not exist or is invalid." << endl << endl;
		cout << "Usage:" << endl;
		cout << argv[0] << " \"path\\to\\file.archive\" \"path\\to\\output\\folder\"" << endl << endl;
		exit(1);
	}
    
    
    int maxLength = 50; // You may need to adjust this based on your use case
    for (int length = 1; length <= maxLength; length++) {
        
		vector<char> passwordCharArray = {};
        
        bruteForce(file, output, passwordCharArray, length, 0);
    }
    return 0;
}




