//=============================================================================
//
// add_point_display�w�b�_ [add_point_display.h]
// Author : �R�c�@�ˑ�
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ADD_POINT_DISPLAY_H_
#define _ADD_POINT_DISPLAY_H_

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "scene.h"
#include "scene2d.h"

//=============================================================================
//�N���X��`
//=============================================================================
class CAddPointDisplay :public CScene2d
{
public:
	//=========================================================================
	//�\������e�N�X�`���̎�ނ̗�
	//=========================================================================
	typedef enum
	{
		POINT_DISPLAY_TYPE_3PT = 0,
		POINT_DISPLAY_TYPE_2PT,
		POINT_DISPLAY_TYPE_1PT,
		POINT_DISPLAY_TYPE_0PT,
		POINT_DISPLAY_TYPE_MISS,
		POINT_DISPLAY_TYPE_MAX
	}POINT_DISPLAY_TYPE;

	CAddPointDisplay();
	~CAddPointDisplay();

	static CAddPointDisplay *Create(int nPlayerNumber);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDisplay(POINT_DISPLAY_TYPE displayType);
private:
	POINT_DISPLAY_TYPE m_displayType;	//�\������e�N�X�`���̃^�C�v
	int m_nPlayerNumber;				//�v���C���[�ԍ�
	bool m_IsDraw;						//�`�悷�邩�ǂ���
	int m_nShoeCounter;					//�`�悷�鎞�Ԃ̃J�E���^�[
};
#endif // !_ADD_POINT_DISPLAY_H_
