#ifndef SCENE_ID_H_
#define SCENE_ID_H_

// シーンの種類
enum class SceneId
{
	Loading,	// ローディングシーン
	Title,		// タイトルシーン
	StageSelect,// ステージセレクトシーン
	GamePlay,	// ゲームプレイシーン

	Stage1,		// ステージ１シーン
	Stage2,		// ステージ２シーン
	Stage3,		// ステージ３シーン

	Result,		// リザルトシーン
};
#endif // !SCENE_ID_H_