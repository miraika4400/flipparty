////////////////////////////////////////////////////
//
//    �܃p�[�e�B�N���N���X�̏���[tears_paticle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "tears_particle.h"
#include "billboard.h"
#include "resource_texture.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************

//**********************************
// �}�N����`
//**********************************
#define LIFE  60                                  // ����
#define MOVE_Y_DIST -2                           // �ړ���Y���̖ڕW�l
#define MOVE_Y_RATE 0.05f                         // �ړ���Y���̌W��
#define SPEED_MIN 1                              // ���x�̍ŏ�
#define SPEED_AMPLITUDE 10                        // ���x�̐U��
#define SPEED_ADJUST 10.0f                        // �X�s�[�h�����l
#define SIZE_MIN 3                               // �T�C�Y�̍ŏ�
#define SIZE_AMPLITUDE 3                         // �T�C�Y�̐U��

#define MOVE D3DXVECTOR3(0.8f ,4.0f ,0.0f )
#define SIZE D3DXVECTOR3(5.0f ,5.0f ,0.0f )
#define SIZE_DIST D3DXVECTOR3(0.0f ,0.0f ,0.0f )
#define SIZE_RATE 0.01f
#define ALPHA_DIST 0.0f
#define ALPHA_RATE 0.02f

//=============================
// �R���X�g���N�^
//=============================
CTearsParticle::CTearsParticle():CScene(OBJTYPE_SYSTEM)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_nLife = LIFE;
	ZeroMemory(&m_apParticle, sizeof(m_apParticle));
}

//=============================
// �f�X�g���N�^
//=============================
CTearsParticle::~CTearsParticle()
{
}

//=============================
// �N���G�C�g
//=============================
CTearsParticle * CTearsParticle::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CTearsParticle *pTears = new CTearsParticle;

	//�@���W
	pTears->m_pos = pos;
	// ������
	pTears->Init();
	return pTears;
}

//=============================
// ����������
//=============================
HRESULT CTearsParticle::Init(void)
{
	// ���ł����x
	float fSpeed = (float)((rand() % SPEED_AMPLITUDE + SPEED_MIN)) / SPEED_ADJUST;

	// ��L�̏�񂩂�ړ��ʂ̐���*Y���͕ʂŗ�������
	m_move = MOVE;

	// �T�C�Y�������_���ɐݒ�
	float fSize = (float)(rand() % SIZE_AMPLITUDE + SIZE_MIN);
	D3DXVECTOR3 randSize;
	randSize.x = 4;
	randSize.y = 4;
	randSize.z = 0.0f;
	
	// ����
	m_nLife = LIFE;

	for (int nCntTears = 0; nCntTears < TEARS_NUM; nCntTears++)
	{
		// �p�[�e�B�N������
		m_apParticle[nCntTears] = CBillboard::Create(m_pos, randSize);
		// �e�N�X�`��
		m_apParticle[nCntTears]->BindTexture(CResourceTexture::GetTexture(CResourceTexture::TEXTURE_PARTICLE_TEARS));
	}
	
	return S_OK;
}

//=============================
// �I������
//=============================
void CTearsParticle::Uninit(void)
{

	for (int nCntTears = 0; nCntTears < TEARS_NUM; nCntTears++)
	{
		if (m_apParticle[nCntTears] != NULL)
		{
			// �|���S���̏I������
			m_apParticle[nCntTears]->Uninit();

			// �������̉��
			delete m_apParticle[nCntTears];
			m_apParticle[nCntTears] = NULL;
		}
	}

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CTearsParticle::Update(void)
{

	// �ړ���
	m_move.y += (MOVE_Y_DIST - m_move.y)*MOVE_Y_RATE;

	// �p�[�e�B�N���̍��W�Ɉړ��ʂ𑫂�
	D3DXVECTOR3 pos = m_apParticle[0]->GetPos();
	pos += m_move;
	m_apParticle[0]->SetPos(pos);
	// �ړ��ʂ�X���̔��]
	m_move.x *= -1;

	// �p�[�e�B�N���̍��W�Ɉړ��ʂ𑫂�
	pos = m_apParticle[1]->GetPos();
	pos += m_move;
	m_apParticle[1]->SetPos(pos);
	// X����߂�
	m_move.x *= -1;

	// �T�C�Y
	D3DXVECTOR3 size = m_apParticle[0]->GetSize();
	size += (SIZE_DIST - size)*SIZE_RATE;
	m_apParticle[0]->SetSize(size);
	m_apParticle[1]->SetSize(size);

	// �J���[
	//D3DXCOLOR col = m_apParticle[0]->GetColor();
	//col.a += (ALPHA_DIST - col.a)*ALPHA_RATE;
	//m_apParticle[0]->SetColor(col);
	//m_apParticle[1]->SetColor(col);

	// ����
	m_nLife--;
	if (m_nLife <= 0)
	{
		// ����
		Uninit();
	}
}


//=============================
// �`�揈��
//=============================
void CTearsParticle::Draw(void)
{
	for (int nCntTears = 0; nCntTears < TEARS_NUM; nCntTears++)
	{
		if (m_apParticle[nCntTears] != NULL)
		{
			// �|���S���̕`�揈��
			m_apParticle[nCntTears]->Draw();
		}
	}
}
