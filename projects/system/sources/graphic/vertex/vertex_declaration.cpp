//*****************************************************************************
//
// vertex declaration
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "vertex_declaration.h"

namespace graphic
{
namespace vertex
{
//=============================================================================
// constructor
//=============================================================================
VertexDeclaration::VertexDeclaration(const TVertexElements& in_vertex_elements)
{
	vertex_elements_ = in_vertex_elements;
}

//=============================================================================
// destructor
//=============================================================================
VertexDeclaration::~VertexDeclaration(void)
{
}

//=============================================================================
// get format
//=============================================================================
const VertexDeclaration::TVertexElements& VertexDeclaration::GetElements(void) const
{
	return vertex_elements_;
}

} // namespace vertex
} // namespace graphic

//---------------------------------- EOF --------------------------------------