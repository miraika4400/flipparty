////////////////////////////////////////////////////
//
//    scene3d�N���X�̏���[scene3d.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "object3d_shader.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "camera_base.h"

//******************************
// �}�N����`
//******************************
#define POLYGON_SIZE 200 // �|���S���̏����T�C�Y
#define FVF_SHADER (D3DFVF_XYZ|D3DFVF_NORMAL |D3DFVF_DIFFUSE|D3DFVF_TEX1)

//===================================
// �R���X�g���N�^
//===================================
CObject3dShader::CObject3dShader(int nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pDecl = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_mtxWorld = {};
	m_pldxBuff = NULL;
	m_bAddMode = false;

	memset(&m_shader, 0, sizeof(m_shader)); // �V�F�[�_�[
}

//===================================
// �f�X�g���N�^
//===================================
CObject3dShader::~CObject3dShader()
{
}

//===================================
// �N���G�C�g�֐�
//===================================
CObject3dShader * CObject3dShader::Create(void)
{
	// �������̊m��
	CObject3dShader *p3dShader;
	p3dShader = new CObject3dShader;
	// ������
	p3dShader->Init();

	return p3dShader;
}

//===================================
// ����������
//===================================
HRESULT CObject3dShader::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�錾
	D3DVERTEXELEMENT9 vertexElements[] = {
		{ 0          ,0          ,D3DDECLTYPE_FLOAT3 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_POSITION ,0 },    // ���W
		{ 0          ,12         ,D3DDECLTYPE_FLOAT3 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_NORMAL   ,0 },    // �@��
		{ 0          ,24         ,D3DDECLTYPE_FLOAT2 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_TEXCOORD ,0 },    // �e�N�X�`��UV
		{ 0          ,32         ,D3DDECLTYPE_FLOAT3 ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_TANGENT  ,0 },    // �ڐ�
		{ 0          ,44         ,D3DDECLTYPE_D3DCOLOR ,D3DDECLMETHOD_DEFAULT ,D3DDECLUSAGE_COLOR    ,0 },  // �J���[
		{ 0xFF       ,0          ,D3DDECLTYPE_UNUSED ,0                     ,0                     ,0 } };

	pDevice->CreateVertexDeclaration(vertexElements, &m_pDecl);

	VERTEX_3D_SHADER *pVtx;// ���_���|�C���^

						   // ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_SHADER)*NUM_VERTEX, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVtxBuff, NULL);

	// �����o�ϐ��̏�����
	m_size = { POLYGON_SIZE, 1.0f, POLYGON_SIZE };
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(+1.0f, +1.0f, -1.0f);
	pVtx[1].pos = D3DXVECTOR3(-1.0f, +1.0f, -1.0f);
	pVtx[2].pos = D3DXVECTOR3(+1.0f, -1.0f, +1.0f);
	pVtx[3].pos = D3DXVECTOR3(-1.0f, -1.0f, +1.0f);

	// �e�N�X�`��UV���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		// �F�̐ݒ�
		pVtx[nCnt].col = m_col;
		// �@��
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// �ڐ�
		pVtx[nCnt].tangent = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}

	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===================================
// �I������
//===================================
void CObject3dShader::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//===================================
// �X�V����
//===================================
void CObject3dShader::Update(void)
{
}

//===================================
// �`�揈��
//===================================
void CObject3dShader::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_shader.pEffect != NULL)
	{// �V�F�[�_�[��NULL����Ȃ��Ƃ�

	 // �V�F�[�_�[�����v�Z�����邽�߃��C�g������
		pDevice->SetRenderState(D3DRS_LIGHTING, false);

		D3DXMATRIX mtxRot, mtxTrans, mtxScail; // �s��v�Z�p�}�g���N�X

											   // ���Z���[�h�̎�
		if (m_bAddMode)
		{
			// ���Z����
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// �}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);
		D3DXMatrixIdentity(&mtxRot);
		D3DXMatrixIdentity(&mtxTrans);
		D3DXMatrixIdentity(&mtxScail);

		// �T�C�Y
		D3DXMatrixScaling(&mtxScail, m_size.x, m_size.y, m_size.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D_SHADER));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_SHADER);

		pDevice->SetTexture(0, m_pTexture);

		pDevice->SetVertexDeclaration(m_pDecl);

		// �e�N�j�b�N
		m_shader.pEffect->SetTechnique(m_shader.achTechniqueName);

		// �p�X���̎擾
		UINT numPass = 0;
		m_shader.pEffect->Begin(&numPass, 0);

		// �V�F�[�_�ɏ��
		D3DXMATRIX mat, viewMtx;
		D3DXMatrixIdentity(&mat);
		mat = m_mtxWorld * (*CManager::GetCamera()->GetViewMtx())* (*CManager::GetCamera()->GetProjectionMtx());
		m_shader.pEffect->SetMatrix("WorldViewProj", &mat); // �v���W�F�N�V����
		m_shader.pEffect->SetMatrix("World", &m_mtxWorld);  // ���[���h
		m_shader.pEffect->SetFloatArray("LightDirection", (float*)&D3DXVECTOR3(0.01f, 1.0f, 0.0f), 3);// ���C�g�f�B���N�V����
		m_shader.pEffect->SetFloatArray("DiffuseColor", (float*)&D3DXVECTOR4(1, 1, 1, 1), 4); // ���ˌ�

																							  // �p�X�����`�揈���̃��[�v
		for (int nCntEffect = 0; nCntEffect < (int)numPass; nCntEffect++)
		{
			// �V�F�[�_�[�ɏ��𑗂�
			SetShaderValue();

			// �V�F�[�_�p�X�̕`��J�n
			m_shader.pEffect->BeginPass(nCntEffect);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// �V�F�[�_�p�X�̏I��
			m_shader.pEffect->EndPass();
		}

		// �V�F�[�_�̏I��
		m_shader.pEffect->End();

		// ���Z���[�h�̎�
		if (m_bAddMode)
		{
			// �ʏ퍇���ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		// �e�N�X�`���̏�����
		pDevice->SetTexture(0, 0);
		// ���C�g������
		pDevice->SetRenderState(D3DRS_LIGHTING, true);

		pDevice->SetVertexDeclaration(NULL);
	}
}

//===================================
// ���W�̃Z�b�g
//===================================
void CObject3dShader::SetPos(const D3DXVECTOR3 pos)
{
	//pos�̑��
	m_pos = pos;
}

//===================================
// �A�j���[�V�������̃Z�b�g
//===================================
void CObject3dShader::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
{
	VERTEX_3D_SHADER *pVtx;// ���_���|�C���^

						   // ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = uv[0];
	pVtx[1].tex = uv[1];
	pVtx[2].tex = uv[2];
	pVtx[3].tex = uv[3];

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

//===================================
// �T�C�Y�̃Z�b�g
//===================================
void CObject3dShader::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// ���_���W�̍Đݒ�
	SetPos(m_pos);
}

//===================================
// �F�̃Z�b�g
//===================================
void CObject3dShader::SetColor(const D3DXCOLOR col)
{
	VERTEX_3D_SHADER *pVtx;// ���_���|�C���^

	m_col = col;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

//===================================
// HLSL�ɒl�𑗂�
//===================================
void CObject3dShader::SetShaderValue(void)
{

}