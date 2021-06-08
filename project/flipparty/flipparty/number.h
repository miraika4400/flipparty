//=============================================================================
//
// number�w�b�_ [number.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"

//*****************************
//�N���X��`
//*****************************

//�i���o�[�N���X
class CNumber
{
public:
	//============
	// �����o�֐�
	//============

	CNumber();
	~CNumber();
	static CNumber *Create(const int nNum, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col); // �N���X����

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col); // ������
	void Uninit(void);                                                                // �I��
	void Update(void);                                                                // �X�V
	void Draw(void);                                                                  // �`��
	void SetNumber(const int nNumber);                                                // �i���o�[�̃Z�b�g

	// �J���[�̃Z�b�g�A�擾
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
private:
	//============
	// �����o�ϐ�
	//============
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C��
	int m_nNumber;                          // �i���o�[
	D3DXCOLOR m_col;                        // �F
};

#endif