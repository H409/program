//*****************************************************************************
//
// directx9 depth buffer factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_DEPTH_BUFFER_FACTORY_H_
#define _DX9_DEPTH_BUFFER_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/depth_buffer/base_depth_buffer_factory.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************


//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace depth_buffer
{
class DX9DepthBufferFactory : public base::depth_buffer::BaseDepthBufferFactory
{
public:
	// constructor
	explicit DX9DepthBufferFactory(LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9DepthBufferFactory(void);

protected:

private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;

	TBaseDepthBuffer Create_(const u16& in_width,const u16& in_height,const base::depth_buffer::FORMAT& in_format)override;

};

} // namespace depth_buffer
} // namespace base
} // namespace graphic

#endif // _BASE_DEPTH_BUFFER_FACTORY_H_

//---------------------------------- EOF --------------------------------------
