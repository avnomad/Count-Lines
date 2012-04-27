#include <stdio.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_PATH_LENGTH 10240

int main()
{	
	char contentsListName[L_tmpnam];
	FILE *contentsList;

	char dirCommand[1024] = "dir /s /a:-d-s /b /o:-d /t:w>>";	// to do: change the dir command.

	unsigned int lines;
	unsigned int l;
	char currentFileName[MAX_PATH_LENGTH];
	FILE *currentFile;
	int ch;

		// create a file with the contents of the folder and it's subfolders.
	tmpnam(contentsListName);	// create a name for a temporary file and save it in contentsListName.
	strcat(dirCommand,contentsListName);	// complement the dirCommand with the file name.
	system(dirCommand);	// send the command to the system.

		// rename the files
	if(contentsList = fopen(contentsListName,"r"))	// if you can open the contentsList file.
	{
		lines = 0;
		while(fgets(currentFileName,MAX_PATH_LENGTH,contentsList))	// for each file in the list.
		{
			*strrchr(currentFileName,'\n') = '\0';	// erase the newline appended by fgets to the name.
			if(currentFile = fopen(currentFileName,"r"))	// if you can open file.
			{
				while((ch = fgetc(currentFile)) != EOF)
					if(ch == '\n')
						++lines;
			}
			else	// if you can't open the current file,
				cerr<<"could not open file "<<currentFileName<<" for reading."<<endl;	// notify for error.			
		} // end while

			// once you have finished using the contentsList file,
		fclose(contentsList);	// close it.
	}
	else	// if you can't open the contentsList file.
		cerr<<"could not open file "<<contentsListName<<" for reading."<<endl;	// notify for error.

		// delete the contents list file when you don't need it any more.
	if(remove(contentsListName))
		cerr<<"could not delete file "<<contentsListName<<"."<<endl;	// notify on failure to delete.

	cout<<"The total number of lines in the files of this folder is: "<<lines<<endl;
	system("PAUSE");
	return 0;
} // end function main
