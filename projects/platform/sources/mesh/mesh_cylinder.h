#ifndef CYLINDER
#define CYLINDER
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)	//インデックス数計算用

class Cylinder:public CScene3D
{
	public:
	Cylinder(LPDIRECT3DDEVICE9 device):CScene3D(device){pDevice=device;};
	Cylinder(int nPriority):CScene3D(nPriority){}
	virtual ~Cylinder();

	HRESULT Init(	float posX,float posY,float posZ,float rotY,
					int nNumBlockX,int nNumBlockZ,float fSizeBlockX,
					float fSizeBlockZ);			//メッシュフィールド初期化

	void Uninit(void);							//解放
	void Update(void);							//モデル更新
	void Draw(void);							//モデル描画
	static Cylinder* Create(LPDIRECT3DDEVICE9 device);

	void SetPosition(D3DXVECTOR3 pos);			//座標アクセサー
	void SetPosition(float x,float y,float z);
	D3DXVECTOR3 GetPosition(void){return m_pos;};

	void SetRotation(D3DXVECTOR3 rot);			//角度アクセサー
	void SetRotation(float x,float y,float z);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

private:

	LPDIRECT3DTEXTURE9		g_pD3DTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	g_pD3DVtxBuff;		//頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9	g_pIndexBuff;		//インデックスバッファ
	int g_VtxIdxNum;							//頂点の総インデックス数
	LPDIRECT3DDEVICE9 pDevice;					//デバイス保存ポインタ

	D3DXMATRIX g_mtxWorld;						//ワールドマトリックス

	int g_NumBlockX,g_NumBlockZ;				//ブロック数
	int g_NumVtx;								//総頂点数
	int g_NumPolygon;							//総ポリゴン数
	float g_SizeBlockX,g_SizeBlockZ;			//ブロックサイズ
	
	D3DXVECTOR3			m_pos;					//シリンダーの位置
	D3DXVECTOR3			m_rot;					//シリンダーの回転
	D3DXVECTOR3			m_scl;					//壁の拡大縮小

	float m_cylindersizeX;						//シリンダーの大きさ
	float m_cylindersizeY;
	float m_circumference;						//シリンダーの円周
	float m_radius;								//シリンダーの半径

	D3DXVECTOR3* m_normalBuf;					//法線バッファ
};

#endif