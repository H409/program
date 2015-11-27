#ifndef CYLINDER
#define CYLINDER
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)	//�C���f�b�N�X���v�Z�p

class Cylinder:public CScene3D
{
	public:
	Cylinder(LPDIRECT3DDEVICE9 device):CScene3D(device){pDevice=device;};
	Cylinder(int nPriority):CScene3D(nPriority){}
	virtual ~Cylinder();

	HRESULT Init(	float posX,float posY,float posZ,float rotY,
					int nNumBlockX,int nNumBlockZ,float fSizeBlockX,
					float fSizeBlockZ);			//���b�V���t�B�[���h������

	void Uninit(void);							//���
	void Update(void);							//���f���X�V
	void Draw(void);							//���f���`��
	static Cylinder* Create(LPDIRECT3DDEVICE9 device);

	void SetPosition(D3DXVECTOR3 pos);			//���W�A�N�Z�T�[
	void SetPosition(float x,float y,float z);
	D3DXVECTOR3 GetPosition(void){return m_pos;};

	void SetRotation(D3DXVECTOR3 rot);			//�p�x�A�N�Z�T�[
	void SetRotation(float x,float y,float z);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

private:

	LPDIRECT3DTEXTURE9		g_pD3DTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	g_pD3DVtxBuff;		//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	g_pIndexBuff;		//�C���f�b�N�X�o�b�t�@
	int g_VtxIdxNum;							//���_�̑��C���f�b�N�X��
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ۑ��|�C���^

	D3DXMATRIX g_mtxWorld;						//���[���h�}�g���b�N�X

	int g_NumBlockX,g_NumBlockZ;				//�u���b�N��
	int g_NumVtx;								//�����_��
	int g_NumPolygon;							//���|���S����
	float g_SizeBlockX,g_SizeBlockZ;			//�u���b�N�T�C�Y
	
	D3DXVECTOR3			m_pos;					//�V�����_�[�̈ʒu
	D3DXVECTOR3			m_rot;					//�V�����_�[�̉�]
	D3DXVECTOR3			m_scl;					//�ǂ̊g��k��

	float m_cylindersizeX;						//�V�����_�[�̑傫��
	float m_cylindersizeY;
	float m_circumference;						//�V�����_�[�̉~��
	float m_radius;								//�V�����_�[�̔��a

	D3DXVECTOR3* m_normalBuf;					//�@���o�b�t�@
};

#endif