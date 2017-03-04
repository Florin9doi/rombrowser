#pragma once
#pragma pack(push)
#pragma pack(1)

using namespace System;

typedef System::Byte UInt8;

class TRomHeader
{
public:
	UInt8 iJump[128];
	union {
		UInt32 iVersion;
		struct _iVersion {
			UInt8 Major;
			UInt8 Minor;
			UInt16 Build;
		} _iVersion_;
	};
	Int64 iTime;
	UInt32 iRomBase;
	UInt32 iRomSize;
	UInt32 iRomRootDirectoryList;
	UInt32 iKernDataAddress;
	UInt32 iKernStackAddress;
	UInt32 iPrimaryFile;
	UInt32 iSecondaryFile;
	UInt32 iCheckSum;
	Int64 iLanguage;
	UInt32 iHardware;
	union {
		UInt64 iScreenSize;
		struct iScreenSize {
			UInt32 Width;
			UInt32 Height;
		};
	};
	UInt32 iScreenBitsPerPixel;
	UInt32 iRomSectionHeader;
	UInt32 iTotalSvDataSize;
	UInt32 iVariantFile;
	UInt32 iExtensionFile;
	UInt32 iRelocInfo;
	UInt32 iTraceMask;
	UInt32 iUserDataAddress;
	UInt32 iTotalUserDataSize;
	UInt32 iPad[32-25];
};

typedef struct _TRomRootDirectoryList {
	UInt32 iNumRootDirs;
	UInt32 iHardwareVariant;
	UInt32 iAddressLin;
} TRomRootDirectoryList;

typedef struct _TRomEntry {
	UInt32 iSize;
	UInt32 iAddressLin;
	UInt8 iAtt;
	UInt8 iNameLength;
	UInt8 iName;
	char name[128];
} TRomEntry;

public ref class PathElement {
public:
	PathElement() {};

	UInt32 address;
	UInt32 sizeT;
	UInt32 offset;
	System::Windows::Forms::TreeNode^ parentNode;
};

class ROM
{
public:
	UInt32 baseAddress;
	UInt32 length;
	UInt8 *data;

	ROM(String^ filePath) {
		array<Byte>^ tempBuffer = System::IO::File::ReadAllBytes(filePath);
		length = tempBuffer->Length;
		data = new UInt8[length];
		for (UInt32 i = 0; i < length; i++) {
			data[i] = tempBuffer[i];
		}
		baseAddress = ((TRomHeader*)data)->iRomBase;
	};

	~ROM() {
		delete[] data;
	};

	inline TRomHeader* getHeaderAddress() {
		return (TRomHeader*)data;
	}
	inline UInt8* getDataAddress() {
		return data;
	}
	inline void* getPointerTo(UInt32 address) {
		return getDataAddress() + address - baseAddress;
	}
	inline UInt8 read8(UInt32 address) {
		if (address < baseAddress) return 0;
		return *(UInt8*)(getDataAddress() + address - baseAddress);
	}
	template <typename T> inline T read(T address) {
		if (address < baseAddress) return 0;
		return *(T*)(getDataAddress() + address - baseAddress);
	}
};

#pragma pack(pop)