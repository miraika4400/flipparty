//=============================================================================
//
// particle�w�b�_ [particle.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "billboard.h"

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CParticle : public CBillboard
{
public:
	//============
	// ��ԗ�
	//============
	// �p�[�e�B�N���^�C�v
	typedef enum
	{
		PARTICLE_BOX = 0, // �l�p
		PARTICLE_TEARS,   // ��
		PARTICLE_CIRCLE,  // ��
		PARTICLE_MAX,     // �^�C�v�̍ő吔
	}PARTICLE_TYPE;

	//============
	//�����o�֐�
	//============
	CParticle();
	~CParticle();

	// static
	static CParticle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 size, const int nLife,
		const D3DCOLOR col, const PARTICLE_TYPE type = PARTICLE_BOX); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	// �ړ��ʂ̎擾�E�Z�b�g
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	//============
	// �����o�ϐ�
	//============
	LPDIRECT3DTEXTURE9 m_apTexture[PARTICLE_MAX]; // �e�N�X�`��
	D3DXVECTOR3   m_move;  // �ړ���
	int           m_nLife; // ����
	PARTICLE_TYPE m_type;  // �p�[�e�B�N���̎��
};

#endif