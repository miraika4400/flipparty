//=============================================================================
//
// mini_result�w�b�_ [mini_result.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _MINI_RESULT_H_
#define _MINI_RESULT_H_

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

//�^�C�g���N���X
class CMiniResult : public CScene
{
public:
	//============
	// �����o�֐�
	//============
	CMiniResult();
	~CMiniResult();

	static CMiniResult *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:

};

#endif