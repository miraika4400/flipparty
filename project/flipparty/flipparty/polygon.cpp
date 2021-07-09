//===================================================
//
//    �|���S���N���X�̏���[polygon.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
// �C���N���[�h
//**********************************
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//==================================
// �R���X�g���N�^
//==================================
CPolygon::CPolygon()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_bAddMode = false;
}

//==================================
// �f�X�g���N�^
//==================================
CPolygon::~CPolygon()
{

}

//==================================
// �N���G�C�g
//==================================
CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{
	// �������̊m��
	CPolygon *pPolygon = new CPolygon;

	// ����������
	pPolygon->Init(pos, size, col);

	return pPolygon;
}

//==================================
// ����������
//==================================
HRESULT CPolygon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{

	VERTEX_2D *pVtx;// ���_���|�C���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0);

	// �e�N�X�`��UV���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================
// �I������
//==================================
void CPolygon::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==================================
// �X�V����
//==================================
void CPolygon::Update(void)
{
}

//==================================
// �`�揈��
//==================================
void CPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
	}

	// ���Z���[�h�̎�
	if (m_bAddMode)
	{
		// ���Z����
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���Z���[�h�̎�
	if (m_bAddMode)
	{
		// �ʏ퍇���ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	pDevice->SetTexture(0, 0);
}

void CPolygon::SetVertexPos(D3DXVECTOR3 pos[NUM_VERTEX])
{
	VERTEX_2D *pVtx;// ���_���|�C���^

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].pos = pos[0];
	pVtx[1].pos = pos[1];
	pVtx[2].pos = pos[2];
	pVtx[3].pos = pos[3];

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

void CPolygon::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// ���_���|�C���^

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

//===================================
// �A�j���[�V�������̃Z�b�g
//===================================
void CPolygon::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
{
    VERTEX_2D *pVtx;// ���_���|�C���^

                    // ���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].tex = uv[0];
    pVtx[1].tex = uv[1];
    pVtx[2].tex = uv[2];
    pVtx[3].tex = uv[3];

    // �A�����b�N
    m_pVtxBuff->Unlock();
}