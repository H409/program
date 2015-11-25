#include "develop_tool.h"
#include "system/win_system.h"

#ifndef _RELEASE
namespace develop_tool {
DevelopTool::DevelopTool(void)
{
	auto directx9 = GET_DIRECTX9_DEVICE();

	develop_display_ = std::make_shared<DevelopDisplay>(directx9,800,600);
}

DevelopTool* DevelopTool::GetInstance(void)
{
	static DevelopTool instance;

	return &instance;
}

void develop_tool::DevelopTool::Update(void)
{
	develop_display_->Update();
}

void DevelopTool::Draw(void)
{
	develop_display_->Draw();
}

DevelopTool::TDevelopDisplay DevelopTool::GetDevelopDisplay(void) const
{
	return develop_display_;
}
} // namespace develop_tool

#endif // _RELEASE

//---------------------------------- EOF --------------------------------------
