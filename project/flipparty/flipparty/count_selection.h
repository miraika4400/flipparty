//=============================================================================
//
// count_slection�w�b�_ [count_slection.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _COUNT_SELECTION_H_
#define _COUNT_SELECTION_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CPolygon;

//*****************************
//�N���X��`
//*****************************

// �l���I���N���X
class CCountSelect : public CScene
{
public:
	//============
	// ��
	//============
	// �l���Z���N�gUI�^�C�v
	typedef enum
	{
		SELECT_2_PLAYER = 0,
		SELECT_3_PLAYER,
		SELECT_4_PLAYER,
		SELECT_COUNT_MAX
	}SELECT_UI_TYPE;

	//============
	// �����o�֐�
	//============
	CCountSelect();
	~CCountSelect();

	static CCountSelect *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	static int GetPlayerNum(void) { return m_nPlayerNum; }// �v���C���[�l���̎擾����

private:
	void SelectUi(void);      // UI�̑I������
	void ManageUiColor(void); // UI�J���[�̊Ǘ�
	
	//============
	// �����o�ϐ�
	//============
	static int m_nPlayerNum;                // �Q�[���ɎQ�����Ă���v���C���[�̐l��
	CPolygon *m_pPolygon[SELECT_COUNT_MAX]; // UI�|���S��
	int  m_nSelectUi;                       // �I��ł���UI�̃^�C�v
};

#endif#pragma once
