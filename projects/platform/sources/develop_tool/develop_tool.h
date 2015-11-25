//*****************************************************************************
//
// develop tool
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DEVELOP_TOOL_H_
#define _DEVELOP_TOOL_H_

#ifndef _RELEASE
//*****************************************************************************
// include
//*****************************************************************************
#include "develop_display.h"

namespace develop_tool {
class DevelopTool
{
public:
	using TDevelopDisplay = std::shared_ptr<DevelopDisplay>;

	static DevelopTool* GetInstance(void);

	void Update(void);

	void Draw(void);

	TDevelopDisplay GetDevelopDisplay(void)const;
private:
	DevelopTool(void);
	TDevelopDisplay develop_display_;
};
} // namespace develop_tool

#define DEVELOP_DISPLAY(format,...) develop_tool::DevelopTool::GetInstance()->GetDevelopDisplay()->Print(format,__VA_ARGS__)
#define DEVELOP_TOOL_UPDATE() develop_tool::DevelopTool::GetInstance()->Update()
#define DEVELOP_TOOL_DRAW() develop_tool::DevelopTool::GetInstance()->Draw()
#else
#define DEVELOP_DISPLAY(format,...)
#define DEVELOP_TOOL_UPDATE()
#define DEVELOP_TOOL_DRAW()
#endif // _RELEASE
#endif // _DEVELOP_TOOL_H_

//---------------------------------- EOF --------------------------------------
