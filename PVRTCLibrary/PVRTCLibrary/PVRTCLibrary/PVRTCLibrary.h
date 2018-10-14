#pragma once

#include "PVRTexture.h" 
#include <PVRTextureUtilities.h>

using namespace pvrtexture;

#ifdef PLOTAGON_EXPORT
#define PLOTAGON_PVRTC __declspec(dllexport) 
#else
#define PLOTAGON_PVRTC __declspec(dllimport) 
#endif

typedef void(*StringParameterCallback)(const char*);

extern "C"
{
	PLOTAGON_PVRTC void CompressTextureToFile(const char* filePath, unsigned char* data, uint32 height, uint32 width, uint32 mipLevels, uint32 quality, bool preMultiplied, bool dither);

	PLOTAGON_PVRTC void* GetTextureData(const char* filePath, int mipLevels, int** dataSizes);

	PLOTAGON_PVRTC void* GetUncompressedData(unsigned char* pvrData, uint32 size, uint32 width, uint32 height, bool premultiplied, int* dataSize);

	PLOTAGON_PVRTC void FreeUncompressedData(void* dataPointer);

	PLOTAGON_PVRTC void SetDebugLogCallback(StringParameterCallback callback);
}


