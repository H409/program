//*****************************************************************************
//
// vertex declaration
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _VERTEX_DECLARATION_H_
#define _VERTEX_DECLARATION_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"
#include "vertex_element.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace vertex
{
class VertexDeclaration : public utility::base::Base
{
public:
	using TVertexElement = VERTEX_ELEMENT;
	using TVertexElements = std::vector<TVertexElement>;

	// destructor
	virtual ~VertexDeclaration(void);

	// get buffer
	virtual void* GetBuffer(void)const = 0;

	// get format
	const TVertexElements& GetElements(void)const;

protected:
	explicit VertexDeclaration(const TVertexElements& in_vertex_elements);
	std::vector<VERTEX_ELEMENT> vertex_elements_;

private:

};

} // namespace vertex
} // namespace graphic

#endif // _VERTEX_DECLARATION_H_

//---------------------------------- EOF --------------------------------------

