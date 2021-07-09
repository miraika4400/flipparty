//=============================================================================
//
// thunder�w�b�_ [thunder.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _THUNDER_H_
#define _THUNDER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene3d.h"

//=============================
// �O���錾
//=============================

//*****************************
//�N���X��`
//*****************************

// ���N���X
class CThunder : public CScene3d
{
public:
	//============
	// �����o�֐�
	//============
	CThunder();
	~CThunder();

	static CThunder *Create(D3DXVECTOR3 pos, int nPlayerNum); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:

	int m_nPlayerNum;
	int m_nCntAnim;       // �A�j���[�V�����J�E���g
	int m_nAnimX;         // �A�j���[�V����X��
	int m_nAnimY;         // �A�j���[�V����Y��
};

#endif