////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "rank_ui.h"
#include "billboard.h"
#include "resource_texture.h"

//=============================
// �}�N����`
//=============================
#define UI_SIZE D3DXVECTOR3(40.0f,40.0f,0.0f)
#define MAX_ANIMATION_X 4      // �A�j���[�V������ ��
#define MAX_ANIMATION_Y 4      // �A�j���[�V������ �c
#define ANIMARION_INTERVAL 5   // �A�j���[�V�����ڍs�t���[����

//=============================
// �ÓI�����o�ϐ��錾
//=============================

//=============================
// �R���X�g���N�^
//=============================
CRankUI::CRankUI()
{
	// �ϐ��̃N���A
	m_pBillboard = NULL;  // �r���{�[�h�|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// ���W
	m_nRank = 0;          // ����
	m_nCntAnim = 0;       // �A�j���[�V�����J�E���g
	m_nAnimX = 0;         // �A�j���[�V����X��
}

//=============================
// �f�X�g���N�^
//=============================
CRankUI::~CRankUI()
{
}

//=============================
// �N���G�C�g
//=============================
CRankUI * CRankUI::Create(D3DXVECTOR3 pos, int nRank)
{
	// �������̊m��
	CRankUI *pRankUi = new CRankUI;

	// �����̑��
	pRankUi->m_pos = pos; 
	pRankUi->m_nRank = nRank;

	// ������
	pRankUi->Init();

	return pRankUi;
}

//=============================
// ����������
//=============================
HRESULT CRankUI::Init(void)
{
	m_pBillboard = CBillboard::Create(m_pos, UI_SIZE);
	m_nCntAnim = 0;       // �A�j���[�V�����J�E���g
	m_nAnimX = 0;         // �A�j���[�V����X��

	// �e�N�X�`���̐ݒ�
	m_pBillboard->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_UI_RANK));
	
	// UV���W�̐ݒ�
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / MAX_ANIMATION_X;
	float fv = 1.0f / MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nRank);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nRank + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank + fv);

	// UV���W�Z�b�g
	m_pBillboard->SetTextureUV(uv);

	return S_OK;
}

//=============================
// �I������
//=============================
void CRankUI::Uninit(void)
{
	if (m_pBillboard != NULL)
	{
		m_pBillboard->Uninit();
		delete m_pBillboard;
		m_pBillboard = NULL;
	}

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CRankUI::Update(void)
{
	m_nCntAnim++;

	if ((ANIMARION_INTERVAL %m_nCntAnim) == 0)
	{
		m_nAnimX++;
		if (m_nAnimX >= MAX_ANIMATION_X)
		{
			m_nAnimX = 0;
		}

		// UV���W�̐ݒ�
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / MAX_ANIMATION_X;
		float fv = 1.0f / MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nRank);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nRank + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nRank + fv);

		// UV���W�Z�b�g
		m_pBillboard->SetTextureUV(uv);
	}
}

//=============================
// �`�揈��
//=============================
void CRankUI::Draw(void)
{
	if (m_pBillboard!=NULL)
	{
		m_pBillboard->Draw();
	}
}
