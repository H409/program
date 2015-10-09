//=============================================================================
//
// �X�L���A�j���[�V�����̏��� [CSkinAnimetion.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __CSKINANIMETION_H__
#define __CSKINANIMETION_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"


//�O���錾
class CRender;
class CSceneX;

typedef struct THING
{	
	LPD3DXMESH pMesh;
	LPD3DXFRAME pFrameRoot;
	LPD3DXANIMATIONCONTROLLER pAnimController;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures; 
	DWORD dwNumMaterials;
	D3DXVECTOR3 vecPosition;
	D3DXMATRIX matRotation;
	D3DXMATRIX matWorld;

	THING()
	{
		ZeroMemory(this,sizeof(THING));
	}
}THING;


//�h���t���[���\���� (���ꂼ��̃��b�V���p�̍ŏI���[���h�s���ǉ�����j
struct MYFRAME: public D3DXFRAME
{
    D3DXMATRIX CombinedTransformationMatrix;
};
//�h�����b�V���R���e�i�[�\����(
//�R���e�i�[���e�N�X�`���𕡐����Ă�悤�Ƀ|�C���^�[�̃|�C���^�[��ǉ�����j
struct MYMESHCONTAINER: public D3DXMESHCONTAINER
{
    LPDIRECT3DTEXTURE9*  ppTextures;
    DWORD dwWeight;//�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
	DWORD dwBoneAmt;//�{�[���̐�
    LPD3DXBUFFER pBoneBuffer;//�{�[���E�e�[�u��
    D3DXMATRIX** ppBoneMatrix;//�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
    D3DXMATRIX* pBoneOffsetMatrices;//�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
};
//X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����Ă����N���X��h��������B
//ID3DXAllocateHierarchy�͔h�����邱�Ƒz�肵�Đ݌v����Ă���B
class MY_HIERARCHY: public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY(){}
    STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
    STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR ,CONST D3DXMESHDATA* ,CONST D3DXMATERIAL* , 
		CONST D3DXEFFECTINSTANCE* , DWORD , CONST DWORD *, LPD3DXSKININFO , LPD3DXMESHCONTAINER *);
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME );
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER );	
};
//
//
//
class SKIN_MESH
{
public:
	HRESULT InitThing(LPDIRECT3DDEVICE9,THING *,LPSTR,D3DXVECTOR3*);
	HRESULT AllocateBoneMatrix( THING* , LPD3DXMESHCONTAINER  );
	HRESULT AllocateAllBoneMatrices(THING* ,  LPD3DXFRAME  );
	VOID RenderMeshContainer(LPDIRECT3DDEVICE9, MYMESHCONTAINER* ,MYFRAME* );
	VOID UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );
	VOID DrawFrame(LPDIRECT3DDEVICE9,LPD3DXFRAME );

	MY_HIERARCHY GetHierarchy(void)
	{
		return cHierarchy;
	}
protected:
	MY_HIERARCHY cHierarchy;

};


#endif