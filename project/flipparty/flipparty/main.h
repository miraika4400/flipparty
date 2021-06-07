//=============================================================================
//
// ���C���w�b�_ [main.h]
// Author : ���V ����
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �G���[����
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800	// �x���Ώ��p("dinput.h"�̒��O�ɒ�`)

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <WinSock2.h>
#include <windows.h>
#include "d3dx9.h"
#include <dinput.h>
#include <xaudio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "ws2_32.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WINDOW_CLASS_NAME "AppClass" // �E�C���h�E�̃N���X��
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define SCREEN_WIDTH 1280  // ��ʃT�C�Y ��
#define SCREEN_HEIGHT 720  // ��ʃT�C�Y �c
#define NUM_POLYGON 2      // ��`��̃|���S����
#define NUM_VERTEX 4       // ��`��̒��_��
#define VEC3_ZERO D3DXVECTOR3(0.0f,0.0f,0.0f) //0�x�N�g��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DVECTOR pos;   // �ʒu
	float rhw;       // rhw
	D3DCOLOR col;    // �F
	D3DXVECTOR2 tex; // �e�N�X�`����UV���W
}VERTEX_2D;

// �|���S���̒��_���
typedef struct
{
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;    //�F
	D3DXVECTOR2 tex; //�e�N�X�`����UV���W
}VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#ifdef _DEBUG
int GetFps(void);
#endif

#endif