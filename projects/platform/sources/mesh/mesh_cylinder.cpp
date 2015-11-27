#include "mesh_cylinder.h"

Cylinder::~Cylinder()
{

}
Cylinder* Cylinder::Create(LPDIRECT3DDEVICE9 device)
{

	Cylinder* p=new Cylinder(device);
	p->Init(0.0f,0.0f,0.0f,0.0f,20,20,10.0f,10.0f);
	p->SetPosition(0.0f,200.0f,100.0f);
	return p;

}
HRESULT Cylinder::Init(	float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY)
{
	VERTEX_3D *pVtx;			//頂点情報
	WORD *pIndex;				//インデックス情報

	//法線バッファの動的確保
	m_normalBuf = new D3DXVECTOR3[nNumBlockX*nNumBlockY*2];

	//ポジション初期化
	m_pos=D3DXVECTOR3(posX,posY,posZ);

	//回転(ラジアン)
	m_rot = D3DXVECTOR3(0.0f,rotY,0.0f);
	//拡大縮小
	m_scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//シリンダーの円周
	m_circumference=nNumBlockX*fSizeBlockX;
	//シリンダーの半径
	m_radius=m_circumference/D3DX_PI/2;
	//シリンダーの面一枚の角度
	float facedigree=(D3DX_PI*2)/fSizeBlockX;

	//インデックス番号最大数
	g_VtxIdxNum = SUM_INDEX(nNumBlockX,nNumBlockY);

	//頂点座標番号最大数
	g_NumVtx = (nNumBlockX+1)*(nNumBlockY+1);

	//ポリゴン数
	g_NumPolygon = ((nNumBlockX*2)*nNumBlockY)+((nNumBlockY-1)*4);


		//インデックスバッファの生成
	if(FAILED(pDevice->CreateIndexBuffer(	sizeof(WORD)*g_VtxIdxNum,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_pIndexBuff,
											NULL)))
	{
		return E_FAIL;
	}
	//頂点バッファの生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*g_NumVtx,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&g_pD3DVtxBuff,
										NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(GetDevice(),"data/TEXTURE/tatemono.bmp",&g_pD3DTexture);

	//頂点座標の設定
	g_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	for(int y=0,num=0;y<nNumBlockY+1;y++)
	{
		for(int x=0;x<nNumBlockX+1;x++)
		{
			//pVtx[num].vtx = D3DXVECTOR3(-(nNumBlockX*fSizeBlockX/2)+(fSizeBlockX*x),(nNumBlockY*fSizeBlockY/2)+(-fSizeBlockY*y),0);
			pVtx[num].vtx = D3DXVECTOR3(-(cosf(facedigree*-x))*m_radius,(-fSizeBlockY*y),(sinf(facedigree*-x))*m_radius);
			pVtx[num].nor = D3DXVECTOR3(0,1.0f,0);
			pVtx[num].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[num].tex = D3DXVECTOR2((float)x/5,(float)y/5);
			num++;
		}
	}
	//法線バッファの初期化(メッシュフィールド形成する、各ポリゴンの法線を求め、保存する)
	D3DXVECTOR3 a,b;			//1面の一辺保存
	D3DXVECTOR3 c,d,e;			//法線ベクトル保存
	for(int z = 0;z < nNumBlockY;z++)
	{
		for(int x = 0;x < nNumBlockX;x++)
		{
			//面1
			a=	pVtx[x+((nNumBlockX+1)*z)+1].vtx				-	pVtx[x+((nNumBlockX+1)*z)].vtx;
			b=	pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+1)].vtx	-	pVtx[x+((nNumBlockX+1)*z)].vtx;
			D3DXVec3Cross(&c,&a,&b);
			D3DXVec3Normalize(&c,&c);
			m_normalBuf[x*2+(z*nNumBlockX*2)]=c;

			//面2
			a=pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+1)].vtx	-	pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+2)].vtx;
			b=pVtx[x+((nNumBlockX+1)*z)+1].vtx				-	pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+2)].vtx;
			D3DXVec3Cross(&c,&a,&b);
			D3DXVec3Normalize(&c,&c);
			m_normalBuf[x*2+(z*nNumBlockX*2)+1]=c;
		}
	}
	//頂点法線の計算
	//※頂点法線とは各頂点の持つ法線ベクトルのこと
	//頂点が四角形のポリゴンの対角線をなしている場合、隣接するすべての三角ポリゴンの法線から求める
	for(int x=0;x<(nNumBlockX+1)*(nNumBlockY+1);x++)
	{
		int VtxNum= x;
		//頂点番号が左上にある場合
		if(VtxNum == 0)
		{
			pVtx[VtxNum].nor = D3DXVECTOR3(m_normalBuf[0]);
		}

		//頂点番号が右上にある場合
		else if(VtxNum == nNumBlockX)
		{
			D3DXVECTOR3 a = m_normalBuf[(nNumBlockX*2)-2];
			D3DXVECTOR3 b = m_normalBuf[(nNumBlockX*2)-1];
			D3DXVECTOR3 c = a+b;
			D3DXVec3Normalize(&c,&c);
			pVtx[VtxNum].nor=D3DXVECTOR3(c);
		}

		//頂点番号が右下にある場合
		else if(VtxNum == (nNumBlockX+1) * (nNumBlockY+1) - 1)
		{
			pVtx[VtxNum].nor = D3DXVECTOR3(m_normalBuf[(nNumBlockX+1)*(nNumBlockY+1)-1]);
		}

		//頂点番号が左下にある場合
		else if(VtxNum == (nNumBlockX+1) * nNumBlockY)
		{
			D3DXVECTOR3 a = m_normalBuf[(nNumBlockX*2) * nNumBlockY];
			D3DXVECTOR3 b = m_normalBuf[(nNumBlockX*2) * nNumBlockY + 1];
			D3DXVECTOR3 c = a+b;
			D3DXVec3Normalize(&c,&c);
			pVtx[VtxNum].nor=D3DXVECTOR3(c);
		}
		//頂点番号が上端にある場合
		else if(VtxNum < (nNumBlockX+1))
		{
			D3DXVECTOR3 a = m_normalBuf[VtxNum * 2 - 2];
			D3DXVECTOR3 b = m_normalBuf[VtxNum * 2 - 1];
			D3DXVECTOR3 c = m_normalBuf[VtxNum * 2];
			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}
		//頂点番号が下端にある場合
		else if(VtxNum > (nNumBlockX+1) * nNumBlockY)
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum * 2) - ((nNumBlockX*2)+(nNumBlockY*2)+1)];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum * 2) - ((nNumBlockX*2)+(nNumBlockY*2)+1) + 1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum * 2) - ((nNumBlockX*2)+(nNumBlockY*2)+1) + 2];

			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}
		//頂点番号が左端にある場合
		else if(VtxNum != 0 && VtxNum % (nNumBlockX+1) == 0)
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - (nNumBlockX*2)];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - (nNumBlockX*2)+1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2)];
			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}	
		//頂点番号が右端にある場合
		else if((VtxNum - nNumBlockX) % (nNumBlockX+1) == 0)
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - 1];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - 1 + (nNumBlockX*2) - 1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - 1 + (nNumBlockX*2)];
			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}
		//上記以外
		else
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1)) +1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1)) + 2];
			D3DXVECTOR3 d = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))+(nNumBlockX*2-1)];
			D3DXVECTOR3 e = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))+(nNumBlockX*2-1) + 1];
			D3DXVECTOR3 f = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))+(nNumBlockX*2-1) + 2];
			D3DXVECTOR3 g =a+b+c+d+e+f;
			D3DXVec3Normalize(&g,&g);
			pVtx[VtxNum].nor=D3DXVECTOR3(g);
		}
	}//for
	g_pD3DVtxBuff -> Unlock();

	//インデックスバッファ設定
	g_pIndexBuff->Lock(0,0,(void**)&pIndex,0);

	//繰り返し管理変数
	int loopx=0;
	int VtxNo=0;
	int check=0;

	for(int y = 0;y<nNumBlockY;y++)
	{
		//右下の折り返し地点でのインデックスの保存
		if(y != 0)
		{
			loopx = 0;
			check =				(y*(nNumBlockX+1))+(((loopx+3)%2)*(nNumBlockX+1)+(loopx/2));

			pIndex[VtxNo] =		(y*(nNumBlockX+1))+(((loopx+1)%2)*(nNumBlockX+1)+(loopx/2));
			VtxNo++;
		}
		for(loopx = 0;loopx<(nNumBlockX+1)*2;loopx++)
		{
			check =				(y*(nNumBlockX+1))+(((loopx+3)%2)*(nNumBlockX+1)+(loopx/2));

			pIndex[VtxNo] =		(y*(nNumBlockX+1))+(((loopx+1)%2)*(nNumBlockX+1)+(loopx/2));
			VtxNo++;
		}
		//左上の折り返し地点でのインデックス保存
		pIndex[VtxNo] = pIndex[VtxNo-1];
		VtxNo++;
	}

	g_pIndexBuff->Unlock();

	return S_OK;
}

