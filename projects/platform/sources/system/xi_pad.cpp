//*****************************************************************************
//
// xinput pad
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "xi_pad.h"
#include <XInput.h>
#pragma comment(lib,"xinput.lib")

namespace input {
namespace directinput8 {
XIPad::XIPad(u32 in_number)
	:number_(in_number)
{
	Clear();
}

XIPad::~XIPad(void)
{
}

void XIPad::Update(void)
{
	XINPUT_STATE xinput_state = {NULL};
	XInputGetState(number_,&xinput_state);

	bool is_press[(u32)KEY::MAX];

	is_press[(u32)KEY::L_LEFT] = xinput_state.Gamepad.sThumbLX < -X_INPUT_DEEP;
	is_press[(u32)KEY::L_RIGHT] = xinput_state.Gamepad.sThumbLX >  X_INPUT_DEEP;
	is_press[(u32)KEY::L_UP]    = xinput_state.Gamepad.sThumbLY >  X_INPUT_DEEP;
	is_press[(u32)KEY::L_DOWN]  = xinput_state.Gamepad.sThumbLY < -X_INPUT_DEEP;
	is_press[(u32)KEY::R_LEFT]  = xinput_state.Gamepad.sThumbRX < -X_INPUT_DEEP;
	is_press[(u32)KEY::R_RIGHT] = xinput_state.Gamepad.sThumbRX >  X_INPUT_DEEP;
	is_press[(u32)KEY::R_UP]    = xinput_state.Gamepad.sThumbRY >  X_INPUT_DEEP;
	is_press[(u32)KEY::R_DOWN]  = xinput_state.Gamepad.sThumbRY < -X_INPUT_DEEP;

	for(u32 i = 0;i < BUTTON_MAX + 1;++i)
	{
		is_press[i] = ((xinput_state.Gamepad.wButtons >> i) & 0x0001) ? true : false;
	}

	is_press[(u32)KEY::L2] = xinput_state.Gamepad.bLeftTrigger  > X_INPUT_TRIGGER_DEEP;
	is_press[(u32)KEY::R2] = xinput_state.Gamepad.bRightTrigger > X_INPUT_TRIGGER_DEEP;

	l_stick_._x = xinput_state.Gamepad.sThumbLX;
	l_stick_._y = xinput_state.Gamepad.sThumbLY;
	r_stick_._x = xinput_state.Gamepad.sThumbRX;
	r_stick_._y = xinput_state.Gamepad.sThumbRY;

	l_trigger_ = xinput_state.Gamepad.bLeftTrigger;
	r_trigger_ = xinput_state.Gamepad.bRightTrigger;

	for(u32 i = 0; i < (u32)KEY::MAX;++i)
	{
		is_trigger_[i] = (is_press[i] ^ is_press_[i]) & is_press[i];

		is_release_[i] = (is_press[i] ^ is_press_[i]) & !is_press[i];

		is_press_[i] = is_press[i];
	}
}

void XIPad::Clear(void)
{
	l_stick_ = float2(0.0f,0.0f);
	r_stick_ = float2(0.0f,0.0f);
	l_trigger_ = 0.0f;
	r_trigger_ = 0.0f;

	for(u32 i = 0;i < (u32)KEY::MAX;++i)
	{
		is_press_[i] = false;
		is_trigger_[i] = false;
		is_release_[i] = false;
	}
}

bool XIPad::IsPress(KEY in_key) const
{
	return is_press_[(u32)in_key];
}

bool XIPad::IsTrigger(KEY in_key) const
{
	return is_trigger_[(u32)in_key];
}

bool XIPad::IsRelease(KEY in_key) const
{
	return is_release_[(u32)in_key];
}

const float2& XIPad::GetLStick(void) const
{
	return l_stick_;
}

const float2& XIPad::GetRStick(void) const
{
	return r_stick_;
}

f32 XIPad::GetLTrigger(void) const
{
	return l_trigger_;
}

f32 XIPad::GetRTrigger(void) const
{
	return r_trigger_;
}
} // namespace directinput8
} // namespace input

//---------------------------------- EOF --------------------------------------
