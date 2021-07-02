//=============================================================================
//
// �L���Q�[���̃v���C���[�w�b�_ [player_remember.h]
// Author : AYANO KUDO
//
//=============================================================================
//��d�C���N���[�h�h�~
#ifndef _PLAYER_REMEMBER_H_
#define _PLAYER_REMEMBER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "player.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayerRemember : public CPlayer
{
public:
    // �����o�֐�
    CPlayerRemember();
    ~CPlayerRemember();

    static CPlayerRemember* Create(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    bool IsLoss;        // �E���������ǂ���
};


#endif _PLAYER_REMEMBER_H_