//=============================================================================
//
// �v���~�e�B�u�\������ [main.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)    // �x���΍��p
#include "dinput.h"
#include "debug.h"
#include "xaudio2.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment(lib,"winmm.lib")

//�v�Z���x�㏸
#pragma intrinsic(sqrt,pow,sin,cos,tan,asin,acos,atan)


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"GM31"				// �E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define SAFE_RELEASE(p)	{if(p != NULL){(p)->Release(); (p) = NULL;}}
#define SAFE_DELETE(p)	{if(p != NULL){delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p != NULL){delete [] (p); (p) = NULL;}}
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1 )
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//�p�[�e�B�N��
#define FVF_VERTEX_PATCLE	(D3DFVF_XYZ |  D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_MINE		(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct 
{
	D3DXVECTOR3 vtx;	//���_���W
	float rhw;
	D3DCOLOR diffuse;	//���ˌ�
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;
// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;						// ���_���W
	D3DXVECTOR3 nor;						// �@���x�N�g��
	D3DCOLOR diffuse;						// ���ˌ�
	D3DXVECTOR2 tex;						// �e�N�X�`�����W

} VERTEX_3D;
// ���_�t�H�[�}�b�g�̒�`
typedef struct _TLVERTEX
{
	float		x,y,z;
	D3DCOLOR	color;
	float		tu,tv;
}TLVERTEX,*LPTLVERTEX;

typedef enum
{
	MODE_TITLE,
	MODE_TUTOLIAL,
	MODE_GAME,
	MODE_RESULT,
//	MODE_GAMEOVER,
//	MODE_RANKING,
	MODE_MAX
}MODE;

//��std���g�p����
//using namespace std;

//�J�b�R�C�C�I�I�@SAFE_RELEASE�֐��I�I define�}�N���Ȃ�Ă����Â�
template <class Interface>	//�������_�u���|�C���^�Ȃ̂Ł�������
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if(*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Relase();
		(*ppInterfaceToRelease) = nullptr;
	}
}
int GetFPS(void);


/*
//�N���X
class List
{
public:
	struct Node
	{
		Node* mNext;
		Node* mPrev;
		double mValue;
	};
	List();
	~List();
	//�ǉ� �S�ďꏊ��Ԃ�
	Node* addBefore( Node* , double value ); //�w��ꏊ�̑O�ɒǉ�
	Node* addAfter( Node*, double value ); //�w��ꏊ�̌�ɒǉ�
	Node* addHead( double value ); //�擪�ǉ�
	Node* addTail( double value ); //�����ǉ�
	//�폜
	void remove( Node* ); //�w��ꏊ���폜
	void removeHead(); //�擪���폜
	void removeTail(); //�������폜
	//�擾�n
	double value( Node* ) const;
	Node* next( Node* ) const;
	Node* previous( Node* ) const;
	Node* first() const;
	Node* last() const;
private:
	Node mDummyHead;
	Node mDummyTail;
};
//�擪�Ɩ��������ʈ�������Ȃ��悤�ɂ�����ƍH�v�����Ă���B
List::List(){
	//�ŏ���肳��ɑO�ɂ���_�~�[�v�f
	mDummyHead.mNext = &mDummyTail;
	mDummyHead.mPrev = 0;
	mDummyHead.mValue = 0.0;
	//�Ō�̗v�f�̂���Ɍ�ɂ���_�~�[�v�f�B
	mDummyTail.mNext = 0;
	mDummyTail.mPrev = &mDummyHead;
	mDummyTail.mValue = 0.0;
}

List::~List(){
	//�S�������ĉ��Ȃ��Ƃ����Ȃ�
	Node* p = first();
	while ( p )
	{
		Node* nxt = next( p );
		delete p;
		p = nxt;
	}
}

List::Node* List::addAfter( Node* cur, double v )
{
	Node* e = new Node();
	//���̓z�����o��
	Node* nxt = cur->mNext;
	//�l�i�[
	e->mValue = v;
	e->mPrev = cur; //�w��ꏊ���O��
	e->mNext = nxt; //�w��̎��̂�����
	//�w��̓z�͑O�ɂȂ�̂ŁA���͑������z�ɂȂ�
	cur->mNext = e;
	//�w��̎��̓z�͌�ɂȂ�̂ŁA�O�͑������z�ɂȂ�
	nxt->mPrev = e;

	return e;
}

List::Node* List::addBefore( Node* cur, double v )
{
	Node* e = new Node();
	//�O�̓z�����o��
	Node* prev = cur->mPrev;
	//�l�i�[
	e->mValue = v;
	e->mPrev = prev; //�w��̑O�̓z���O
	e->mNext = cur; //�w��̓z����
	//�w��̓z�͌�ɂȂ�̂ŁA�O�͑������z�ɂȂ�
	cur->mPrev = e;
	//�w��̑O�̓z�͑O�ɂȂ�̂ŁA��͑������z�ɂȂ�
	prev->mNext = e;

	return e;
}

List::Node* List::addHead( double v )
{
	return addBefore( first(), v ); //�_�~�[�v�f�̂������ł���������B
}

List::Node* List::addTail( double v )
{
	return addAfter( last(), v ); //�_�~�[�v�f�̂������ł���������
}

void List::remove( Node* cur )
{
	//��
	Node* nxt = cur->mNext;
	//�O
	Node* prev = cur->mPrev;
	//�O�̓z�̎����A���ɂ���B
	prev->mNext = nxt;
	//���̓z�̑O���A�O�ɂ���B
	nxt->mPrev = prev;
	//����
	delete cur;
	cur = 0;
}

void List::removeHead()
{ //����͂قƂ�Ǖʖ��B
	remove( first() );
}

void List::removeTail()
{ //����͂قƂ�Ǖʖ��B
	remove( last() );
}

double List::value( Node* p ) const 
{
	return p->mValue;
}

List::Node* List::next( Node* p ) const 
{
	Node* r = p->mNext;
	if ( r == &mDummyHead || r == &mDummyTail )
	{
		return 0;
	}
	else
	{
		return r;
	}
}

List::Node* List::previous( Node* p ) const 
{
	Node* r = p->mPrev;
	if ( r == &mDummyHead || r == &mDummyTail )
	{
		return 0;
	}
	else
	{
		return r;
	}
}

List::Node* List::first() const 
{
	return mDummyHead.mNext; //�_�~�[�擪�̎����{���̐擪
}

List::Node* List::last() const 
{
	return mDummyTail.mPrev; //�_�~�[�����̑O���{���̖���
}
*/
#endif