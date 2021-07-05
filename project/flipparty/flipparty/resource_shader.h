//=============================================================================
//
// Resource_Shaderヘッダ [Resource_Shader.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESOURCE_SHADER_H_
#define _RESOURCE_SHADER_H_

//*****************************
//インクルード
//*****************************
#include "main.h"

//*****************************
//マクロ定義
//*****************************
#define MAX_TEHNIQUENAME_LENGTH 32// テクニック文字数最大

//*****************************
//クラス定義
//*****************************

//テクスチャクラス
class CResourceShader
{
public:
	// 列挙
	// テクスチャ種類
	typedef enum
	{
		SHADER_PLAYER = 0,  // プレイヤー
		SHADER_MAX          // テクスチャ数
	}SHADER_TYPE;

	// シェーダー構造体
	typedef struct
	{
		LPD3DXEFFECT pEffect;                             // エフェクトファイル
		char achTechniqueName[MAX_TEHNIQUENAME_LENGTH];   // HLSLテクニックネーム
	}Shader;

	// メンバ関数
	static CResourceShader * Create(void);                          // クラス生成
	static void Release(void);                               // クラス破棄
	static Shader GetShader(SHADER_TYPE type); // テクスチャの取得処理*引数：取得したいテクスチャ

private:
	CResourceShader();//隠しコンストラクタ
public:
	~CResourceShader();

private:
	void Load(void); // テクスチャ読み込み
	void Unload(void); // テクスチャ破棄

	// メンバ変数
	static const std::string m_aEffectPath[SHADER_MAX];    // テクスチャのパス
	static const std::string m_aTechniqueName[SHADER_MAX]; // テクスチャのパス
	static CResourceShader *m_pSingleTex;                    // テクスチャクラスのポインタ*シングルトン用
	Shader m_apShader[SHADER_MAX];      // テクスチャのポインタ
};

#endif