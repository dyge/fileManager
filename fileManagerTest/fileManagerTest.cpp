// fileManagerTest.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
//#include <fileapi.h>
//#include <windows.h> //
#include <Windows.h>
#include <stdio.h>

using namespace std;

#define BUFFSIZE 128

int main() // int argc , TCHAR *argv[]
{
	//TCHAR buffer[BUFFSIZE];
	//int x, i = 0;
	//buffer[0] = '\0';
	//x = GetLogicalDriveStrings(BUFFSIZE - 1, buffer);
	//while (i < x && buffer[i]) 
	//{
	//	_tprintf(_T("buffer: %s\n"), &buffer[i]);
	//	cout << (_T("Type: %s"), GetDriveType(_T("C:\\"))) << endl;
	//	cout << (_T("Type: %s"), GetDriveType(_T("%s\\", &buffer[i]))) << std::endl;
	//	//_tprintf(_T("Type: %s"), GetDriveType(_T("%s", &buffer[i])));
	//	while (buffer[i]) i++;
	//	i++;
	//}

	WCHAR myDrives[] = L"A:\\";

	DWORD myDrivesBitMask = GetLogicalDrives();

	if (myDrivesBitMask == 0)
	{
		wprintf(L"GetLogicalDrives() failed\n");
	}
	else
	{
		wprintf(L"Logical drives:\n");
		while (myDrivesBitMask)
		{
			if (myDrivesBitMask & 1)
			{
				int myType = GetDriveType(myDrives);

				switch (myType)
				{
				case 0:
					printf("Drive: %S   Type: %d -> DRIVE_UNKNOWN\n", myDrives, myType);
					break;
				case 1:
					printf("Drive: %S   Type: %d -> DRIVE_NO_ROOT_DIR\n", myDrives, myType);
					break;
				case 2:
					printf("Drive: %S   Type: %d -> DRIVE_REMOVABLE\n", myDrives, myType);
					break;
				case 3:
					printf("Drive: %S   Type: %d -> DRIVE_FIXED\n", myDrives, myType);
					break;
				case 4:
					printf("Drive: %S   Type: %d -> DRIVE_REMOTE\n", myDrives, myType);
					break;
				case 5:
					printf("Drive: %S   Type: %d -> DRIVE_CDROM\n", myDrives, myType);
					break;
				case 6:
					printf("Drive: %S   Type: %d -> DRIVE_RAMDISK\n", myDrives, myType);
					break;
				default:
					"Unknown drive type\n";
				}
			}
			myDrives[0]++;
			myDrivesBitMask >>= 1;
		}
		wprintf(L"\n");
	}

	return 0;
}