//=============================================================================
//
// blind�w�b�_ [blind.h]
// Author : ���V ����
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

//2d�|���S���N���X
class CBlind : public CScene3d
{
public:
	CBlind();
	~CBlind();

	static CBlind *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};

#endif