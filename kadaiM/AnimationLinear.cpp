//=============================================================================
//
// �V�[���J�ڏ��� [AnimationLinear.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//=============================================================
// AnimationLinear.cpp
// ���`��Ԃɂ��L�[�t���[���A�j���[�V�����N���X�̎���
//=============================================================
#include "AnimationLinear.h"

//=============================================================
// ����
//=============================================================
//-------------------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//-------------------------------------------------------------
AnimationLinear::AnimationLinear()
 : m_numKey(0), m_keys(0), m_values(0), m_isLoop(TRUE), m_startTime(0), m_duration(0)
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
AnimationLinear::~AnimationLinear()
{
	if(m_keys != 0) 
	{
		delete[] m_keys;
	}

	if(m_values != 0) 
	{
		delete[] m_values;
	}
}

//---------------------------------------------------------
// �L�[�̐���
// ����
//		numKey : �L�[�̐�
//---------------------------------------------------------
void AnimationLinear::CreateKey(int numKey)
{

	// �L�[�t���[�����̐ݒ�
	m_numKey = numKey;

	// �Â��f�[�^���폜
	if(m_keys != 0) 
	{
		delete[] m_keys;
	}

	if(m_values != 0) 
	{
		delete[] m_values;
	}

	// �V�����z��̐���
	m_keys   = new float[m_numKey];
	m_values = new float[m_numKey];

}
	
//---------------------------------------------------------
// �L�[�ƃL�[�ɑΉ�����l�̐ݒ�
// �L�[�͏����������珇�Ԃɐݒ肷�邱��
// 2�x�ڈȍ~�����C���f�b�N�X���g�p�����ꍇ�͏㏑�������
// ����
//		index : �C���f�b�N�X, 0 <= index < createKey�Ő��������L�[�̐�
//		key   : �L�[, 0.0f <= key <= 1.0f
//		value : �L�[�ɑΉ�����l
//---------------------------------------------------------
void AnimationLinear::SetKeyValue(int index, float key, float value)
{
	//�C���f�b�N�X��0��菬�����A�܂��͌��݂̃L�[�̐��ȏ�Ȃ牽�����Ȃ�
	if((index < 0) || (index >= m_numKey)) 
	{
		return;
	}

	m_keys[index]	= key;
	m_values[index]	= value;
}

//---------------------------------------------------------
// �A�j���[�V�����̒���(�L�[��0����1�܂ŕω�����̂ɂ����鎞��)�̐ݒ�
// ����
//		duration : ����(�~���b)
//---------------------------------------------------------
void AnimationLinear::SetDuration(DWORD duration)
{
	// �A�j���[�V�����S�̂̌p�����Ԃ������o�ϐ��ɕۑ�
	m_duration = duration;
}

//---------------------------------------------------------
// �A�j���[�V���������[�v���邩�ǂ����̐ݒ�
// ����
//		isLoop : TRUE�Ȃ烋�[�v����, FALSE�Ȃ烋�[�v���Ȃ�
//---------------------------------------------------------
void AnimationLinear::SetLoopFlag(DWORD isLoop)
{
	m_isLoop = isLoop;
}

//---------------------------------------------------------
// �A�j���[�V�����J�n�����̐ݒ�
// ����
//		start : �A�j���[�V�����̊J�n����(�~���b)
//---------------------------------------------------------
void AnimationLinear::SetStartTime(DWORD start)
{
	m_startTime = start;
}

