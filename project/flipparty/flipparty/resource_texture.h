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
		TEXTURE_TUTORIAL_FLAG,   // チュートリアル(はたあげ)
        TEXTURE_TUTORIAL_FRY,    // チュートリアル(連打)
        TEXTURE_TUTORIAL_REMEMBER,// チュートリアル(記憶)
		TEXTURE_PARTICLE_BOX,    // パーティクル*箱
		TEXTURE_PARTICLE_TEARS,  // パーティクル*涙
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
		TEXTURE_TOONSHADOW_ICEBERG,// トゥーンシャドウ*氷山
        TEXTURE_UI_PLAYER_RIGHT,           // UI// UI 右手を上げたとき（記憶ゲームで使用）
        TEXTURE_UI_PLAYER_LEFT,         // UI// UI 左手を上げたとき（記憶ゲームで使用）
        TEXTURE_UI_MARU,         // UI「〇」
        TEXTURE_UI_BATU,         // UI「×」
        TEXTURE_UI_000,          // UI プレイヤー番号（記憶ゲームで使用）
        TEXTURE_UI_001,          // UI「のばんです」（記憶ゲームで使用）
		TEXTURE_UI_RANK,         // UI「順位」
		TEXTURE_BLIND,			 //ブラインド
		TEXTURE_UI_RIGHT_UP,	 // UI　右上げ
		TEXTURE_UI_RIGHT_DOWN,	 // UI　右下げ
		TEXTURE_UI_LEFT_UP,		 // UI　左上げ
		TEXTURE_UI_LEFT_DOWN,	 // UI　左下げ
		TEXTURE_THUNDER_EFFECT,  // 雷エフェクト
        TEXTURE_SNOW,            // 吹雪エフェクト
		TESTURE_ICON_FLAGRACING, // 旗揚げゲームアイコン
		TESTURE_ICON_FLY,        // 連打ゲームアイコン
		TESTURE_ICON_REMENBER,   // 記憶ゲームアイコン
		TESTURE_RESULTBOARD_BACK,// リザルトボード背景
		TESTURE_WARNING,         // 警告
		TESTURE_PENGUIN_SHADOW,  // ペンギンの影
		TEXTURE_STRAT_ICON,		 // STARTアイコン
		TEXTURE_RESULT_LOGO,	 // リザルトロゴ
		TEXTURE_END_ICON,		// ENDアイコン
		TEXTURE_ADD_POINT_DISPLAY,	//加点表示
		TEXTURE_MINIRESULT_LOGO,    // ミニリザルトロゴ
		TEXTURE_PENGUIN_SHADOW,    // ペンギンの影
		TESTURE_POINT_BACK,        // ポイント背景
		TEXTURE_MAX              // テクスチャ数
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