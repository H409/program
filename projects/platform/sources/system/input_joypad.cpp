//=============================================================================
//
// �Q�[���p�b�h���͏��� [input_joypad.cpp]
// Author :
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "input_joypad.h"
#include <math.h>

const int WAIT_TIME = 25;

int InputJoypad::m_joyNum = 0;

InputJoypad::InputJoypad()
{
	// �L�[������
	for (int i = 0; i < (int)KEY_CODE::KEY_NUM; i++)
	{
		m_aKeyState[i] = 0;
		m_aTriggerKey[i] = 0;
		m_aReleaseKey[i] = 0;
		m_aHoldKey[i] = 0;
		m_aRepeatKey[i] = 0;
		m_aCountKey[i] = 0;
	}

	for (int cnt = 0; cnt < (int)KEY_CODE::KEY_NUM - (int)KEY_CODE::KEY_A; cnt++)
	{
		m_nJoyButtonID[cnt] = JOY_BUTTON1 << cnt;
	}

	m_joyState.dwSize = sizeof(JOYINFOEX);
	// �擾���ݒ�
	m_joyState.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNZ | JOY_RETURNR | JOY_RETURNPOV | JOY_RETURNBUTTONS;

	m_joyState.dwButtons = 0;
	m_joyState.dwXpos = 0x7fff;
	m_joyState.dwYpos = 0x7fff;
	m_joyState.dwZpos = 0x7fff;
	m_joyState.dwRpos = 0x7fff;
	m_joyState.dwPOV = 0xffff;
	m_this_id = m_joyNum;
	m_joyNum++;
}

InputJoypad::~InputJoypad()
{
	m_joyNum--;
}

HRESULT InputJoypad::Init()
{
	return S_OK;
}

void InputJoypad::Uninit()
{

}

void InputJoypad::Update()
{
	JOYINFOEX curJoyState;		// ���݂̃L�[���

	curJoyState.dwSize = sizeof(JOYINFOEX);
	curJoyState.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNZ | JOY_RETURNR | JOY_RETURNPOV | JOY_RETURNBUTTONS;

	if (joyGetPosEx(m_this_id, &curJoyState) == JOYERR_NOERROR)
	{
		// ���͏��̃��Z�b�g
		memset(&m_aKeyState[0], 0x00, sizeof(m_aKeyState));
		memset(&m_aTriggerKey[0], 0x00, sizeof(m_aTriggerKey));
		memset(&m_aReleaseKey[0], 0x00, sizeof(m_aReleaseKey));
		memset(&m_aHoldKey[0], 0x00, sizeof(m_aHoldKey));
		memset(&m_aRepeatKey[0], 0x00, sizeof(m_aRepeatKey));

		// �A�i���O�X�e�B�b�N���X�V
#ifndef KEY_RIGHT
		if (curJoyState.dwXpos > 0x7fff + 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_RIGHT] = 0x01;
		}

		if (!(m_joyState.dwXpos > 0x7fff + 0x4000) && (curJoyState.dwXpos > 0x7fff + 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_RIGHT] = 0x01;
		}

		if ((m_joyState.dwXpos > 0x7fff + 0x4000) && !(curJoyState.dwXpos > 0x7fff + 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_RIGHT] = 0x01;
		}

		if ((m_joyState.dwXpos > 0x7fff + 0x4000) && (curJoyState.dwXpos > 0x7fff + 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_RIGHT] = 0x01;
		}
#endif
#ifndef KEY_LEFT
		if (curJoyState.dwXpos < 0x7fff - 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_LEFT] = 0x01;
		}

		if (!(m_joyState.dwXpos < 0x7fff - 0x4000) && (curJoyState.dwXpos < 0x7fff - 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_LEFT] = 0x01;
		}

		if ((m_joyState.dwXpos < 0x7fff - 0x4000) && !(curJoyState.dwXpos < 0x7fff - 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_LEFT] = 0x01;
		}

		if ((m_joyState.dwXpos < 0x7fff - 0x4000) && (curJoyState.dwXpos < 0x7fff - 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_LEFT] = 0x01;
		}
#endif
#ifndef KEY_DOWN
		if (curJoyState.dwYpos > 0x7fff + 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_DOWN] = 0x01;
		}

		if (!(m_joyState.dwYpos > 0x7fff + 0x4000) && (curJoyState.dwYpos > 0x7fff + 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_DOWN] = 0x01;
		}

		if ((m_joyState.dwYpos > 0x7fff + 0x4000) && !(curJoyState.dwYpos > 0x7fff + 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_DOWN] = 0x01;
		}

		if ((m_joyState.dwYpos > 0x7fff + 0x4000) && (curJoyState.dwYpos > 0x7fff + 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_DOWN] = 0x01;
		}