//---------------------------------------------------------
// �����ɑΉ�����l���擾����
// ����
//		time   : ����(�~���b)
//		pValue : ���ʂ��󂯎��ϐ��ւ̃|�C���^
//		pIsEnd : �A�j���[�V�����I������t���O���󂯎��ϐ��ւ̃|�C���^, �I�����Ă�����TRUE������Ȃ����FALSE
// �߂�l
//		�l�̎擾�ɐ���������TRUE, ���s������FALSE
//---------------------------------------------------------
BOOL AnimationLinear::GetValue(DWORD time, float* pValue, BOOL* pIsEnd)
{
	if(pValue == 0) 
	{
		return FALSE;
	}

	if(pIsEnd == 0) 
	{
		return FALSE;
	}

	if(m_numKey <= 0) 
	{
		return FALSE;
	}

	//----------------------------------------
	//�A�j���[�V�������I�����Ă����Ƃ��̏���
	//----------------------------------------
	DWORD	endTime = m_startTime + m_duration;	//�I������

	if(!m_isLoop) 
	{	// ���[�v���Ȃ��ꍇ
		if(time < m_startTime) 
		{ 
			// �������J�n����������������΍ŏ��̒l��Ԃ�
			*pValue = m_values[0];
			*pIsEnd = TRUE;
			return TRUE;
		}
		else if(time > endTime) 
		{ 
			// �������I�����������傫����΍Ō�̒l��Ԃ�
			*pValue = m_values[m_numKey - 1];
			*pIsEnd = TRUE;
			return TRUE;
		}
	}

	//----------------------------------------
	//�A�j���[�V�����̌v�Z
	//----------------------------------------
	int		beginIndex;
	int		endIndex;
	float	fraction;
	float	slope;

	// ���ݎ����������ɕϊ�
	fraction = GetFraction(time);
	// ���ݎ����ɂ����Ƃ��߂����O�̃L�[�t���[���擾
	beginIndex = GetBeginIndex(fraction);
	// ���ݎ����ɂ����Ƃ��߂�����̃L�[�t���[���擾
	endIndex = beginIndex + 1;

	// �l�̌v�Z
	if(beginIndex < 0) 
	{	// �A�j���[�V�����J�n�O
		*pValue = m_values[0];	// �ŏ��̃L�[�t���[���̒l��Ԃ�
	}
	else if(beginIndex >= m_numKey - 1) 
	{	// �A�j���[�V�����I����
		*pValue = m_values[m_numKey - 1];	// �Ō�̃L�[�t���[���̒l��Ԃ�
	}
	else 
	{
		// �X���i1.0������̑����ʁj�����߂�
		float diffValue = m_values[endIndex] - m_values[beginIndex];// �L�[�t���[���Ԃ̒l�̍�
		float diffTime = m_keys[endIndex] - m_keys[beginIndex];		// �L�[�t���[���Ԃ̌p������
		slope = diffValue / diffTime; 

		// ���ݒl�����߂�
		float fPastFromPrev = fraction - m_keys[beginIndex];	// ���O�̃L�[�t���[������̌o�ߎ��ԁi���ݎ���- ���O�̃L�[�t���[���̎����j
		*pValue = slope * fPastFromPrev + m_values[beginIndex]; // ���ݒl�̌v�Z
	}

	*pIsEnd = FALSE;

	return TRUE;
}

//---------------------------------------------------------
// �����������ɕϊ�����
// ����
//		time   : ����(�~���b)
// �߂�l
//		����
//---------------------------------------------------------
float AnimationLinear::GetFraction(DWORD time)
{
	DWORD	diffTime;
	float	fraction;

	// �������犄�������߂�
	if(m_duration == 0) 
	{
		fraction = 1.0f;
	}
	else 
	{
		if(time > m_startTime) 
		{
			//�ʏ폈��
			// ���ݎ�������X�^�[�g����������
			diffTime = time - m_startTime;
			// ���[�v�Ή�
			diffTime = diffTime % m_duration;
			//�����̌v�Z
			fraction = (float)diffTime / (float)m_duration;
			//�������������g�p
			fraction = fraction - (int)fraction;
		}
		else 
		{
			//�����A���ݎ������A�X�^�[�g������菬�����Ƃ�
			//�^�C�}�[��������Ă��܂����Ƃ���������
			diffTime = m_startTime - time;
			diffTime = diffTime % m_duration;
			fraction = (float)diffTime / (float)m_duration;
			fraction = 1.0f - (fraction - (int)fraction);
		}
	}

	return fraction;
}

//---------------------------------------------------------
// �����ɑΉ�����C���f�b�N�X���擾����
// ����
//		fraction : ����
// �߂�l
//		�z��̃C���f�b�N�X, fraction���o�^����Ă���L�[��菬�������-1
//---------------------------------------------------------
int AnimationLinear::GetBeginIndex(float fraction)
{
	if(fraction < m_keys[0])
		return -1;

	// �����Ɏw�肳�ꂽ�����ƃL�[�t���[���̊������r����
	int index = 0;
	for(int i = 0; i < m_numKey; i++) 
	{
		// �L�[�t���[�����傫���Ȃ����甭��
		if(m_keys[i] <= fraction) 
		{
			index = i;
		}
		else 
		{
			break;
		}
	}

	return index;
}