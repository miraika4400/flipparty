//=============================================================================
//
// textureヘッダ [texture.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//クラス定義
//*****************************

//テクスチャクラス
class CResourceTexture
{
public:
	// 列挙
	// テクスチャ種類
	typedef enum
	{
		TEXTURE_TITLE = 0,       // タイトル
		TEXTURE_TUTORIAL,        // チュートリアル
		TEXTURE_PARTICLE_BOX,    // パーティクル*箱
		TEXTURE_PARTICLE_STAR,   // パーティクル*星
		TEXTURE_PARTICLE_CIRCLE, // パーティクル*円
		TEXTURE_NUMBER,          // ナンバー
		TEXTURE_LEFT,            // 左矢印
		TEXTURE_RIGHT,           // 右矢印
		TEXTURE_UP,              // 上矢印
		TEXTURE_DOWN,            // 下矢印
		TEXTURE_ICON_1P,         // 1pアイコン
		TEXTURE_ICON_2P,         // 2pアイコン
		TEXTURE_ICON_3P,         // 3pアイコン
		TEXTURE_ICON_4P,         // 4pアイコン
		TEXTURE_COUNT_SELECT_2,  // 人数選択UI2人
		TEXTURE_COUNT_SELECT_3,  // 人数選択UI3人
		TEXTURE_COUNT_SELECT_4,  // 人数選択UI4人
		TEXTURE_TOONSHADOW,      // トゥーンシャドウ
		TEXTURE_TOONSHADOW_CLOUD,// トゥーンシャドウ*雲
        TEXTURE_UI_UP,           // UI「あげて」
        TEXTURE_UI_DOWN,         // UI「さげて」
        TEXTURE_UI_MARU,         // UI「〇」
        TEXTURE_UI_BATU,         // UI「×」
        TEXTURE_UI_000,          // UI プレイヤー番号（記憶ゲームで使用）
        TEXTURE_UI_001,          // UI「のばんです」（記憶ゲームで使用）
		TEXTURE_UI_RANK,         // UI「順位」
		TEXTURE_THUNDER_EFFECT,  // 雷エフェクト
		TEXTURE_MAX        // テクスチャ数
	}TEXTURE_TYPE;
	
	// メンバ関数
	static CResourceTexture * Create(void);                          // クラス生成
	static void Release(void);                               // クラス破棄
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE type); // テクスチャの取得処理*引数：取得したいテクスチャ
	
private:
	CResourceTexture();//隠しコンストラクタ
public:
	~CResourceTexture();

private:
	void Load(void); // テクスチャ読み込み
	void Unload(void); // テクスチャ破棄

	// メンバ変数
	static const std::string m_aTexPath[TEXTURE_MAX]; // テクスチャのパス
	static CResourceTexture *m_pSingleTex;                    // テクスチャクラスのポインタ*シングルトン用
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_MAX];      // テクスチャのポインタ
};

#endif