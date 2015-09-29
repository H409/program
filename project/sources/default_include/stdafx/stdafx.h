//*****************************************************************************
//
// プリコンパイル済みヘッダー
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _STDAFX_H_
#define _STDAFX_H_

//*****************************************************************************
// stl
//*****************************************************************************
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#include <unordered_map>
#include <condition_variable>

//*****************************************************************************
// library
//*****************************************************************************
#include "using_library.h"

#ifdef _USING_WINDOWS_
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <process.h>
#pragma comment (lib,"winmm.lib")
#endif // _USING_WINDOWS_

#ifdef _USING_DIRECTX9_
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#endif // _USING_DIRECTX9_

#ifdef _USING_OPENGL_
#include <GL/gl.h>
#include <GL/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glext.lib")
#endif // _USING_OPENGL_

#ifdef _USING_XAUDIO2_
#include <xaudio2.h>
#endif // _USING_XAUDIO2_

#ifdef _USING_DIRECT_INPUT_
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#endif // _USING_DIRECT_INPUT_

#endif // _STDAFX_H_

//-----------------------------------EOF---------------------------------------