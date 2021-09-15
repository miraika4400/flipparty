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

	typedef enum
	{
		BLIND_STATE_MOVE = 0,
		BLIND_STATE_NORMAL,
		BLIND_STATE_MAX
	}BLIND_STATE;

	CBlind();
	~CBlind();

	static CBlind *Create(int nTime,int nStartTime);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTime(int nTime) { m_nTime = nTime; }
	BLIND_STATE GetState(void) { return m_state; }
private:
	int m_nTime;	//�^�C�}�[
	int m_nMoveStartTime;	//�ړ��J�n�^�C��
	BLIND_STATE m_state;	//�u���C���h�̏��
	CScene3d *m_pBlackPolygon;	//���|���S��
};

#endif