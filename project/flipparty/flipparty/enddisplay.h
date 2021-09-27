//=============================================================================
//
// enddisplay�w�b�_ [enddisplay.h]
// Author : �R�c�ˑ�
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ENDDISPLAY_H_
#define _ENDDISPLAY_H_


//*****************************
//�C���N���[�h
//*****************************
#include "scene2d.h"

//=============================================================================
//�I���\��
//=============================================================================
class CEndDisplay :public CScene2d
{
public:
	CEndDisplay();
	~CEndDisplay();

	static CEndDisplay *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nCntTime;		//�^�C���J�E���g
};
#endif 