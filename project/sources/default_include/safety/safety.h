//*****************************************************************************
//
// safety
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _SAFETY_H_
#define _SAFETY_H_

//=============================================================================
// Safe Delete
//=============================================================================
template<typename _T>inline void SafeDelete(_T*& pointer)
{
	if(pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}

//=============================================================================
// Safe Delete Array
//=============================================================================
template<typename _T>inline void SafeDeleteArray(_T*& pointer)
{
	if(pointer != nullptr)
	{
		delete[] pointer;
		pointer = nullptr;
	}
}

//=============================================================================
// Safe Initialize
//=============================================================================
template<typename _T>inline bool SafeInitialize(_T*& pointer)
{
	if(pointer != nullptr)
	{
		return pointer->Initialize();
	}

	return false;
}

//=============================================================================
// Safe Uninitialize
//=============================================================================
template<typename _T>inline void SafeUninitialize(_T*& pointer)
{
	if(pointer != nullptr)
	{
		pointer->Uninitialize();
	}
}

//=============================================================================
// Safe Release
//=============================================================================
template<typename _T>inline void SafeRelease(_T*& pointer)
{
	if(pointer != nullptr)
	{
		pointer->Release();
		pointer = nullptr;
	}
}

#endif	// _SAFETY_H_

//---------------------------------- EOF --------------------------------------
