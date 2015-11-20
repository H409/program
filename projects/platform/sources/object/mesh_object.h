//*****************************************************************************
//
// mesh object
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_OBJECT_H_
#define _MESH_OBJECT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "object.h"

namespace mesh {
class Mesh;
}

//*****************************************************************************
// class declaration
//*****************************************************************************
class MeshObject : public Object
{
public:
	using TMesh = std::shared_ptr<mesh::Mesh>;

	// constructor
	explicit MeshObject(TMesh in_mesh);

	// destructor
	virtual ~MeshObject(void) = default;

protected:

private:
	TMesh mesh_;

	// draw
	void Draw_(void)override;
};

#endif // _OBJECT_H_

//---------------------------------- EOF --------------------------------------
