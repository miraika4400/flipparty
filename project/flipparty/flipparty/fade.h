//=============================================================================
//
// fade�w�b�_ [fade.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _FADE_H_
#define _FADE_H_
//***********************************
//�C���N���[�h
//***********************************
#include "main.h"
#include "manager.h"

//***********************************
// �O���錾
//***********************************
class CPolygon;

//=============================
//�N���X��`
//=============================

//�t�F�[�h�N���X
class CFade
{
public:
	//============
	// �񋓒�`
	//============
	// �t�F�[�h���
	typedef enum
	{
		FADE_NONE = 0, // ���ł��Ȃ����
		FADE_IN,       // �t�F�[�h�C��
		FADE_OUT,      // �t�F�[�h�A�E�g
		FADE_MAX,      // ��Ԃ̍ő吔
	}FADE;

	//============
	// �����o�֐�
	//============
	CFade();
	~CFade();

	static CFade*Create(void); //�N���X����

	HRESULT Init(void);                // ������
	void Uninit(void);                 // �I��
	void Update(void);                 // �X�V
	void Draw(void);                   // �`��
	void SetFade(CManager::MODE mode); // �t�F�[�h�̃Z�b�g
private:
	//============
	// �����o�ϐ�
	//============
	CPolygon*      m_pPolygon;  // �t�F�[�h�|���S��
	D3DXCOLOR      m_col;       // �J���[
	CManager::MODE m_modeNext;  // �l�N�X�g���[�h
	FADE           m_fade;      // �t�F�[�h���
};

#endif