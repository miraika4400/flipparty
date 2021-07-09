////////////////////////////////////////////////////
//
//    ���N���X�̏���[thunder.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//**********************************
// �C���N���[�h
//**********************************
#include "thunder.h"
#include "resource_texture.h"
#include "manager.h"
#include "renderer.h"
#include "rule_flygame.h"
#include "player_flygame.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define MAX_ANIMATION_X 3     // �A�j���[�V������ ��
#define MAX_ANIMATION_Y 4     // �A�j���[�V������ �c
#define ANIMATION_INTERVAL 6  // �A�j���[�V�����ڍs�t���[����
#define SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)

//=============================
// �R���X�g���N�^
//=============================
CThunder::CThunder() :CScene3d(OBJTYPE_PARTICLE)
{
	m_nCntAnim = 0;       // �A�j���[�V�����J�E���g
	m_nAnimX = 0;         // �A�j���[�V����X��
	m_nAnimY = 0;         // �A�j���[�V����Y��
	m_nPlayerNum = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CThunder::~CThunder()
{
}

//=============================
// �N���G�C�g
//=============================
CThunder * CThunder::Create(D3DXVECTOR3 pos , int nPlayerNum)
{
	// �������̊m��
	CThunder *pThunder = new CThunder;
	// ������
	pThunder->Init();

	// �ʒu�̔��f
	pThunder->SetPos(pos);
	// �v���C���[�ԍ�
	pThunder->m_nPlayerNum = nPlayerNum;
	return pThunder;
}

//=============================
// ����������
//=============================
HRESULT CThunder::Init(void)
{
	// ������
	CScene3d::Init();

	// �T�C�Y�̐ݒ�
	SetSize(SIZE);

	// �A�j���[�V�����ϐ��̏�����
	m_nCntAnim = 0;       // �A�j���[�V�����J�E���g
	m_nAnimX = 0;         // �A�j���[�V����X��
	m_nAnimY = 0;         // �A�j���[�V����Y��

	// �e�N�X�`����
	BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_THUNDER_EFFECT));

	// UV���W�̐ݒ�
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / MAX_ANIMATION_X;
	float fv = 1.0f / MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV���W�Z�b�g
	SetTextureUV(uv);

	return S_OK;
}

//=============================
// �I������
//=============================
void CThunder::Uninit(void)
{
	CScene3d::Uninit();
}


//=============================
// �X�V����
//=============================
void CThunder::Update(void)
{
	m_nCntAnim++;

	if (ANIMATION_INTERVAL < m_nCntAnim)
	{
		m_nCntAnim = 0;
		m_nAnimX++;
		if (m_nAnimX >= MAX_ANIMATION_X)
		{
			m_nAnimY++;
		}

		// UV���W�̐ݒ�
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / MAX_ANIMATION_X;
		float fv = 1.0f / MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV���W�Z�b�g
		SetTextureUV(uv);

		if (m_nAnimY >= MAX_ANIMATION_Y)
		{
			// �X�^����Ԃɂ���
			CRuleFly::GetPlayer(m_nPlayerNum)->SetState(CFlyGamePlayer::STATE_STAN);

			Uninit();
		}
	}
}

//=============================
// �`�揈��
//=============================
void CThunder::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	DWORD lightEnable;
	pDevice->GetRenderState(D3DRS_LIGHTING, &lightEnable);
	// ���C�g�I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	CScene3d::Draw();

	// ���C�g�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, lightEnable);
}
