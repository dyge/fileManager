// fileManagerTest.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
//#include <windows.h>
#include <Windows.h>
#include <stdio.h>

using namespace std;

#define BUFFSIZE 128

int main()
{
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

				if (myType == 3)
				{
					unsigned __int64 userBytes, totalBytes, freeBytes;
					bool res = GetDiskFreeSpaceEx(myDrives, (PULARGE_INTEGER)&userBytes, (PULARGE_INTEGER)&totalBytes, (PULARGE_INTEGER)&freeBytes);
					if (res != 0)
					{
						printf("Available space: %I64u\n", userBytes);
						printf("Total space: %I64u\n", totalBytes);
						printf("Free space: %I64u\n", freeBytes);
					}
					else
					{
						cout << "Failed" << endl;
					}
				}
				cout << "\n";
			}
			myDrives[0]++;
			myDrivesBitMask >>= 1;
		}
	}

	return 0;
}
