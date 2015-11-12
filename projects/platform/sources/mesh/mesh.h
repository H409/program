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
namespace mesh {
class Mesh
{
public:
	virtual ~Mesh(void) = default;

	// apply
	void Apply(void);

	// get buffer
	const LPDIRECT3DVERTEXBUFFER9 GetBuffer(void)const;

	// get index buffer
	const LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(void)const;

	// get stride
	const u32& GetStride(void)const;

	// get primitive type
	const D3DPRIMITIVETYPE& GetPrimitiveType(void)const;

	// get vertex count
	const u32& GetVertexCount(void)const;

	// get primitive count
	const u32& GetPrimitiveCount(void)const;

	// is used
	bool IsUsedIndexBuffer(void)const;

	// is 3D
	bool Is3D(void)const;

	// get vertex declaration
	const LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration(void);

protected:
	Mesh(bool in_is_3d,bool in_is_used_index_buffer);

	u32 stride_;
	D3DPRIMITIVETYPE primitive_type_;
	u32 vertex_count_;
	u32 primitive_count_;
	LPDIRECT3DVERTEXBUFFER9 direct3dvertexbuffer9_;
	LPDIRECT3DINDEXBUFFER9 direct3dindexbuffer9_;
	bool is_used_index_buffer_;
	bool is_3d_;
	bool is_dirty_;
	static const D3DVERTEXELEMENT9 VERTEXELEMENTS[];
	static std::unordered_map<const D3DVERTEXELEMENT9*,std::shared_ptr<IDirect3DVertexDeclaration9>> vertex_declarations_;

private:
	virtual const D3DVERTEXELEMENT9* GetVertexElements_(void)const;
	virtual void UpdateVertexBuffer_(void) = 0;
};
} // namespace mesh

#endif // _MESH_H_

//---------------------------------- EOF --------------------------------------
