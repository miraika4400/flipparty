//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************

// サウンドクラス
class CSound
{
public:
	//============
	// 状態列挙
	//============
	typedef enum
	{
		LABEL_BGM_TITLE = 0,        // タイトルBGM
		LABEL_BGM_TUTORIAL,         // チュートリアル
		LABEL_BGM_FLAG_GAME,        // 旗揚げゲームのBGM
		LABEL_BGM_FLY_GAME,         // 連打ゲームのBGM
		LABEL_BGM_REMEMBER_GAME,    // 記憶ゲームのBGM
		LABEL_BGM_MINIRESULT,       // ミニリザルトのBGM
		LABEL_BGM_RESULT,           // リザルトのBGM
		LABEL_SE_ENTER,             // エンター音
		LABEL_SE_CURSOR,            // カーソル音
        LABEL_SE_OK,                // 記憶ゲーム正解の音
        LABEL_SE_MISS,              // 記憶ゲーム不正解の音
		LABEL_SE_MISS2,             // ぶぶー
		LABEL_SE_MISS3,             // ぶぶー
		LABEL_SE_MISS4,             // ぶぶー
		LABEL_SE_WARNING,           // 警告音
		LABEL_SE_FLIPPER_LEFT1,     // フリッパー左
		LABEL_SE_FLIPPER_LEFT2,     // フリッパー左
		LABEL_SE_FLIPPER_LEFT3,     // フリッパー左
		LABEL_SE_FLIPPER_LEFT4,     // フリッパー左
		LABEL_SE_FLIPPER_RIGHT1,    // フリッパー右
		LABEL_SE_FLIPPER_RIGHT2,    // フリッパー右
		LABEL_SE_FLIPPER_RIGHT3,    // フリッパー右
		LABEL_SE_FLIPPER_RIGHT4,    // フリッパー右
		LABEL_SE_STAN1,             // stan
		LABEL_SE_STAN2,             // stan
		LABEL_SE_STAN3,             // stan
		LABEL_SE_STAN4,             // stan
		LABEL_SE_COUNT,				// カウント音
		LABEL_SE_START,				// ゲーム開始音
		LABEL_SE_GAME_END,			// ゲーム終了音
		LABEL_SE_RESULT_WIN,		// 位置発表時SE
		LABEL_SE_PASSING_PENGUIN,	// 通過ペンギンの足音
		SOUND_LABEL_MAX,            // サウンド最大数
	}LABEL;

	//============
	// メンバ関数
	//============
	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);   // 初期化
	void Uninit(void);         // 終了
	HRESULT Play(LABEL label); // 再生
	void Stop(LABEL label);    // 停止
	void Stop(void);           // 再生中の音のすべて停止
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//============
	// 構造体定義
	//============
	// パラメータ
	typedef struct
	{
		char *pFilename; // ファイル名
		int nCntLoop;    // ループカウント
	} SOUNDPARAM;

	//============
	// メンバ変数
	//============
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];             // パラメータ

	IXAudio2 *m_pXAudio2;                                    // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;              // マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];   // ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];                    // オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];                     // オーディオデータサイズ
};
#endif