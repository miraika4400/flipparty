////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "rule_manager.h"
#include "polygon.h"
#include "rule_base.h"
#include "rule_flygame.h"
#include "remember_rule.h"

//=============================
// �}�N����`
//=============================
#define FADE_RATE 0.1f  // �t�F�[�h���[�g

//=============================
// �ÓI�����o�ϐ��錾
//=============================

//=============================
// �R���X�g���N�^
//=============================
CRuleManager::CRuleManager() : CScene(OBJTYPE_SYSTEM)
{
	// �ϐ��̃N���A
	m_pGameRule    = NULL;                       // ���[��
	m_pFadePolygon = NULL;                       // �t�F�[�h�p�|���S��
	m_ruleNext     = RULE_FLAG_RACING;           // �l�N�X�g���[��
	m_fadeState    = FADE_NONE;                  // �t�F�[�h���
	m_polygonCol   = { 1.0f, 1.0f, 1.0f, 1.0f};  // �J���[
}

//=============================
// �f�X�g���N�^
//=============================
CRuleManager::~CRuleManager()
{
}

//=============================
// �N���G�C�g
//=============================
CRuleManager * CRuleManager::Create(void)
{
	// �������̊m��
	CRuleManager *pRuleManager = new CRuleManager;
	// ������
	pRuleManager->Init();
	return pRuleManager;
}

//=============================
// ����������
//=============================
HRESULT CRuleManager::Init(void)
{
	// ���[���N���X�̏�����
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		delete m_pGameRule;
		m_pGameRule = NULL;
	}

	// ���[���N���X�̐���
	if (m_pGameRule == NULL)
	{
		m_pGameRule = CRuleFly::Create();
	}

	// �|���S���̐���
	m_pFadePolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), // ���W�@
		                              D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), // �T�C�Y
		                              m_polygonCol);                                          // �F

	return S_OK;
}

//=============================
// �I������
//=============================
void CRuleManager::Uninit(void)
{
	// ���[���N���X�̔j��
	if (m_pGameRule != NULL)
	{
		m_pGameRule->Uninit();
		delete m_pGameRule;
		m_pGameRule = NULL;
	}

	// �|���S���̔j��
	if (m_pFadePolygon != NULL)
	{
		m_pFadePolygon->Uninit();
		delete m_pFadePolygon;
		m_pFadePolygon = NULL;
	}

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CRuleManager::Update(void)
{
	if (m_fadeState == FADE_NONE)
	{
		// ���[���N���X�̍X�V����
		if (m_pGameRule != NULL)
		{
			m_pGameRule->Update();
		}
	}
	else
	{
		//�t�F�[�h�C��
		if (m_fadeState == FADE_IN)
		{
			m_polygonCol.a -= FADE_RATE;

			if (m_polygonCol.a <= 0.0f)
			{
				m_polygonCol.a = 0.0f;
				m_fadeState = FADE_NONE;
			}
		}

		//�t�F�[�h�A�E�g
		else if (m_fadeState == FADE_OUT)
		{
			m_polygonCol.a += FADE_RATE;
			if (m_polygonCol.a >= 1.0f)
			{
				m_polygonCol.a = 1.0f;
				m_fadeState = FADE_IN;

				// ���[���N���X�̏�����
				if (m_pGameRule != NULL)
				{
					m_pGameRule->Uninit();
					delete m_pGameRule;
					m_pGameRule = NULL;
				}

				// ���[���̐���
				switch (m_ruleNext)
				{
				case RULE_FLAG_RACING: 
					// ���g��
					//m_pGameRule = CRuleFly::Create();
					break;
				case RULE_FLY:
					// �t���C
					m_pGameRule = CRuleFly::Create();
					break;
				case RULE_REMENBER:
					// �L��
					m_pGameRule = CRememjber_rule::Create();
					break;
				default:
					break;
				}
				
			}
		}

		// �J���[�̃Z�b�g
		m_pFadePolygon->SetColor(m_polygonCol);
	}
	
}

//=============================
// �`�揈��
//=============================
void CRuleManager::Draw(void)
{
	m_pFadePolygon->Draw();
}

//=============================
//���[���̃Z�b�g����
//=============================
void CRuleManager::SetRule(RULE_TYPE ruleNext)
{
	m_fadeState = FADE_OUT;
	m_ruleNext = ruleNext;
}
