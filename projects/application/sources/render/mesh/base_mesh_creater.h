//*****************************************************************************
//
// base mesh creater
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_MESH_CREATER_H_
#define _BASE_MESH_CREATER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"
#include "mesh_format.h"

namespace render {
namespace mesh {
class MeshBuffer;
} // mesh
} // render

//*****************************************************************************
// class definition
//*****************************************************************************
namespace render {
namespace mesh {
class BaseMeshCreater : public utility::base::Base
{
public:
	using TFormat = FORMAT;
	using TMeshBuffer = std::shared_ptr<MeshBuffer>;
	using TMeshBuffers = std::vector<TMeshBuffer>;

	// destructor
	virtual ~BaseMeshCreater(void);

	// get mesh buffer
	const TMeshBuffers& GetMeshBuffers(void);

	// set format
	void SetFormat(const TFormat& in_format);

	// get format
	const TFormat& GetFormat(void)const;

protected:
	// constructor
	BaseMeshCreater(void);

	TFormat format_;
	TMeshBuffers mesh_buffers_;

private:
	virtual bool SetFormat_(const TFormat& in_format) = 0;

};

} // namespace mesh
} // namespace render

#endif // _BASE_MESH_CREATER_H_

//---------------------------------- EOF --------------------------------------
