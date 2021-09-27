//=============================================================================
//
// stratcount�w�b�_ [stratcount.h]
// Author : �R�c�ˑ�
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _STRATCOUNT_H_
#define _STRATCOUNT_H_


//*****************************
//�C���N���[�h
//*****************************
#include "scene.h"

class CNumber;
class CScene2d;

class CStratCount :public CScene
{
public:
	CStratCount();
	~CStratCount();

	static CStratCount *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CNumber *m_pNumber;	//�i���o�[�N���X�̃|�C���^�ϐ�
	CScene2d *m_pScene2D;
	int m_nCntTime;		//�^�C���J�E���g
	int m_nLimitTime;	//��������
};
#endif 