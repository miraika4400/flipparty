////////////////////////////////////////////////////
//
//    particle�N���X�̏���[particle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "resource_texture.h"

//*****************************
// �}�N����`
//*****************************

//******************************
// �ÓI�����o�ϐ��錾
//*****************************

//******************************
// �R���X�g���N�^
//******************************
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_type = PARTICLE_BOX;
}

//******************************
// �f�X�g���N�^
//******************************
CParticle::~CParticle()
{
}

//******************************
// �N���G�C�g
//******************************
CParticle * CParticle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife, const D3DCOLOR col,const PARTICLE_TYPE type)
{
	// �������̊m��
	CParticle *pParticle;
	pParticle = new CParticle;

	// �^�C�v�̐ݒ�
	pParticle->m_type = type;

	// ������
	pParticle->Init();

	// �e�l�̑���E�Z�b�g
	pParticle->SetPos(pos);                  // ���W
	pParticle->m_move = move;                // �ړ���
	pParticle->SetSize(size);                // �T�C�Y
	pParticle->m_nLife = nLife;              // ����
	pParticle->SetColor(col);                // �J���[
	pParticle->SetPriority(OBJTYPE_PARTICLE); // �I�u�W�F�N�g�^�C�v
	pParticle->SetAngle((float)(rand() % 360));       // ��]�p�x�������_��
	pParticle->SetAddMode(true);             // ���Z����
	return pParticle;
}

//******************************
// ����������
//******************************
HRESULT CParticle::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	m_apTexture[PARTICLE_BOX] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_BOX);
	m_apTexture[PARTICLE_STAR] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_STAR);
	m_apTexture[PARTICLE_CIRCLE] = CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_CIRCLE);
	// �e�N�X�`�����蓖��
	BindTexture(m_apTexture[m_type]);

	return S_OK;
}

//******************************
// �I������
//******************************
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
}

//******************************
// �X�V����
//******************************
void CParticle::Update(void)
{
	// �ړ�
	SetPos(GetPos() + m_move);

	// ����
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//******************************
// �`�揈��
//******************************
void CParticle::Draw(void)
{
	CBillboard::Draw();
}
