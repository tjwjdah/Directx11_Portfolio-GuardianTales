#pragma once


#include <Windows.h>


#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#include "SimpleMath.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

#include "define.h"
#include "struct.h"
#include "extern.h"
#include "Ptr.h"



// std
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <typeinfo>
#include <random>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
using std::experimental::filesystem::path;



using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;


#include "func.h"