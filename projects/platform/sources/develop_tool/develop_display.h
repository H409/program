//*****************************************************************************
//
// develop display
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************
#pragma once
#ifndef _DEVELOP_DISPLAY_H_
#define _DEVELOP_DISPLAY_H_

namespace develop_tool {
class DevelopDisplay
{
public:
	// constructor
	DevelopDisplay(LPDIRECT3DDEVICE9 in_direct3ddevice9,u16 in_width,u16 in_height);

	// destructor
	virtual ~DevelopDisplay(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// print
	void Print(const char* in_format,...);
	void PrintR(const char* in_format,...);

private:
	static const u32 STRING_MAX = 1024;
	s8 string_[STRING_MAX];
	s8 stringR_[STRING_MAX];

	bool is_show_;
	LPD3DXFONT font_;
	u16 width_;
	u16 height_;
};
} // namespace develop_tool

#endif // _DEVELOP_DISPLAY_H_

//---------------------------------- EOF --------------------------------------
