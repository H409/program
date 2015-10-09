//=============================================================================
//
// �X�L���A�j���[�V�����̏��� [CSkinAnimetion.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#include "CSkinAnimetion.h"
#include "CRender.h"

//�x����������
#pragma warning(disable:4996)

//HRESULT MY_HIERARCHY::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
//�t���[�����쐬����
HRESULT MY_HIERARCHY::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
{
    HRESULT hr = S_OK;
    MYFRAME *pFrame;
    *ppNewFrame = NULL;

    pFrame = new MYFRAME;
    if (pFrame == NULL)
    {
		return E_OUTOFMEMORY;    
    }
	pFrame->Name=new TCHAR[lstrlen(Name) + 1];	
    if (!pFrame->Name)
	{
		return E_FAIL;
	}
	strcpy(pFrame->Name,Name);

    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
    pFrame->pMeshContainer = NULL;
    pFrame->pFrameSibling = NULL;
    pFrame->pFrameFirstChild = NULL;
    *ppNewFrame = pFrame;

    return S_OK;
}
//
//HRESULT MY_HIERARCHY::CreateMeshContainer
//���b�V���R���e�i�[���쐬����
HRESULT MY_HIERARCHY::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA* pMeshData,
                            CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances,
							DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
                            LPD3DXMESHCONTAINER *ppMeshContainer) 
{

	HRESULT hr;
	MYMESHCONTAINER *pMeshContainer = NULL;
	INT iFacesAmount;
	INT iMaterial;
	LPDIRECT3DDEVICE9 pDevice = NULL;
	LPD3DXMESH pMesh = NULL;
	*ppMeshContainer = NULL;
	DWORD dwBoneAmt=0;
	
	pMesh = pMeshData->pMesh;
	pMeshContainer = new MYMESHCONTAINER;
	if (pMeshContainer == NULL)
	{
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pMeshContainer, sizeof(MYMESHCONTAINER));
	
	pMeshContainer->Name=new TCHAR[lstrlen(Name) + 1];	
	if (!pMeshContainer->Name)
	{
		return E_FAIL;
	}
	strcpy(pMeshContainer->Name,Name);
	pMesh->GetDevice(&pDevice);
	iFacesAmount = pMesh->GetNumFaces();  
	
	pMeshContainer->MeshData.pMesh = pMesh;   
	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;	
	
	//���b�V���̃}�e���A���ݒ�
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[iFacesAmount*3];
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		return E_FAIL;
	}
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * iFacesAmount*3);
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	
	if (NumMaterials > 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);
	
		for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				TCHAR strTexturePath[MAX_PATH];
				strcpy( strTexturePath,  pMeshContainer->pMaterials[iMaterial].pTextureFilename );
				if( FAILED( D3DXCreateTextureFromFile( pDevice, strTexturePath, 
							&pMeshContainer->ppTextures[iMaterial] ) ) )
					pMeshContainer->ppTextures[iMaterial] = NULL;
				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else
	{
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}
	//���Y���b�V�����X�L�����������Ă���ꍇ�i�X�L�����b�V���ŗL�̏����j
	if (pSkinInfo != NULL)
	{
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();
		dwBoneAmt = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[dwBoneAmt];

		for (DWORD i= 0; i < dwBoneAmt; i++)
		{	
			memcpy(&pMeshContainer->pBoneOffsetMatrices[i],
				pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i),sizeof(D3DMATRIX));	
		}
		if(FAILED(pMeshContainer->pSkinInfo->ConvertToBlendedMesh(
			pMesh,                                       
			NULL,	pMeshContainer->pAdjacency,NULL, NULL, NULL,
			&pMeshContainer->dwWeight,
			&pMeshContainer->dwBoneAmt,
			&pMeshContainer->pBoneBuffer,
			&pMeshContainer->MeshData.pMesh)
			))
		{
			return E_FAIL;
		}
	}
	//���[�J���ɐ����������b�V���R���e�i�[���Ăяo�����ɃR�s�[���� �i�R�s�[����Ȃ����ǁE�E�E�j
	*ppMeshContainer = pMeshContainer;
	//�Q�ƃJ�E���^�𑝂₵���̂Ō��炷
	SAFE_RELEASE(pDevice);

	return S_OK;
}
//
//HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
//�t���[����j������
HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
{
	SAFE_DELETE_ARRAY( pFrameToFree->Name );
	SAFE_DELETE( pFrameToFree );

	return S_OK; 
}
//
//HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
//���b�V���R���e�i�[��j������
HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	INT iMaterial;
	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	
	SAFE_DELETE_ARRAY( pMeshContainer->Name );
	SAFE_RELEASE(pMeshContainer->pSkinInfo);
	SAFE_DELETE_ARRAY( pMeshContainer->pAdjacency );
	SAFE_DELETE_ARRAY( pMeshContainer->pMaterials );
	SAFE_DELETE_ARRAY( pMeshContainer->ppBoneMatrix );

	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE( pMeshContainer->ppTextures[iMaterial] );
		}
	}
	SAFE_RELEASE( pMeshContainer->MeshData.pMesh );
	SAFE_RELEASE( pMeshContainer->pBoneBuffer );
	SAFE_DELETE_ARRAY( pMeshContainer->pBoneOffsetMatrices );
	SAFE_DELETE_ARRAY( pMeshContainer->ppBoneMatrix );   
	SAFE_DELETE( pMeshContainer );

	return S_OK;
}

