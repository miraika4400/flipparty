//=============================================================================
//
// tears_particle�w�b�_ [tears_particle.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TEARS_PARTICLE_H_
#define _TEARS_PARTICLE_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CBillboard;

//=============================
// �}�N����`
//=============================
#define TEARS_NUM 2  // ��x�̐�������̗܂̗�(���E�Ɉ����������)

//*****************************
//�N���X��`
//*****************************

//�܃p�[�e�B�N���N���X
class CTearsParticle: public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CTearsParticle();
	~CTearsParticle();

	static CTearsParticle *Create(D3DXVECTOR3 pos); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	//============
	// �����o�ϐ�
	//============
	D3DXVECTOR3 m_pos;       // ���W
	D3DXVECTOR3 m_move;      // �ړ���
	int m_nLife;             // ����
	CBillboard * m_apParticle[TEARS_NUM]; // �p�[�e�B�N���N���X
};

#endif