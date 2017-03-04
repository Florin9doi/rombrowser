#pragma once
#pragma pack(push)
#pragma pack(1)

using namespace System;

class TDllRefTable
{
public:
	UInt16 iFlags;
	UInt16 iNumberOfEntries;
};

class TDllRefTableEntry
{
public:
	UInt32 iEntryPoint;
	TDllRefTable* iDllRefTable;
};

class TRomImageHeader
{
public:
	UInt32 iUid1;
	UInt32 iUid2;
	UInt32 iUid3;
	UInt32 iCheck;
	UInt32 iEntryPoint;
	UInt32 iCodeAddress;
	UInt32 iDataAddress;
	UInt32 iCodeSize;
	UInt32 iTextSize;
	UInt32 iDataSize;
	UInt32 iBssSize;
	UInt32 iHeapSizeMin;
	UInt32 iHeapSizeMax;
	UInt32 iStackSize;
	TDllRefTable* iDllRefTable; // 16b+16b
	UInt32 iExportDirCount;
	UInt32 iExportDir;

	// security info // 10 bytes
	UInt32 iCheckSumCode;
	UInt32 iCheckSumData;
	
	UInt32 iVersion; // 8 major, 8 minor, 16 build
	UInt32 iFlags;
	UInt32 iPriority; // TProcessPriority :  150=low, 950=supervisor
	UInt32 iDataBssLinearBase;
	UInt32 iNextExtension;
	UInt32 iHardwareVariant;
};

#pragma pack(pop)