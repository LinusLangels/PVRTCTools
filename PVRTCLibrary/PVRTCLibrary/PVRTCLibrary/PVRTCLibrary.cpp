// PVRTCLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "PVRTCLibrary.h"

static StringParameterCallback debugLog;

extern "C"
{
	void CompressTextureToFile(const char* filePath, unsigned char* data, uint32 height, uint32 width, uint32 mipLevels, uint32 quality, bool preMultiplied, bool dither)
	{
		if (debugLog != NULL)
		{
			debugLog("Start compressing texture");
		}
		
		CPVRTextureHeader textureHeader(PVRStandard8PixelType.PixelTypeID,
			height,
			width,
			1,
			mipLevels,
			1,
			1,
			ePVRTCSpacelRGB,
			ePVRTVarTypeUnsignedByteNorm,
			preMultiplied);

		CPVRTexture sTexture(textureHeader, data);

		PixelType pixType(ePVRTPF_PVRTCI_4bpp_RGBA);

		if (debugLog != NULL)
		{
			debugLog("Begin transcoding texture");
		}

		ECompressorQuality compressionQuality = (ECompressorQuality)quality;

		Transcode(sTexture,
			pixType,
			ePVRTVarTypeUnsignedByteNorm,
			ePVRTCSpacelRGB, compressionQuality, dither);

		CPVRTString path(filePath, strlen(filePath));
		sTexture.saveFile(path);

		if (debugLog != NULL)
		{
			debugLog("Done compressing texture");
		}
	}

	void* GetTextureData(const char* filePath, int mipLevels, int** dataSizes)
	{
		CPVRTexture cTexture(filePath);

		*dataSizes = new int[mipLevels];

		for (int x = 0; x < mipLevels; x++)
		{
			uint32 size = cTexture.getDataSize(x);
			(*dataSizes)[x] = size;

			char str[16]; // could be less but i'm too lazy to look for the actual the max length of an integer
			snprintf(str, sizeof(str), "%d", size);
			debugLog(str);
		}

		int totalDataSize = cTexture.getDataSize();
		auto returnData = new unsigned char[totalDataSize];

		memcpy(returnData, cTexture.getDataPtr(), totalDataSize);

		return returnData;
	}
	
	void* GetUncompressedData(unsigned char* pvrData, uint32 size, uint32 width, uint32 height, bool premultiplied, int* dataSize)
	{
		CPVRTextureHeader textureHeader(ePVRTPF_PVRTCI_4bpp_RGBA,
			height,
			width,
			1,
			1,
			1,
			1,
			ePVRTCSpacelRGB,
			ePVRTVarTypeUnsignedByteNorm,
			premultiplied);

		CPVRTexture sTexture(textureHeader, pvrData);

		Transcode(
			sTexture,
			PVRStandard8PixelType,
			ePVRTVarTypeUnsignedByteNorm,
			ePVRTCSpacelRGB
		);

		*dataSize = sTexture.getDataSize();

		int totalDataSize = sTexture.getDataSize();
		auto returnData = new unsigned char[totalDataSize];

		memcpy(returnData, sTexture.getDataPtr(), totalDataSize);

		return returnData;
	}

	void FreeUncompressedData(void* dataPointer)
	{
		if (dataPointer != nullptr)
		{
			delete[] dataPointer;
		}
	}

	void SetDebugLogCallback(StringParameterCallback callback)
	{
		debugLog = callback;
	}
}


