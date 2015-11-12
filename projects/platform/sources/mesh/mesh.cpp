//*****************************************************************************
//
// mesh
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "mesh.h"
#include "system/win_system.h"

namespace mesh {
//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DVERTEXELEMENT9 Mesh::VERTEXELEMENTS[] =
{
	{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
	{ 0,sizeof(float3),D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 },
	{ 0,sizeof(float3) + sizeof(float2),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0 },
	{ 0,sizeof(float3) + sizeof(float2) + sizeof(float3),D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0 },
	D3DDECL_END()
};

std::unordered_map<const D3DVERTEXELEMENT9*,std::shared_ptr<IDirect3DVertexDeclaration9>> Mesh::vertex_declarations_;

//=============================================================================
// constructor
//=============================================================================
Mesh::Mesh(bool in_is_3d,bool in_is_used_index_buffer)
	:stride_(0)
	,primitive_type_(D3DPT_TRIANGLELIST)
	,vertex_count_(0)
	,direct3dvertexbuffer9_(nullptr)
	,direct3dindexbuffer9_(nullptr)
	,is_3d_(in_is_3d)
	,is_used_index_buffer_(in_is_used_index_buffer)
	,is_dirty_(true)
{
}

//=============================================================================
// apply
//=============================================================================
void Mesh::Apply(void)
{
	if(is_dirty_)
	{
		UpdateVertexBuffer_();
		is_dirty_ = false;
	}
}

//=============================================================================
// get buffer
//=============================================================================
const LPDIRECT3DVERTEXBUFFER9 Mesh::GetBuffer(void)const
{
	return direct3dvertexbuffer9_;
}

//=============================================================================
// get index buffer
//=============================================================================
const LPDIRECT3DINDEXBUFFER9 Mesh::GetIndexBuffer(void) const
{
	return direct3dindexbuffer9_;
}

//=============================================================================
// get stride
//=============================================================================
const u32& Mesh::GetStride(void)const
{
	return stride_;
}

//=============================================================================
// get primitive type
//=============================================================================
const D3DPRIMITIVETYPE& Mesh::GetPrimitiveType(void)const
{
	return primitive_type_;
}

//=============================================================================
// get vertex count
//=============================================================================
const u32 & Mesh::GetVertexCount(void) const
{
	return vertex_count_;
}

//=============================================================================
// get primitive count
//=============================================================================
const u32& Mesh::GetPrimitiveCount(void)const
{
	return primitive_count_;
}

//=============================================================================
// is used index buffer
//=============================================================================
bool Mesh::IsUsedIndexBuffer(void)const
{
	return is_used_index_buffer_;
}

//=============================================================================
// is 3D
//=============================================================================
bool Mesh::Is3D(void) const
{
	return is_3d_;
}

//=============================================================================
// get vertex declaration
//=============================================================================
const LPDIRECT3DVERTEXDECLARATION9 Mesh::GetVertexDeclaration(void)
{
	auto key = GetVertexElements_();
	auto it = vertex_declarations_.find(key);

	if(it == vertex_declarations_.end())
	{
		LPDIRECT3DVERTEXDECLARATION9 vertex_declaration = nullptr;
		auto directx9 = GET_DIRECTX9_DEVICE();

		directx9->CreateVertexDeclaration(key,&vertex_declaration);
		auto vertex_ = std::shared_ptr<IDirect3DVertexDeclaration9>(vertex_declaration,[](IDirect3DVertexDeclaration9* vertex) {vertex->Release();});

		vertex_declarations_.insert(std::make_pair(key,vertex_));
		return vertex_declaration;
	}

	return it->second.get();
}

//=============================================================================
// get vertex elements
//=============================================================================
const D3DVERTEXELEMENT9* Mesh::GetVertexElements_(void) const
{
	return VERTEXELEMENTS;
}

} // namespace mesh

//---------------------------------- EOF --------------------------------------
