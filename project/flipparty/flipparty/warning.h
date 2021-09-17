//=============================================================================
//
// warning�w�b�_ [warning.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _WARNING_H_
#define _WARNING_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CBillboard;

//*****************************
//�}�N����`
//*****************************

//*****************************
//�N���X��`
//*****************************

//�x���N���X
class CWarningUI : public CScene
{
public:
	//*****************************
	// �񋓒�`
	//*****************************

	//*****************************
	// �����o�֐�
	//*****************************
	CWarningUI();
	~CWarningUI();

	static CWarningUI *Create(int nPlayerNum); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	D3DXVECTOR3 ReturnUIPosition(void);

	//*****************************
	// �����o�ϐ�
	//*****************************
	CBillboard * m_pBillboard; // �r���{�[�h
	int m_nPlayerNum;          // �v���C���[�ԍ�
	float m_fAlpha;            // �A���t�@�l
	int m_nCloudCount;         // �_�����J�E���g
};

#endif