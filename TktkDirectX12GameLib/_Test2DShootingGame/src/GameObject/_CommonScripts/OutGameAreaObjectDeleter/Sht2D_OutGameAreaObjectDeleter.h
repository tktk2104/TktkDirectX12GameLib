#ifndef SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_
#define SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_

#include <TktkDX12GameLib.h>

// 画面外に出たら自身を殺すコンポーネント
class Sht2D_OutGameAreaObjectDeleter
	: public tktk::ComponentBase
{
public:

	Sht2D_OutGameAreaObjectDeleter(const tktkMath::Vector2& gameAreaLeftTopPos, const tktkMath::Vector2& gameAreaRightBottomPos);

public:

	void start();
	void update();

private:

	// 画面範囲の左上座標
	tktkMath::Vector2 m_gameAreaLeftTopPos;

	// 画面範囲の右下座標
	tktkMath::Vector2 m_gameAreaRightBottomPos;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_
