// VCNETDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int _stdcall ReportVersion() { return 91; }


// Return the sum of two numbers 
int _stdcall Sum(int inA, int inB) 
{ 
	int SumVar = inA+ inB;
	return SumVar; 
}