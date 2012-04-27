//	Copyright (C) 2008, 2010, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Count Lines.
 *
 *	Count Lines is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Count Lines is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Count Lines.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma warning(disable : 4996)

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#include <fstream>
using std::ifstream;

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
