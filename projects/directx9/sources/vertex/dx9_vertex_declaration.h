//*****************************************************************************
//
// directx9 vertex buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_VERTEX_DECLARATION_H_
#define _DX9_VERTEX_DECLARATION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/vertex/vertex_declaration.h"

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
namespace vertex
{
class DX9VertexDeclaration : public graphic::vertex::VertexDeclaration
{
public:
	// constructor
	DX9VertexDeclaration(LPDIRECT3DDEVICE9 in_direct3ddevice9,const TVertexElements& in_vertex_elements);

	// destructor
	virtual ~DX9VertexDeclaration(void);

	// get buffer
	void* GetBuffer(void)const override;

protected:

private:
	static const std::unordered_map<TVertexElement::TYPE,D3DDECLTYPE> TYPE_MAP;
	static const std::unordered_map<TVertexElement::USAGE,D3DDECLUSAGE> USAGE_MAP;

	LPDIRECT3DVERTEXDECLARATION9 direct3dvertexdeclaration9_;
	D3DVERTEXELEMENT9 TVertexElementToD3DVERTEXELEMENT9(const TVertexElement& in_vertex_element);

};

} // namespace vertex
} // namespace directx9
} // namespace graphic

#endif // _DX9_VERTEX_BUFFER_H_

//---------------------------------- EOF --------------------------------------

