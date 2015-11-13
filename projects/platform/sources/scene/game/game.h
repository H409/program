//*****************************************************************************
//
// game.h
//
// Author		: Masahiro Yamaguchi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "../base/scene_base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************


//*****************************************************************************
// class definition
//*****************************************************************************
class Game : public SceneBase
{
public:
	// �R���X�g���N�^
	Game();

	// �f�X�g���N�^
	virtual ~Game();

	// �V�[���̏������B
	virtual bool Initialize(SceneManager* p_scene_manager) override;

	// �V�[���̏I�������B
	virtual void Finalize(void) override;

	// �X�V�������s���B
	virtual void Update(void) override;

	// �`�揈�����s���B
	virtual void Draw(void) override;
private:

};

#endif