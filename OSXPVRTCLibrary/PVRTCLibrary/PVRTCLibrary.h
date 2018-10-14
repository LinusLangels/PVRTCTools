//
//  PVRTCLibrary.h
//  PVRTCLibrary
//
//  Created by Linus Langels on 12/07/16.
//  Copyright © 2016 Plotagon. All rights reserved.
//

#ifndef PVRTCLibrary_h
#define PVRTCLibrary_h

#include <stdio.h>
#include "PVRTexture.h"
#include "PVRTextureUtilities.h"

using namespace pvrtexture;

typedef void(*StringParameterCallback)(const char*);

extern "C"
{
    void* GetUncompressedData(unsigned char* pvrData, uint32 size, uint32 width, uint32 height, bool premultiplied, int* dataSize);
    
    void FreeUncompressedData(unsigned char* dataPointer);
    
    void SetDebugLogCallback(StringParameterCallback callback);
}


#endif /* PVRTCLibrary_h */
