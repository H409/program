//*****************************************************************************
//
// scene
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************
class SceneFactory;

//*****************************************************************************
// class definition
//*****************************************************************************
class Scene
{
public:
	enum TYPE
	{
		TYPE_LOGO = 0,		// �^�C�g���O�̃��S
		TYPE_TITLE,			// �^�C�g��
		TYPE_GAME,			// �Q�[��
		TYPE_RESULT,		// ���U���g
		TYPE_MAX			// �^�C�v�̍ő吔
	};

	// constructor
	Scene(const TYPE& type);

	// destructor
	virtual ~Scene(void);

	// initialize
	virtual bool Initialize(void){ return true; }

	// uninitialize
	virtual void Uninitialize(void){}

	// update
	virtual void Update(void){}

	// draw
	virtual void Draw(void){}

	// create factory
	virtual SceneFactory* CreateFactory(void)const{ return nullptr; }

	// accessor
	const TYPE& __type(void)const { return type_; }
	SceneFactory* __next_scene_factory(void)const { return next_scene_factory_; }
	void __is_fade(bool is_fade) { is_fade_ = is_fade; }
	bool __is_stop(void) { return is_stop_; }

protected:
	SceneFactory* next_scene_factory_;
	bool is_fade_;
	bool is_stop_;

private:
	TYPE type_;
};

#endif	// _SCENE_H_

//---------------------------------- EOF --------------------------------------
