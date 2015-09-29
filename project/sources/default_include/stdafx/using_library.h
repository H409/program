//*****************************************************************************
//
// using librarys
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once

#ifndef _USING_LIBRARY_H_
#define _USING_LIBRARY_H_

//*****************************************************************************
// macro definition
//*****************************************************************************
#define _USING_WINDOWS_
#define _USING_GRAPHIC_LIBRARY_
#define _USING_AUDIO_LIBRARY_
#define _USING_INPUT_LIBRARY_

// use windows
#ifdef _USING_WINDOWS_

// use graphic library
#ifdef _USING_GRAPHIC_LIBRARY_

// use directx
#define _USING_DIRECTX9_

// not use directx
#ifndef _USING_DIRECTX9_

// use opengl
#define _USING_OPENGL_

// not use opengl
#ifndef _USING_OPENGL_

#endif	// _USING_OPENGL_

#endif	// _USING_DIRECTX_

#endif // _USING_GRAPHIC_LIBRARY_

// use sound library
#ifdef _USING_AUDIO_LIBRARY_

// use xaudio2
#define _USING_XAUDIO2_

// not use xaudio2
#ifndef _USING_XAUDIO2_

#endif	// _USING_XAUDIO2_

#endif // _USING_AUDIO_LIBRARY_

// use input library
#ifdef _USING_INPUT_LIBRARY_

// use direct input
#define _USING_DIRECT_INPUT_

// not use direct input
#ifndef _USING_DIRECT_INPUT_

#endif // _USING_DIRECT_INPUT_

#endif // _USING_INPUT_LIBRARY_

#endif // _USING_WINDOWS_

#endif	// _USING_LIBRARY_H_

//---------------------------------- EOF --------------------------------------
