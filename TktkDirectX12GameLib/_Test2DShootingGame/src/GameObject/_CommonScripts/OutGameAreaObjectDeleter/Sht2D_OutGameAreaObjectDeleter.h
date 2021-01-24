#ifndef SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_
#define SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_

#include <TktkDX12GameLib.h>

class Sht2D_OutGameAreaObjectDeleter
	: public tktk::ComponentBase
{
public:

	Sht2D_OutGameAreaObjectDeleter(const tktkMath::Vector2& gameAreaLeftTopPos, const tktkMath::Vector2& gameAreaRightBottomPos);

public:

	void start();
	void update();

private:

	tktkMath::Vector2 m_gameAreaLeftTopPos		{         - 128.0f,         - 128.0f };
	tktkMath::Vector2 m_gameAreaRightBottomPos	{ 1920.0f + 128.0f, 1080.0f + 128.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_