#endif
#ifndef KEY_UP
		if (curJoyState.dwYpos < 0x7fff - 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_UP] = 0x01;
		}

		if (!(m_joyState.dwYpos < 0x7fff - 0x4000) && (curJoyState.dwYpos < 0x7fff - 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_UP] = 0x01;
		}

		if ((m_joyState.dwYpos < 0x7fff - 0x4000) && !(curJoyState.dwYpos < 0x7fff - 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_UP] = 0x01;
		}

		if ((m_joyState.dwYpos < 0x7fff - 0x4000) && (curJoyState.dwYpos < 0x7fff - 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_UP] = 0x01;
		}
#endif

#ifndef KEY_RIGHT_RIGHT
		if (curJoyState.dwZpos > 0x7fff + 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_RIGHT_RIGHT] = 0x01;
		}

		if (!(m_joyState.dwZpos > 0x7fff + 0x4000) && (curJoyState.dwZpos > 0x7fff + 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_RIGHT_RIGHT] = 0x01;
		}

		if ((m_joyState.dwZpos > 0x7fff + 0x4000) && !(curJoyState.dwZpos > 0x7fff + 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_RIGHT_RIGHT] = 0x01;
		}

		if ((m_joyState.dwZpos > 0x7fff + 0x4000) && (curJoyState.dwZpos > 0x7fff + 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_RIGHT_RIGHT] = 0x01;
		}
#endif
#ifndef KEY_RIGHT_LEFT
		if (curJoyState.dwZpos < 0x7fff - 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_RIGHT_LEFT] = 0x01;
		}

		if (!(m_joyState.dwZpos < 0x7fff - 0x4000) && (curJoyState.dwZpos < 0x7fff - 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_RIGHT_LEFT] = 0x01;
		}

		if ((m_joyState.dwZpos < 0x7fff - 0x4000) && !(curJoyState.dwZpos < 0x7fff - 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_RIGHT_LEFT] = 0x01;
		}

		if ((m_joyState.dwZpos < 0x7fff - 0x4000) && (curJoyState.dwZpos < 0x7fff - 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_RIGHT_LEFT] = 0x01;
		}
#endif
#ifndef KEY_RIGHT_DOWN
		if (curJoyState.dwRpos > 0x7fff + 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_RIGHT_DOWN] = 0x01;
		}

		if (!(m_joyState.dwRpos > 0x7fff + 0x4000) && (curJoyState.dwRpos > 0x7fff + 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_RIGHT_DOWN] = 0x01;
		}

		if ((m_joyState.dwRpos > 0x7fff + 0x4000) && !(curJoyState.dwRpos > 0x7fff + 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_RIGHT_DOWN] = 0x01;
		}

		if ((m_joyState.dwRpos > 0x7fff + 0x4000) && (curJoyState.dwRpos > 0x7fff + 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_RIGHT_DOWN] = 0x01;
		}
#endif
#ifndef KEY_RIGHT_UP
		if (curJoyState.dwRpos < 0x7fff - 0x4000)
		{
			m_aKeyState[(int)KEY_CODE::KEY_RIGHT_UP] = 0x01;
		}

		if (!(m_joyState.dwRpos < 0x7fff - 0x4000) && (curJoyState.dwRpos < 0x7fff - 0x4000))
		{
			m_aTriggerKey[(int)KEY_CODE::KEY_RIGHT_UP] = 0x01;
		}

		if ((m_joyState.dwRpos < 0x7fff - 0x4000) && !(curJoyState.dwRpos < 0x7fff - 0x4000))
		{
			m_aReleaseKey[(int)KEY_CODE::KEY_RIGHT_UP] = 0x01;
		}

		if ((m_joyState.dwRpos < 0x7fff - 0x4000) && (curJoyState.dwRpos < 0x7fff - 0x4000))
		{
			m_aHoldKey[(int)KEY_CODE::KEY_RIGHT_UP] = 0x01;
		}
