//
//  PVRTCLibrary.c
//  PVRTCLibrary
//
//  Created by Linus Langels on 12/07/16.
//  Copyright © 2016 Plotagon. All rights reserved.
//

#include "PVRTCLibrary.h"
#include <libc.h>

static StringParameterCallback debugLog;

extern "C"
{
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
    
    void FreeUncompressedData(unsigned char* dataPointer)
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