void Cylinder::Uninit(void)
{
	CScene3D::Uninit();
	//RELEASE_P(g_pIndexBuff)
	DELETE_P(m_normalBuf)
	Release();
}

void Cylinder::Update(void)
{

	if(m_rot.y>D3DX_PI)
	{
		m_rot.y=-D3DX_PI;
	}
	else if(m_rot.y<-D3DX_PI)
	{
		m_rot.y=D3DX_PI;
	}
}

void Cylinder::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//それぞれのマトリクスの設定
	D3DXMatrixIdentity(&g_mtxWorld);

	D3DXMatrixScaling(&mtxScl,1.0f,1.0f,1.0f);							//拡大倍率
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);				//傾き//弧度法で入れる Y,X,Z
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);				//空間の平行移動
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxTranslate);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

	//頂点バッファをデータストリームソースにバインド
	pDevice ->SetStreamSource(0,g_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	
	pDevice->SetIndices(g_pIndexBuff);
	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice ->SetTexture(0,g_pD3DTexture);

	//ポリゴンの描画(インデックスバージョン)
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,g_VtxIdxNum,0,g_NumPolygon);
}


//アクセサー
void Cylinder::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}
void Cylinder::SetPosition(float x,float y,float z)
{
	m_pos= D3DXVECTOR3(x,y,z);
}
void Cylinder::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}
void Cylinder::SetRotation(float x,float y,float z)
{
	m_rot= D3DXVECTOR3(x,y,z);
}