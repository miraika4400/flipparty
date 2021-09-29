//=============================================================================
//
// resultboard�w�b�_ [resultboard.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _FLAG_RAICING_GAME_POLYGON_
#define _FLAG_RAICING_GAME_POLYGON_

//*****************************
//�C���N���[�h
//*****************************
#include "scene.h"

//=============================
// �O���錾
//=============================
class CPolygon;
class CNumber;

//=============================
// �}�N����`
//=============================
#define POINT_MAX_DIGIT 2 // �X�R�A�ő包��

//=============================
//�N���X��`
//=============================

//���U���g�{�[�h�N���X
class CFlagRaicingGamePolygon :public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CFlagRaicingGamePolygon();
	~CFlagRaicingGamePolygon();

	static CFlagRaicingGamePolygon *Create(int nPlayerNum, D3DXVECTOR3 pos); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	void CreateScore(void);          // �X�R�A�|���S���̐���

	//============
	// �����o�ϐ�
	//============
	D3DXVECTOR3 m_pos;  // ���W
	int m_nPlayerNum;
	CNumber *m_apScoreNumber[POINT_MAX_DIGIT];           // �X�R�A�̐����|���S��
	CPolygon * m_pBack;                                  // �w�i
};

#endif