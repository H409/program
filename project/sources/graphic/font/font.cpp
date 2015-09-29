//*****************************************************************************
//
// font
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "font.h"

namespace graphic
{
namespace font
{

//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* Font::FONT_NAME[TYPE_MAX] =
{
	"ÇlÇr ÉSÉVÉbÉN",
	"ÇlÇr ñæí©",
	"ÉÅÉCÉäÉI",
	"Meiryo UI"
};

const u32 Font::SPECIAL_CHARACTER[] =
{
	(' '),
	('Å@'),
};

//=============================================================================
// constructor
//=============================================================================
Font::Font(const u32& in_character_code,const Font::TYPE& in_type,const u16& in_size)
	:character_code_(in_character_code)
	,type_(in_type)
	,size_(in_size)
	,width_(0)
	,height_(0)
	,offset_y_(0)
{
	if(IsSpecialCharacter(in_character_code))
	{

	}
	else
	{
		HDC hdc;
		HFONT hfont;
		HFONT preview_hfont;
		LOGFONT logfont = { 0 };
		GLYPHMETRICS glyphmetrics;

		logfont.lfHeight = size_;
		logfont.lfWidth = 0;
		logfont.lfEscapement = 0;
		logfont.lfOrientation = 0;
		logfont.lfWeight = 0;
		logfont.lfItalic = FALSE;
		logfont.lfUnderline = TRUE;
		logfont.lfStrikeOut = FALSE;
		logfont.lfCharSet = SHIFTJIS_CHARSET;
		logfont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
		logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logfont.lfQuality = PROOF_QUALITY;
		logfont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
		memcpy(logfont.lfFaceName,FONT_NAME[type_],strlen(FONT_NAME[type_]));

		hdc = GetDC(NULL);
		hfont = CreateFontIndirect(&logfont);
		preview_hfont = (HFONT)SelectObject(hdc,hfont);
		MAT2 mat2 = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };

		DWORD size = GetGlyphOutline(hdc,character_code_,GGO_GRAY4_BITMAP,&glyphmetrics,0,nullptr,&mat2);
		u8* ptr = nullptr;
		if(size == -1)
		{
			// 
			SelectObject(hdc,preview_hfont);
			DeleteObject(hfont);
			ReleaseDC(NULL,hdc);
			return;
		}

		ptr = new u8[size];
		GetGlyphOutline(hdc,character_code_,GGO_GRAY4_BITMAP,&glyphmetrics,size,ptr,&mat2);

		// 
		SelectObject(hdc,preview_hfont);
		DeleteObject(hfont);
		ReleaseDC(NULL,hdc);

		width_ = (glyphmetrics.gmBlackBoxX + 3) / 4 * 4;
		height_ = glyphmetrics.gmBlackBoxY;
		offset_y_ = size_ - glyphmetrics.gmptGlyphOrigin.y;

		// 
	}
}

//=============================================================================
// constructor
//=============================================================================
Font::Font(const std::string& in_character,const Font::TYPE& in_type,const u16& in_size)
	:Font(StringToCharactorCode(in_character),in_type,in_size)
{
}

//=============================================================================
// destructor
//=============================================================================
Font::~Font(void)
{
}

//=============================================================================
// is special character
//=============================================================================
bool Font::IsSpecialCharacter(const u32& character_code) const
{
	for(auto character : SPECIAL_CHARACTER)
	{
		if(character_code == character)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// string to charactor code
//=============================================================================
u32 Font::StringToCharactorCode(const std::string& in_character) const
{
	u32 character_code = 0;

	DEBUG_ASSERT(in_character.length() != 0);

	if(IsDBCSLeadByte((BYTE)*in_character.c_str()))
	{
		DEBUG_ASSERT_MESSAGE(in_character.length() <= 2,"1ï∂éöÇÃÇ›ëŒâû");
		character_code = (BYTE)in_character[0] << 8 | (BYTE)in_character[1];
	}
	else
	{
		DEBUG_ASSERT_MESSAGE(in_character.length() <= 1,"1ï∂éöÇÃÇ›ëŒâû");
		character_code = in_character[0];
	}

	return character_code;
}

} // namespace font
} // namespace graphic

//---------------------------------- EOF --------------------------------------
