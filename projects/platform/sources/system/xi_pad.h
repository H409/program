//*****************************************************************************
//
// xinput pad
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _XI_PAD_H_
#define _XI_PAD_H_

//namespace input {
//namespace directinput8 {
class XIPad
{
public:
	enum class KEY
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		START,
		BACK,
		L1,
		R1,
		L3,
		R3,
		L2,
		R2,
		A,
		B,
		X,
		Y,
		L_LEFT,
		L_RIGHT,
		L_UP,
		L_DOWN,
		R_LEFT,
		R_RIGHT,
		R_UP,
		R_DOWN,
		MAX
	};

	// constructor
	XIPad() {};
	explicit XIPad(u32 in_number);

	// destructor
	virtual ~XIPad(void);

	// update
	void Update(void);

	// clear
	void Clear(void);

	bool GetPress(KEY in_key)const;
	bool GetTrigger(KEY in_key)const;
	bool GetRelease(KEY in_key)const;

	const float2& GetLStick(void)const;
	const float2& GetRStick(void)const;
	f32 GetLTrigger(void)const;
	f32 GetRTrigger(void)const;

private:
	static const s32 X_INPUT_DEEP = 5000;
	static const s8 X_INPUT_TRIGGER_DEEP = 10;
	static const u32 BUTTON_MAX = 16;

	float2 l_stick_;
	float2 r_stick_;
	f32 l_trigger_;
	f32 r_trigger_;
	bool is_press_[(u32)KEY::MAX];
	bool is_trigger_[(u32)KEY::MAX];
	bool is_release_[(u32)KEY::MAX];
	u32 number_;
};
//} // namespace directinput8
//} // namespace input

#endif // _XI_PAD_H_

//---------------------------------- EOF --------------------------------------
