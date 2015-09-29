//*****************************************************************************
//
// directx9 depth buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_DEPTH_BUFFER_H_
#define _DX9_DEPTH_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/depth_buffer/base_depth_buffer.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace depth_buffer
{
class DX9DepthBuffer : public graphic::base::depth_buffer::BaseDepthBuffer
{
public:
	// constructor
	DX9DepthBuffer(const u16& in_width,const u16& in_height,LPDIRECT3DDEVICE9 in_direct3ddevice9);
	DX9DepthBuffer(const u16& in_width,const u16& in_height,const base::depth_buffer::FORMAT& in_format,LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9DepthBuffer(void);

	// get buffer
	void* GetBuffer(void)const override;

protected:

private:
	// constructor
	DX9DepthBuffer(void);

	static const base::depth_buffer::FORMAT DEFAULT_FORMAT;

	LPDIRECT3DSURFACE9 depth_buffer_;

	D3DFORMAT ConvertD3DFORMATFromFormat_(const base::depth_buffer::FORMAT& in_format);
};

} // namespace depth_buffer
} // namespace directx9
} // namespace graphic

#endif // _DX9_DEPTH_BUFFER_H_

//---------------------------------- EOF --------------------------------------
