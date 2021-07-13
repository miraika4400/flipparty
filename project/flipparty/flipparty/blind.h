//=============================================================================
//
// blind�w�b�_ [blind.h]
// Author : �R�c �ˑ�
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _BLIND_H_
#define _BLIND_H_

//*****************************
//�C���N���[�h
//*****************************
#include "scene3d.h"

//*****************************
//�N���X��`
//*****************************

//�u���C���h�N���X
class CBlind : public CScene3d
{
public:
	CBlind();
	~CBlind();

	static CBlind *Create(int nTime);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime) { m_nTime = nTime; }
private:
	int m_nTime;	//�^�C�}�[
	bool m_bMoving;	//�ړ��\���ǂ���
};

#endif