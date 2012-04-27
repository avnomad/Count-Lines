#pragma warning(disable : 4996)

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#include <fstream>
using std::ifstream;
//using std::ios_base::badbit;
//using std::ios_base::failbit;
//using std::ios_base::eofbit;
//using std::ios_base::in;
//using std::ios_base::binary;

#include <string>
using std::string;
using std::getline;

#include <cstdlib>
using std::system;

#include <cstdio>
using std::tmpnam;
using std::remove;


int main()
{
	ifstream list,current;
	string listName = tmpnam(NULL),currentName;
	string dirCommand = "dir /s /a:-d-s /b /o:-d /t:w>>";
	unsigned int lines_total = 0;

		// set the streams to throw exceptions on errors.
	list.exceptions(ifstream::badbit|ifstream::failbit);
	current.exceptions(ifstream::badbit|ifstream::failbit);

		// create a file with the contents of the folder and it's subfolders.
	system((dirCommand+listName).c_str());

	try
	{
		list.open(listName.c_str());
		list.exceptions(ifstream::badbit);
		while(getline(list,currentName), currentName != "")	// if the list file has empty lines this might not work
		{													// fortunately it shouldn't have such lines.
			current.exceptions(ifstream::badbit|ifstream::failbit);
			current.open(currentName.c_str(),ifstream::in);
			current.exceptions(ifstream::badbit);
			while(current)
				if(current.get() == '\n')
					++lines_total;
			current.close();
			current.clear();
		} // end while
		list.close();
	}
	catch(std::ios_base::failure e)
	{
		cerr << e.what() << "trying to open:\n";
		cerr << currentName << endl;
	} // end catch

	if(remove(listName.c_str()))
		cerr << "could not delete temporary file " << listName << "." << endl;	// notify on failure to delete.

	cout << "The total number of lines in the files of this folder is: "<< lines_total << endl;

	system("PAUSE");
	return 0;
} // end function main
