// fileManagerTest.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
//#include <windows.h>
#include <Windows.h>
#include <stdio.h>
#include <string>

using namespace std;

#define BUFFSIZE 128

//struct keepSizes
//{
//	unsigned __int64 terabyte;
//	unsigned __int64 gigabyte;
//	unsigned __int64 megabyte;
//	unsigned __int64 kilobyte;
//	unsigned __int64 byte;
//};
//
//void convertBytes(keepSizes keeper)
//{
//	keeper.kilobyte = keeper.byte / 1024;
//}

string getUnit(int iterNum)
{
	switch (iterNum)
	{
	case 1:
		return "Kilobytes";
		break;
	case 2:
		return "Megabytes";
		break;
	case 3:
		return "Gigabytes";
		break;
	case 4:
		return "Terabytes";
		break;
	default:
		return "Not known";
		break;
	}
}

void printConvertedSize(unsigned __int64 size, string text)
{
	int num = 0;
	double precisionSize;
	do
	{
		if (size <= (1024 * 1024))
		{
			precisionSize = size;
			precisionSize = precisionSize / 1024;
			size = precisionSize;
			num++;
		}
		else
		{
			size = size / 1024;
			num++;
		}
	} while (size > 1024);

	string unit = getUnit(num);
	cout << text << unit << ": " << std::to_string(precisionSize) << endl;
}

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
						printConvertedSize(userBytes, "Available space in ");
						printf("Total space: %I64u\n", totalBytes);
						printConvertedSize(totalBytes, "Total space in ");
						printf("Free space: %I64u\n", freeBytes);
						printConvertedSize(freeBytes, "Free space in ");
						printf("Used space: %I64u\n", totalBytes-freeBytes);
						printConvertedSize(totalBytes-freeBytes, "Used space in ");

						/*keepSizes userSize;
						convertBytes(userSize);
						printf("Convert: %I64u\n", userSize.kilobyte);*/
					}
					else
					{
						cout << "Access denied" << endl;
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
