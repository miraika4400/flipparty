//=============================================================================
//
// tears_manager�w�b�_ [tears_manager.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _TEARS_MANAGER_H_
#define _TEARS_MANAGER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
// �O���錾
//*****************************

//*****************************
//�N���X��`
//*****************************

//�܊Ǘ��N���X
class CTearsManager : public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CTearsManager();
	~CTearsManager();

	static CTearsManager *Create(D3DXVECTOR3 pos); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	//============
	// �����o�ϐ�
	//============
	D3DXVECTOR3 m_pos;
	int m_nCntTesrsInterval;  // �܂̃C���^�[�o���J�E���g
};

#endif