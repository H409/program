#ifndef MESHWALL
#define MESHWALL

#define WALL_MAX (4)
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)	//インデックス数計算用

class MeshWall:public CScene3D
{
	public:
	MeshWall(LPDIRECT3DDEVICE9 device):CScene3D(device){pDevice=device;m_pIndexBuff=NULL;};
	MeshWall(int nPriority):CScene3D(nPriority){}
	virtual ~MeshWall();

	HRESULT Init(	float posX,float posY,float posZ,float rotY,
					int nNumBlockX,int nNumBlockZ,float fSizeBlockX,
					float fSizeBlockZ);			//メッシュフィールド初期化

	void Uninit(void);							//解放
	void Update(void);							//モデル更新
	void Draw(void);							//モデル描画
	static MeshWall* Create(LPDIRECT3DDEVICE9 device,float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY);


	void SetLength(void);						//壁から見た中心までの距離を設定
	void SetEdge(void);							//壁の角の座標の設定

	void SetPosition(D3DXVECTOR3 pos);			//座標アクセサー
	void SetPosition(float x,float y,float z);
	D3DXVECTOR3 GetPosition(void){return m_pos;};

	void SetRotation(D3DXVECTOR3 rot);			//角度アクセサー
	void SetRotation(float x,float y,float z);
	void SetRotationFromCenter(float x,float y,float z){m_rot_from_center = D3DXVECTOR3(x,y,z);};
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	static D3DXVECTOR3 GetEdge(int id){return m_edges[id];};

private:


	int m_NumBlockX,m_NumBlockZ;				//ブロック数
	int m_NumVtx;								//総頂点数
	int m_NumPolygon;							//総ポリゴン数
	float m_SizeBlockX,m_SizeBlockZ;			//ブロックサイズ
	float m_wallsizeX;							//壁の大きさX
	float m_wallsizeY;							//壁の大きさY

	D3DXVECTOR3			m_rot_from_center;		//中心点からの回転
	D3DXVECTOR3			m_edge;					//壁の角座標(左側)

	float				m_Length_Edge_From_CenterXZ;		//壁の角から部屋の中心までの距離
	float				m_Length_From_CenterXZ;				//壁の中心から部屋の中心までの距離
	D3DXVECTOR3			m_center;							//壁から見た中心の座標

	int m_id;												//壁の個人番号
	static int m_WallSum;									//現在作成された壁の数
	static D3DXVECTOR3 m_edges[WALL_MAX];					//壁の角を保存するstatic変数

	LPDIRECT3DINDEXBUFFER9 m_pIndexBuff;		// インデックスバッファ
};

#endif