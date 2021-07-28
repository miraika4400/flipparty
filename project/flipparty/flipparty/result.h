//=============================================================================
//
// result�w�b�_ [result.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"
#include "rule_base.h"

//=============================
// �O���錾
//=============================
class CPolygon;
class CPlayer;

//*****************************
//�N���X��`
//*****************************

//���U���g�N���X
class CResult : public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CResult();
	~CResult();

	static CResult *Create(void); //�N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	//============
	// �����o�ϐ�
	//============
	CPolygon *m_pPolygon;                // �|���S��
	CPlayer * m_apPlayer[MAX_PLAYER_NUM]; // �v���C���[�|�C���^
	int m_nCntFallTime;                  // �v���C���[��������^�C�~���O�̃J�E���g�p
};

#endif