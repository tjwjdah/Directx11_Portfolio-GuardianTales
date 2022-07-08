#include "pch.h"
#include "CTextMgr.h"
#include "CDevice.h"

#include <FW1FontWrapper\FW1FontWrapper.h>
#pragma comment(lib, "FW1FontWrapper/FW1FontWrapper.lib")
CTextMgr::CTextMgr()
{

}

CTextMgr::~CTextMgr()
{

}


void CTextMgr::drawText(const WCHAR* Text, float Font_SIze, float Xposition, float Yposition, UINT32 Color, UINT  Flags) {
	IFW1Factory* pFW1Factory;
	
	HRESULT hResult =FW1CreateFactory(FW1_VERSION, &pFW1Factory);
	
	IFW1FontWrapper* pFontWrapper;
	hResult = pFW1Factory->CreateFontWrapper(DEVICE, L"Arial", &pFontWrapper);

	pFontWrapper->DrawString(
		CONTEXT,
		Text,// String
		Font_SIze,// Font size
		Xposition,// X position
		Yposition,// Y position
		Color,// Text color, 0xAaBbGgRr
		Flags// Flags (for example FW1_RESTORESTATE to keep context states unchanged)
	);

	pFontWrapper->Release();
	pFW1Factory->Release();
	
};