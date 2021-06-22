//=============================================================================
//
// �l���I������ [count_selection.cpp]
// Author : ���V����
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "count_selection.h"
#include "polygon.h"
#include "resource_texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"

//*****************************
// �}�N����`
//*****************************
#define UI_SPACE 250.0f                                        // UI�̊Ԋu
#define UI_HEIGHT 500.0f                                       // UI�ʒu�̉�ʏ�̍���
#define UI_SIZE D3DXVECTOR3( 100.0f, 100.0f, 0.0f)               // UI�̃T�C�Y
#define UI_COLOR_SELECT     D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f) // UI�I�����̃J���[
#define UI_COLOR_NOT_SELECT D3DXCOLOR( 0.6f, 0.6f, 0.6f, 1.0f) // UI��I�����̃J���[

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
int CCountSelect::m_nPlayerNum = 0;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCountSelect::CCountSelect() :CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	ZeroMemory(&m_pPolygon, sizeof(m_pPolygon)); // UI�|���S��
	m_nSelectUi = 0;                             // �I��ł���UI�̃^�C�v
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCountSelect::~CCountSelect()
{
}

//=============================================================================
//�N���X����
//=============================================================================
CCountSelect * CCountSelect::Create(void)
{
	// �������̊m��
	CCountSelect *pSelect;
	pSelect = new CCountSelect;

	// ������
	pSelect->Init();

	return pSelect;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CCountSelect::Init(void)
{

	SetPriority(OBJTYPE_UI);
	// �I��ł���UI�̃^�C�v�̏�����
	m_nSelectUi = 0;
	
	// UI���W
	D3DXVECTOR3 pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - UI_SPACE, UI_HEIGHT, 0.0f);
	// UI�|���S���̐���
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] == NULL)
		{
			m_pPolygon[nCntUi] = CPolygon::Create(pos, UI_SIZE);
			pos.x += UI_SPACE;
		}
	}
	// �e�N�X�`���̐ݒ�
	m_pPolygon[SELECT_2_PLAYER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COUNT_SELECT_2));
	m_pPolygon[SELECT_3_PLAYER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COUNT_SELECT_3));
	m_pPolygon[SELECT_4_PLAYER]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_COUNT_SELECT_4));

	return S_OK;
}


//=============================================================================
//�I������
//=============================================================================
void CCountSelect::Uninit(void)
{
	// UI�|���S���̔j��
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] != NULL)
		{
			m_pPolygon[nCntUi]->Uninit();
			delete m_pPolygon[nCntUi];
			m_pPolygon[nCntUi] = NULL;
		}
	}
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CCountSelect::Update(void)
{
	// �I������
	SelectUi();
	// UI�J���[�̊Ǘ�
	ManageUiColor();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CCountSelect::Draw(void)
{
	// UI�|���S���̕`��
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] != NULL)
		{
			m_pPolygon[nCntUi]->Draw();
		}
	}
}

//=============================================================================
// UI�̑I������
//=============================================================================
void CCountSelect::SelectUi(void)
{
	// �L�[�{�[�h�ɂ��I������
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RIGHT))
	{// �E
		m_nSelectUi++;
		if (m_nSelectUi >= SELECT_COUNT_MAX)
		{
			m_nSelectUi = 0;
		}
	}
	if(CManager::GetKeyboard()->GetKeyTrigger(DIK_LEFT))
	{// ��
		m_nSelectUi--;
		if (m_nSelectUi < 0)
		{
			m_nSelectUi = SELECT_COUNT_MAX - 1;
		}
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		m_nPlayerNum = m_nSelectUi + 2;
		CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	}
}

//=============================================================================
// UI�J���[�̊Ǘ�����
//=============================================================================
void CCountSelect::ManageUiColor(void)
{
	// �I�����Ă��邩���Ȃ����ŐF��ς���
	for (int nCntUi = 0; nCntUi < SELECT_COUNT_MAX; nCntUi++)
	{
		if (m_pPolygon[nCntUi] != NULL)
		{
			if (m_nSelectUi == nCntUi)
			{// �I����
				m_pPolygon[nCntUi]->SetColor(UI_COLOR_SELECT);
			}
			else
			{// ��I����
				m_pPolygon[nCntUi]->SetColor(UI_COLOR_NOT_SELECT);
			}
		}
	}
}
