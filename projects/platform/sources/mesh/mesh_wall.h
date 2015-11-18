#ifndef MESHWALL
#define MESHWALL

#define WALL_MAX (4)
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)	//�C���f�b�N�X���v�Z�p

class MeshWall:public CScene3D
{
	public:
	MeshWall(LPDIRECT3DDEVICE9 device):CScene3D(device){pDevice=device;m_pIndexBuff=NULL;};
	MeshWall(int nPriority):CScene3D(nPriority){}
	virtual ~MeshWall();

	HRESULT Init(	float posX,float posY,float posZ,float rotY,
					int nNumBlockX,int nNumBlockZ,float fSizeBlockX,
					float fSizeBlockZ);			//���b�V���t�B�[���h������

	void Uninit(void);							//���
	void Update(void);							//���f���X�V
	void Draw(void);							//���f���`��
	static MeshWall* Create(LPDIRECT3DDEVICE9 device,float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY);


	void SetLength(void);						//�ǂ��猩�����S�܂ł̋�����ݒ�
	void SetEdge(void);							//�ǂ̊p�̍��W�̐ݒ�

	void SetPosition(D3DXVECTOR3 pos);			//���W�A�N�Z�T�[
	void SetPosition(float x,float y,float z);
	D3DXVECTOR3 GetPosition(void){return m_pos;};

	void SetRotation(D3DXVECTOR3 rot);			//�p�x�A�N�Z�T�[
	void SetRotation(float x,float y,float z);
	void SetRotationFromCenter(float x,float y,float z){m_rot_from_center = D3DXVECTOR3(x,y,z);};
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	static D3DXVECTOR3 GetEdge(int id){return m_edges[id];};

private:


	int m_NumBlockX,m_NumBlockZ;				//�u���b�N��
	int m_NumVtx;								//�����_��
	int m_NumPolygon;							//���|���S����
	float m_SizeBlockX,m_SizeBlockZ;			//�u���b�N�T�C�Y
	float m_wallsizeX;							//�ǂ̑傫��X
	float m_wallsizeY;							//�ǂ̑傫��Y

	D3DXVECTOR3			m_rot_from_center;		//���S�_����̉�]
	D3DXVECTOR3			m_edge;					//�ǂ̊p���W(����)

	float				m_Length_Edge_From_CenterXZ;		//�ǂ̊p���畔���̒��S�܂ł̋���
	float				m_Length_From_CenterXZ;				//�ǂ̒��S���畔���̒��S�܂ł̋���
	D3DXVECTOR3			m_center;							//�ǂ��猩�����S�̍��W

	int m_id;												//�ǂ̌l�ԍ�
	static int m_WallSum;									//���ݍ쐬���ꂽ�ǂ̐�
	static D3DXVECTOR3 m_edges[WALL_MAX];					//�ǂ̊p��ۑ�����static�ϐ�

	LPDIRECT3DINDEXBUFFER9 m_pIndexBuff;		// �C���f�b�N�X�o�b�t�@
};

#endif