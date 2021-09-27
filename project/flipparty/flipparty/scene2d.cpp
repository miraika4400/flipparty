////////////////////////////////////////////////////
//
//    scene2d�N���X�̏���[scene2d.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "scene2d.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define POLYGON_SIZE 200 // �|���S���̏����T�C�Y

//===================================
// �R���X�g���N�^
//===================================
CScene2d::CScene2d(int nPriority) :CScene(nPriority)
{
	// �ϐ��̃N���A
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_fAngle = 0.0f;
	m_bAddMode = false;
}

//===================================
// �f�X�g���N�^
//===================================
CScene2d::~CScene2d()
{
}

//===================================
// �N���G�C�g�֐�
//===================================
CScene2d * CScene2d::Create(void)
{
	// �������̊m��
	CScene2d *pScene2d;
	pScene2d = new CScene2d;
	// ������
	pScene2d->Init();

	return pScene2d;
}

//===================================
// ����������
//===================================
HRESULT CScene2d::Init(void)
{
	VERTEX_2D *pVtx;// ���_���|�C���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// �����o�ϐ��̏�����
	m_size = { POLYGON_SIZE,POLYGON_SIZE,0.0f };
	m_fAngle = 0.0f;
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���S���璸�_�̋���
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// ���S����E��̒��_�̊p�x
	float fAngle = atan2f(m_size.y, m_size.x);
	// ���S���獶��̒��_�̊p�x
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), m_pos.y + (sinf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), 0);

	// �e�N�X�`��UV���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = m_col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===================================
// �I������
//===================================
void CScene2d::Uninit(void)
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
void CScene2d::Update(void)
{
}

//===================================
// �`�揈��
//===================================
void CScene2d::Draw(void)
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

//===================================
// ���W�̃Z�b�g
//===================================
void CScene2d::SetPos(const D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;// ���_���|�C���^

	//pos�̑��
	m_pos = pos;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���S���璸�_�̋���
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// ���S����E��̒��_�̊p�x
	float fAngle = atan2f(m_size.y, m_size.x);
	// ���S���獶��̒��_�̊p�x
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), m_pos.y + (sinf(fAngle + D3DXToRadian(m_fAngle))  * fDistance), 0);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

//===================================
// �A�j���[�V�������̃Z�b�g
//===================================
void CScene2d::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
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

void CScene2d::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// ���_���W�̍Đݒ�
	SetPos(m_pos);
}

void CScene2d::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// ���_���|�C���^

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
