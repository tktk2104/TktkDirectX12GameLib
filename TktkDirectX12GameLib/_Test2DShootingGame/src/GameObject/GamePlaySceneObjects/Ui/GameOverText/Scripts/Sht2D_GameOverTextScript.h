#ifndef SHT_2D_GAME_OVER_TEXT_SCRIPT_H_
#define SHT_2D_GAME_OVER_TEXT_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ゲームオーバー時のシーン遷移コンポーネント
class Sht2D_GameOverTextScript
	: public tktk::ComponentBase
{
public:

	Sht2D_GameOverTextScript() = default;

public:

	void start();
	void update();

private:

	// 毎秒のｙ方向移動速度
	constexpr static float MoveYSpeedPerSec{ 128.0f };

private:

	// テキストの移動が終わったか？
	bool m_textMoveEnd{ false };

	// 座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_GAME_OVER_TEXT_SCRIPT_H_
