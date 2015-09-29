//*****************************************************************************
//
// font
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FONT_H_
#define _FONT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
class Texture;
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace font
{

class Font : public common::base::Base
{
public:
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_MS_GOTHIC,
		TYPE_MS_MINTYO,
		TYPE_MEIRYO,
		TYPE_MEIRYO_UI,
		TYPE_MAX
	};

	using TTexture = std::shared_ptr<Texture>;

	// constructor
	Font(const u32& in_character_code,const Font::TYPE& in_type,const u16& in_size);
	Font(const std::string& in_character,const Font::TYPE& in_type,const u16& in_size);

	// destructor
	virtual ~Font(void);

	// accessor
	const TYPE& __type(void)const { return type_; }
	const u32& __width(void)const { return width_; }
	const u32& __height(void)const { return height_; }
	const u32& __offset_y(void)const { return offset_y_; }
	const TTexture __texture(void)const { return texture_; }

private:
	static const s8* FONT_NAME[TYPE_MAX];
	static const u32 SPECIAL_CHARACTER[];
	u32 character_code_;
	u16 size_;
	TYPE type_;
	u32 width_;
	u32 height_;
	u32 offset_y_;

	TTexture texture_;
	bool IsSpecialCharacter(const u32& character_code) const;
	u32 StringToCharactorCode(const std::string& charactor) const;
};

} // namespace font
} // namespace graphic

#endif // _FONT_H_

//---------------------------------- EOF --------------------------------------