#endif
		// �A�i���O���[�h�\���L�[���X�V
		BYTE povbit[9] = { 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09, 0 };

		int curAngle = curJoyState.dwPOV / 4500; //�����Z�o
		int angle = m_joyState.dwPOV / 4500; //�����Z�o
		if (curAngle < 9)
		{
			for (int cnt = 0; cnt < (int)KEY_CODE::KEY_CROSS_LEFT + 1; cnt++)
			{
				if (povbit[curAngle] & (1 << cnt))
				{
					m_aKeyState[cnt] = 0x01;
				}

				if (!(povbit[angle] & (1 << cnt)) && (povbit[curAngle] & (1 << cnt)))
				{
					m_aTriggerKey[cnt] = 0x01;
				}

				if ((povbit[angle] & (1 << cnt)) && !(povbit[curAngle] & (1 << cnt)))
				{
					m_aReleaseKey[cnt] = 0x01;
				}

				if ((povbit[angle] & (1 << cnt)) && (povbit[curAngle] & (1 << cnt)))
				{
					m_aHoldKey[cnt] = 0x01;
				}
			}
		}
		// �{�^�����X�V
		for (int cnt = 0; cnt < (int)KEY_CODE::KEY_NUM - (int)KEY_CODE::KEY_A; cnt++)
		{
			// �v���X
			if (curJoyState.dwButtons & m_nJoyButtonID[cnt])
			{
				m_aKeyState[(int)KEY_CODE::KEY_A + cnt] = 0x01;
			}
			// �g���K�[
			if (!(m_joyState.dwButtons & m_nJoyButtonID[cnt]) && (curJoyState.dwButtons & m_nJoyButtonID[cnt]))
			{
				m_aTriggerKey[(int)KEY_CODE::KEY_A + cnt] = 0x01;
			}
			// �����[�X
			if ((m_joyState.dwButtons & m_nJoyButtonID[cnt]) && !(curJoyState.dwButtons & m_nJoyButtonID[cnt]))
			{
				m_aReleaseKey[(int)KEY_CODE::KEY_A + cnt] = 0x01;
			}
			// �z�[���h
			if ((m_joyState.dwButtons & m_nJoyButtonID[cnt]) && (curJoyState.dwButtons & m_nJoyButtonID[cnt]))
			{
				m_aHoldKey[(int)KEY_CODE::KEY_A + cnt] = 0x01;
			}
		}
		// �S���s�[�g�L�[���X�V
		for (int nKey = 0; nKey < (int)KEY_CODE::KEY_NUM; nKey++)
		{
			// ���s�[�g�L�[����
			if (m_aCountKey[nKey] == 0)
			{
				m_aRepeatKey[nKey] = m_aTriggerKey[nKey];
			}
			else if (m_aCountKey[nKey] % WAIT_TIME == 0)
			{
				m_aRepeatKey[nKey] = m_aHoldKey[nKey];
			}
			m_aCountKey[nKey] *= (m_aReleaseKey[nKey] ^ 1);
			m_aCountKey[nKey] += m_aHoldKey[nKey];
		}
		// ���݂̃L�[����ۊ�
		m_joyState = curJoyState;
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool InputJoypad::GetPress(int nKey)
{
	return (m_aKeyState[nKey]) ? TRUE : FALSE;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool InputJoypad::GetTrigger(int nKey)
{
	return (m_aTriggerKey[nKey]) ? TRUE : FALSE;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool InputJoypad::GetRepeat(int nKey)
{
	return (m_aRepeatKey[nKey]) ? TRUE : FALSE;
}

//=============================================================================
// �L�[�{�[�h�̃z�[���h��Ԃ��擾
//=============================================================================
bool InputJoypad::GetHold(int nKey)
{
	return (m_aHoldKey[nKey]) ? TRUE : FALSE;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool InputJoypad::GetRelease(int nKey)
{
	return (m_aReleaseKey[nKey]) ? TRUE : FALSE;
}


//=============================================================================
// �E�A�i���O�X�e�B�b�N�̌X���̋���擾 �X���Ă���p�x�����W�A���l�ŕԂ�
//=============================================================================
float InputJoypad::GetRightAnalogStick(void)
{
	//(6/19�X�V)�v�Z���@�����ǂ��܂���
	float fx = (float)m_joyState.dwZpos - 32727.0f;
	float fy = (float)m_joyState.dwRpos - 32727.0f;

	if (fx == 0)
	{
		return (fy >= 0 ? 1 : -1)*D3DX_PI / 2.f;
	}
	else if (fx<0)
	{
		return atan(fy / fx) + D3DX_PI - (D3DX_PI / 2);
	}
	else {
		return atan(fy / fx) - (D3DX_PI / 2);
	}
}

float InputJoypad::GetLeftAnalogStick(void)
{
	float fx = (float)m_joyState.dwXpos - 32727.0f;
	float fy = (float)m_joyState.dwYpos - 32727.0f;
	if (fx == 0)
	{
		return (fy >= 0 ? 1 : -1)*D3DX_PI / 2.f;
	}
	else if (fx<0)
	{
		return atan(fy / fx) + D3DX_PI - (D3DX_PI / 2);
	}
	else {
		return atan(fy / fx) - (D3DX_PI / 2);
	}
}