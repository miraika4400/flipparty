////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "warning.h"
#include "billboard.h"
#include "resource_texture.h"
#include "rule_flygame.h"
#include "player_flygame.h"
#include "cloud.h"

//=============================
// �}�N����`
//=============================
#define UI_SIZE D3DXVECTOR3(15.0f,15.0f,0.0f)    // UI�T�C�Y
#define UI_POS_Y 105                             // �v���C���[����ǂꂭ�炢�����ʒu��
#define UI_POS_Z 5                               // �v���C���[����ǂꂭ�炢��O��
#define COLOR D3DXCOLOR(1.0f,1.0f,1.0f,m_fAlpha) // �F
#define CLOUD_COUNT 60                           // �_�����J�E���g
#define LIFE CLOUD_COUNT + 60                    // ����

//=============================
// �ÓI�����o�ϐ��錾
//=============================

//=============================
// �R���X�g���N�^
//=============================
CWarningUI::CWarningUI() :CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	m_pBillboard = NULL;  // �r���{�[�h�|�C���^
	m_nCloudCount = 0;
	m_fAlpha = 0.0f;
}

//=============================
// �f�X�g���N�^
//=============================
CWarningUI::~CWarningUI()
{
}

//=============================
// �N���G�C�g
//=============================
CWarningUI * CWarningUI::Create(int nPlayerNum)
{
	// �������̊m��
	CWarningUI *pWarningUi = new CWarningUI;

	// �����̑��
	pWarningUi->m_nPlayerNum = nPlayerNum;

	// ������
	pWarningUi->Init();

	return pWarningUi;
}

//=============================
// ����������
//=============================
HRESULT CWarningUI::Init(void)
{
	// �r���{�[�h�N���X�̐���
	m_pBillboard = CBillboard::Create(ReturnUIPosition(), UI_SIZE);

	// �e�N�X�`���̐ݒ�
	m_pBillboard->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TESTURE_WARNING));

	// �J�E���g�̏�����
	m_nCloudCount = 0;
	
	// �A���t�@�l�̏�����
	m_fAlpha = 0.0f;

	// �F�̐ݒ�
	m_pBillboard->SetColor(COLOR);
	return S_OK;
}

//=============================
// �I������
//=============================
void CWarningUI::Uninit(void)
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
void CWarningUI::Update(void)
{
	m_nCloudCount++;

	if (m_nCloudCount < CLOUD_COUNT)
	{
		m_fAlpha = (float)((m_nCloudCount) % (CLOUD_COUNT / 2)) / (float)(CLOUD_COUNT / 2);
	}
	else if (m_nCloudCount >= LIFE)
	{
		Uninit();
		return;
	}
	else if (m_nCloudCount == CLOUD_COUNT)
	{
		m_fAlpha = 1.0f;
		CCloud::Create(m_nPlayerNum);
	}



	if (m_pBillboard != NULL)
	{
		// UI�̈ʒu����
		m_pBillboard->SetPos(ReturnUIPosition());
		m_pBillboard->SetColor(COLOR);
	}
}

//=============================
// �`�揈��
//=============================
void CWarningUI::Draw(void)
{
	if (m_pBillboard != NULL)
	{
		m_pBillboard->Draw();
	}
}

//=============================
// UI�̈ʒu��Ԃ�
//=============================
D3DXVECTOR3 CWarningUI::ReturnUIPosition(void)
{
	D3DXVECTOR3 OutPos = CRuleFly::GetPlayer(m_nPlayerNum)->GetPos();

	OutPos.y += UI_POS_Y;
	OutPos.z += UI_POS_Z;

	return OutPos;
}
