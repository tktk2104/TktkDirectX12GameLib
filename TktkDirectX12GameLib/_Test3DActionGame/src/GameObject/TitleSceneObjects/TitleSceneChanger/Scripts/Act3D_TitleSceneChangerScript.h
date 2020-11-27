#ifndef ACT_3D_TITLE_SCENE_CHANGER_SCRIPT_H_
#define ACT_3D_TITLE_SCENE_CHANGER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// タイトルシーンから遷移する処理を行うコンポーネント
class Act3D_TitleSceneChangerScript
	: public tktk::ComponentBase
{
public:

	Act3D_TitleSceneChangerScript() = default;

public:

	void start();
	void update();

private:

	// シーン遷移するまでの時間
	constexpr static float SceneChangeTime	{ 2.0f };

	// 自身を殺すまでの時間
	constexpr static float SelfDeadTime		{ 4.0f };

private:
	
	// シーン遷移タイマー
	float	m_sceneChangeSecTimer	{ 0.0f };

	// シーン遷移を開始したか？
	bool	m_startSceneChange		{ false };

	// シーン遷移が終わったか？
	bool	m_endSceneChange		{ false };

	// 画面のフェード用スプライト描画コンポーネント
	tktk::ComponentPtr<tktk::SpriteDrawer> m_fadeSprite;

	// サウンド再生コンポーネント
	tktk::ComponentPtr<tktk::SoundPlayer> m_soundPlayer;
};
#endif // !ACT_3D_TITLE_SCENE_CHANGER_SCRIPT_H_