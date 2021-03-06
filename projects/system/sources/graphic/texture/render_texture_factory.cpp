//*****************************************************************************
//
// render texture factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "render_texture_factory.h"

namespace graphic
{
namespace texture
{
//=============================================================================
// create
//=============================================================================
RenderTextureFactory::TRenderTexture RenderTextureFactory::Create(const std::string & in_key,const u16 & in_width,const u16 & in_height,const FORMAT& in_format)
{
	auto render_texture = Get(in_key);

	if(render_texture == nullptr)
	{
		auto render_texture = Create_(in_width,in_height,in_format);
		container_.insert(std::make_pair(in_key,render_texture));
		return render_texture;
	}

	return render_texture;
}

//=============================================================================
// get
//=============================================================================
RenderTextureFactory::TRenderTexture RenderTextureFactory::Get(const std::string & in_key)
{
	auto it = container_.find(in_key);

	if(it != container_.end())
	{
		return nullptr;
	}

	return it->second;
}

} // namespace texture
} // namespace graphic

//---------------------------------- EOF --------------------------------------
