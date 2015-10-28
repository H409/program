//*****************************************************************************
//
// directx9 vertex buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_vertex_declaration.h"

namespace graphic
{
namespace directx9
{
namespace vertex
{
//*****************************************************************************
// constant definition
//*****************************************************************************
const std::unordered_map<DX9VertexDeclaration::TVertexElement::TYPE,D3DDECLTYPE> DX9VertexDeclaration::TYPE_MAP =
{
	std::make_pair(TVertexElement::TYPE::FLOAT1   ,D3DDECLTYPE_FLOAT1),
	std::make_pair(TVertexElement::TYPE::FLOAT2   ,D3DDECLTYPE_FLOAT2),
	std::make_pair(TVertexElement::TYPE::FLOAT3   ,D3DDECLTYPE_FLOAT3),
	std::make_pair(TVertexElement::TYPE::FLOAT4   ,D3DDECLTYPE_FLOAT4),
	std::make_pair(TVertexElement::TYPE::D3DCOLOR ,D3DDECLTYPE_D3DCOLOR),
	std::make_pair(TVertexElement::TYPE::UBYTE4   ,D3DDECLTYPE_UBYTE4),
	std::make_pair(TVertexElement::TYPE::SHORT2   ,D3DDECLTYPE_SHORT2),
	std::make_pair(TVertexElement::TYPE::SHORT4   ,D3DDECLTYPE_SHORT4),
	std::make_pair(TVertexElement::TYPE::UBYTE4N  ,D3DDECLTYPE_UBYTE4N),
	std::make_pair(TVertexElement::TYPE::SHORT2N  ,D3DDECLTYPE_SHORT2N),
	std::make_pair(TVertexElement::TYPE::SHORT4N  ,D3DDECLTYPE_SHORT4N),
	std::make_pair(TVertexElement::TYPE::USHORT2N ,D3DDECLTYPE_USHORT2N),
	std::make_pair(TVertexElement::TYPE::USHORT4N ,D3DDECLTYPE_USHORT4N),
	std::make_pair(TVertexElement::TYPE::UDEC3    ,D3DDECLTYPE_UDEC3),
	std::make_pair(TVertexElement::TYPE::DEC3N    ,D3DDECLTYPE_DEC3N),
	std::make_pair(TVertexElement::TYPE::FLOAT16_2,D3DDECLTYPE_FLOAT16_2),
	std::make_pair(TVertexElement::TYPE::FLOAT16_4,D3DDECLTYPE_FLOAT16_4),
	std::make_pair(TVertexElement::TYPE::UNUSED   ,D3DDECLTYPE_UNUSED),
};

const std::unordered_map<DX9VertexDeclaration::TVertexElement::USAGE,D3DDECLUSAGE> DX9VertexDeclaration::USAGE_MAP =
{
	std::make_pair(TVertexElement::USAGE::POSITION     ,D3DDECLUSAGE_POSITION),
	std::make_pair(TVertexElement::USAGE::BLENDWEIGHT  ,D3DDECLUSAGE_BLENDWEIGHT),
	std::make_pair(TVertexElement::USAGE::BLENDINDICES ,D3DDECLUSAGE_BLENDINDICES),
	std::make_pair(TVertexElement::USAGE::NORMAL       ,D3DDECLUSAGE_NORMAL),
	std::make_pair(TVertexElement::USAGE::PSIZE        ,D3DDECLUSAGE_PSIZE),
	std::make_pair(TVertexElement::USAGE::TEXCOORD     ,D3DDECLUSAGE_TEXCOORD),
	std::make_pair(TVertexElement::USAGE::TANGENT      ,D3DDECLUSAGE_TANGENT),
	std::make_pair(TVertexElement::USAGE::BINORMAL     ,D3DDECLUSAGE_BINORMAL),
	std::make_pair(TVertexElement::USAGE::TESSFACTOR   ,D3DDECLUSAGE_TESSFACTOR),
	std::make_pair(TVertexElement::USAGE::POSITIONT    ,D3DDECLUSAGE_POSITIONT),
	std::make_pair(TVertexElement::USAGE::COLOR        ,D3DDECLUSAGE_COLOR),
	std::make_pair(TVertexElement::USAGE::FOG          ,D3DDECLUSAGE_FOG),
	std::make_pair(TVertexElement::USAGE::DEPTH        ,D3DDECLUSAGE_DEPTH),
	std::make_pair(TVertexElement::USAGE::SAMPLE       ,D3DDECLUSAGE_SAMPLE),
};

//=============================================================================
// constructor
//=============================================================================
DX9VertexDeclaration::DX9VertexDeclaration(LPDIRECT3DDEVICE9 in_direct3ddevice9,const TVertexElements& in_vertex_elements)
	:VertexDeclaration(in_vertex_elements)
	,direct3dvertexdeclaration9_(nullptr)
{
	std::vector<D3DVERTEXELEMENT9> d3dvertexelement9s;

	d3dvertexelement9s.reserve(in_vertex_elements.size() + 1);

	for(auto vertex_element : in_vertex_elements)
	{
		d3dvertexelement9s.push_back(TVertexElementToD3DVERTEXELEMENT9(vertex_element));
	}

	d3dvertexelement9s.push_back(D3DDECL_END());

	DEBUG_ASSERT(in_direct3ddevice9->CreateVertexDeclaration(&d3dvertexelement9s[0],&direct3dvertexdeclaration9_) == S_OK);
}

//=============================================================================
// destructor
//=============================================================================
DX9VertexDeclaration::~DX9VertexDeclaration(void)
{
	SafeRelease(direct3dvertexdeclaration9_);
}

//=============================================================================
// get buffer
//=============================================================================
void* DX9VertexDeclaration::GetBuffer(void) const
{
	return direct3dvertexdeclaration9_;
}

//=============================================================================
// TVertexElement to D3DVERTEXELEMENT9
//=============================================================================
D3DVERTEXELEMENT9 DX9VertexDeclaration::TVertexElementToD3DVERTEXELEMENT9(const TVertexElement& in_vertex_element)
{
	D3DVERTEXELEMENT9 d3dvertexelement9;

	d3dvertexelement9.Stream = 0;
	d3dvertexelement9.Offset = in_vertex_element._offset;
	d3dvertexelement9.Type = TYPE_MAP.at(in_vertex_element._type);
	d3dvertexelement9.Usage = USAGE_MAP.at(in_vertex_element._usage);
	d3dvertexelement9.UsageIndex = 0;
	d3dvertexelement9.Method = D3DDECLMETHOD_DEFAULT;

	return d3dvertexelement9;
}

} // namespace vertex
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
