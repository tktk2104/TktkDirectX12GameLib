#ifndef SHT_2D_GAME_CLEAR_TEXT_SCRIPT_H_
#define SHT_2D_GAME_CLEAR_TEXT_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_GameClearTextScript
	: public tktk::ComponentBase
{
public:

	Sht2D_GameClearTextScript() = default;

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
#endif // !SHT_2D_GAME_CLEAR_TEXT_SCRIPT_H_