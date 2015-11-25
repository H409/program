//*****************************************************************************
//
// x model
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#include "x_model.h"

XModel::XModel(LPDIRECT3DDEVICE9 in_direct3ddevice9,const std::string& in_filepath)
{
	direct3ddevice9_ = in_direct3ddevice9;
	LPD3DXBUFFER adj_buffer = nullptr;

	// ファイル読み込み
	D3DXLoadMeshFromX(in_filepath.c_str(),D3DXMESH_MANAGED,in_direct3ddevice9,&adj_buffer,&material_buffer_,nullptr,&part_count_,&d3dxmesh_);

	d3dxmaterial_ = (D3DXMATERIAL*)material_buffer_->GetBufferPointer();

	//LPD3DXMESH d3dxmesh;
	//D3DVERTEXELEMENT9 decl[] =
	//{
	//	{ 0, 0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
	//	{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0 },
	//	{ 0,24,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0 },
	//	{ 0,24 + sizeof(D3DCOLOR),D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 },
	//	{ 0,24 + sizeof(D3DCOLOR) * sizeof(D3DXVECTOR2),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0 },
	//	{ 0,24 + sizeof(D3DCOLOR) * sizeof(D3DXVECTOR2) * sizeof(D3DXVECTOR3),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0 },
	//	D3DDECL_END()
	//};
	//
	//d3dxmesh_->CloneMesh(D3DXMESH_SYSTEMMEM,decl,in_direct3ddevice9,&d3dxmesh);
	//SafeRelease(d3dxmesh_);
	//
	//D3DXComputeTangentFrameEx(d3dxmesh,D3DDECLUSAGE_TEXCOORD,0,D3DDECLUSAGE_TANGENT,0,D3DDECLUSAGE_BINORMAL,0,D3DDECLUSAGE_NORMAL,0,0,NULL,0.01f,0.25f,0.01f,&d3dxmesh,NULL);
	//
	//d3dxmesh->Optimize(D3DXMESH_MANAGED | D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,(DWORD*)adj_buffer->GetBufferPointer(),NULL,NULL,NULL,&d3dxmesh_);
	//
	//SafeRelease(d3dxmesh);
	SafeRelease(adj_buffer);
}

XModel::~XModel(void)
{
	SafeRelease(material_buffer_);
	SafeRelease(d3dxmesh_);
}

void XModel::Draw(void)
{
	D3DMATERIAL9 d3dmaterial;

	// 材質情報の取得
	direct3ddevice9_->GetMaterial(&d3dmaterial);

	for(DWORD i = 0;i < part_count_;++i)
	{
		// 材質情報を変更
		direct3ddevice9_->SetMaterial(&d3dxmaterial_[i].MatD3D);
		Draw(i);
	}

	// 材質情報を元に戻す
	direct3ddevice9_->SetMaterial(&d3dmaterial);
}

void XModel::Draw(int part_number)
{
	d3dxmesh_->DrawSubset(part_number);
}

DWORD XModel::GetPartCount(void) const
{
	return part_count_;
}

LPD3DXMATERIAL XModel::GetMaterial(void) const
{
	return d3dxmaterial_;
}

//---------------------------------- EOF --------------------------------------
