#pragma once
#include "CSingleton.h"
class CTextMgr :
    public CSingleton<CTextMgr>
{
    SINGLE(CTextMgr)

public:
    void drawText(const WCHAR* Text, float Font_SIze, float Xposition, float Yposition, UINT32 Color, UINT Flags = 0);
};