//
//HRESULT AllocateBoneMatrix( THING* pThing,LPD3DXMESHCONTAINER pMeshContainerBase )
//
HRESULT SKIN_MESH::AllocateBoneMatrix( THING* pThing,LPD3DXMESHCONTAINER pMeshContainerBase )
{
	MYFRAME *pFrame=NULL;
	DWORD dwBoneAmt=0;

	MYMESHCONTAINER *pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}
	dwBoneAmt = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new D3DXMATRIX*[dwBoneAmt];

	for (DWORD i=0; i<dwBoneAmt; i++)
	{
		pFrame = (MYFRAME*)D3DXFrameFind( pThing->pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i) );
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		pMeshContainer->ppBoneMatrix[i] = &pFrame->CombinedTransformationMatrix;
 
	}
	return S_OK;
}
//
//HRESULT AllocateAllBoneMatrices( THING* pThing,LPD3DXFRAME pFrame )
//
HRESULT SKIN_MESH::AllocateAllBoneMatrices( THING* pThing,LPD3DXFRAME pFrame )
{
    if (pFrame->pMeshContainer != NULL)
    {
        if(FAILED(AllocateBoneMatrix(pThing,pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
    }
    if (pFrame->pFrameSibling != NULL)
    {
        if(FAILED(AllocateAllBoneMatrices(pThing,pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
    }
    if (pFrame->pFrameFirstChild != NULL)
    {
        if(FAILED(AllocateAllBoneMatrices(pThing,pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
    }
    return S_OK;
}
//
//
//
HRESULT SKIN_MESH::InitThing(LPDIRECT3DDEVICE9 pDevice,THING *pThing,LPSTR szXFileName,D3DXVECTOR3* pvecPosition)
{
	// ���b�V���̏����ʒu
	memcpy(&pThing->vecPosition,pvecPosition,sizeof(D3DXVECTOR3));

	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
	if( FAILED( D3DXLoadMeshHierarchyFromX(szXFileName, D3DXMESH_MANAGED, pDevice, &cHierarchy, 
			NULL, &pThing->pFrameRoot, &pThing->pAnimController)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���",szXFileName, MB_OK);
		return E_FAIL;
	}
	//
	AllocateAllBoneMatrices(pThing,pThing->pFrameRoot);

	return S_OK;
}
//
//VOID RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice,MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
//�t���[�����̂��ꂼ��̃��b�V���������_�����O����
VOID SKIN_MESH::RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice,MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
{
	DWORD i,k,m;
	DWORD dwBoneIndex,dwBlendMatrixAmt;    
    DWORD dwPrevBoneID;
    LPD3DXBONECOMBINATION pBoneCombination;
    UINT iMatrixIndex;
    D3DXMATRIX matStack;
	//�X�L�����b�V���̏ꍇ
	if(pMeshContainer->pSkinInfo != NULL)
	{
		pBoneCombination = (LPD3DXBONECOMBINATION)pMeshContainer->pBoneBuffer->GetBufferPointer();

		dwPrevBoneID=UINT_MAX;
		for(i = 0; i < pMeshContainer->dwBoneAmt; i++)
		{
			dwBlendMatrixAmt=0;
			for(k = 0; k< pMeshContainer->dwWeight; k++)
			{
				if (pBoneCombination[i].BoneId[k] != UINT_MAX) 
				{
					dwBlendMatrixAmt=k;
				}
			}
			pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixAmt);
			for(k = 0; k < pMeshContainer->dwWeight; k++) 
			{
				iMatrixIndex = pBoneCombination[i].BoneId[k];
				if (iMatrixIndex != UINT_MAX)
				{
					matStack=pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
					pDevice->SetTransform( D3DTS_WORLDMATRIX(k), &matStack );
				}
			}
			pDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D );
			pDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId] );
			dwPrevBoneID = pBoneCombination[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);	
		}		
	}
	//�ʏ탁�b�V���̏ꍇ
	else
	{
		pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
		for (i = 0; i < pMeshContainer->NumMaterials; i++)
		{
			pDevice->SetMaterial( &pMeshContainer->pMaterials[i].MatD3D );
			pDevice->SetTexture( 0, pMeshContainer->ppTextures[i] );
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}
//
//VOID DrawFrame(LPDIRECT3DDEVICE9 pDevice,LPD3DXFRAME pFrameBase)
//�t���[���������_�����O����B
VOID SKIN_MESH::DrawFrame(LPDIRECT3DDEVICE9 pDevice,LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame=(MYFRAME*)pFrameBase;
    MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;	

    while (pMeshContainer != NULL)
    {
        RenderMeshContainer(pDevice,pMeshContainer, pFrame);

        pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
    }
    if (pFrame->pFrameSibling != NULL)
    {
        DrawFrame(pDevice,pFrame->pFrameSibling);
    }
    if (pFrame->pFrameFirstChild != NULL)
    {
        DrawFrame(pDevice,pFrame->pFrameFirstChild);
    }
}
//
//VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
//�t���[�����̃��b�V�����Ƀ��[���h�ϊ��s����X�V����
VOID SKIN_MESH::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME *pFrame = (MYFRAME*)pFrameBase;	
	
	if (pParentMatrix != NULL)
	{
	    D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
	    pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != NULL)
	{
	    UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
	    UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}



/*
	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
	if( FAILED(D3DXLoadMeshHierarchyFromX(pxfilename, D3DXMESH_MANAGED, m_pD3DDevice, &cHierarchy, 
					NULL, &m_pFrameRoot, &m_pAnimController)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���",pxfilename, MB_OK);
		return E_FAIL;
	}
*/