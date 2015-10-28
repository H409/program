//*****************************************************************************
//
// mesh
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_H_
#define _MESH_H_

//*****************************************************************************
// class declaration
//*****************************************************************************
class Mesh
{
public:
	virtual ~Mesh(void) = default;

	// get buffer
	const LPDIRECT3DVERTEXBUFFER9 GetBuffer(void)const;

	// get index buffer
	const LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(void)const;

	// get stride
	const u32& GetStride(void)const;

	// get primitive type
	const D3DPRIMITIVETYPE& GetPrimitiveType(void)const;

	// get primitive count
	const u32& GetPrimitiveCount(void)const;

	// is used
	bool IsUsedIndexBuffer(void)const;

	// is 3D
	bool Is3D(void)const;

protected:
	Mesh(void) = default;

	u32 stride_;
	D3DPRIMITIVETYPE primitive_type_;
	u32 primitive_count_;
	LPDIRECT3DVERTEXBUFFER9 direct3dvertexbuffer9_;
	LPDIRECT3DINDEXBUFFER9 direct3dindexbuffer9_;
	bool is_used_index_buffer_;
	bool is_3d_;

private:

};
#endif // _OBJECT_H_

//---------------------------------- EOF --------------------------------------
