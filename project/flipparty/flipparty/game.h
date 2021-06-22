//=============================================================================
//
// gameヘッダ [game.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CCamera;
class CLight;
class CCharacter;
class CCpuPoint;
class CCheckPoint;
class CItemPoint;
class CCourse;
class CRuleBase;

//*****************************
//マクロ定義
//*****************************
#define MAX_PLAYER_NUM 1                               // プレイヤーの最大数

//*****************************
//クラス定義
//*****************************

//2dポリゴンクラス
class CGame : public CScene
{
public:
	//*****************************
	// 列挙定義
	//*****************************

	//*****************************
	// メンバ関数
	//*****************************
	CGame();
	~CGame();

	static CGame *Create(void); // クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

	// 取得処理
	static CCamera *GetCamera(void) { return m_pCamera; } // カメラポインタ
	static void SetCamera(CCamera * pCamera);             // カメラクラスのセット処理
private:

	//*****************************
	// メンバ変数
	//*****************************
	static CCamera*m_pCamera;            // カメラ
	static CLight*m_pLight;                               // ライトポインタ
	static CRuleBase *m_pGameRule;   // ルールクラス
};

#endif