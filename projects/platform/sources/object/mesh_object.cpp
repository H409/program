//*****************************************************************************
//
// mesh object
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "mesh_object.h"
#include "action/action.h"
#include "math/math.h"
#include "mesh/mesh.h"
#include "system/win_system.h"

//=============================================================================
// constructor
//=============================================================================
MeshObject::MeshObject(TMesh in_mesh)
	:mesh_(in_mesh)
{
}

//=============================================================================
// draw
//=============================================================================
void MeshObject::Draw_(void)
{
	auto directx9 = GET_DIRECTX9_DEVICE();

	directx9->SetVertexDeclaration(mesh_->GetVertexDeclaration());
	directx9->SetStreamSource(0,mesh_->GetBuffer(),0,mesh_->GetStride());

	mesh_->AttachRenderState();

	if(mesh_->IsUsedIndexBuffer())
	{
		directx9->SetIndices(mesh_->GetIndexBuffer());
		directx9->DrawIndexedPrimitive(mesh_->GetPrimitiveType(),0,0,mesh_->GetVertexCount(),0,mesh_->GetPrimitiveCount());
	}
	else
	{
		directx9->DrawPrimitive(mesh_->GetPrimitiveType(),0,mesh_->GetPrimitiveCount());
	}

	mesh_->DetachRenderState();
}

//---------------------------------- EOF --------------------------------------
