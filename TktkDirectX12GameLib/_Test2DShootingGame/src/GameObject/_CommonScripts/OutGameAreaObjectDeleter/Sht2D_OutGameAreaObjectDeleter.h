#ifndef SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_
#define SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_

#include <TktkDX12GameLib.h>

// ��ʊO�ɏo���玩�g���E���R���|�[�l���g
class Sht2D_OutGameAreaObjectDeleter
	: public tktk::ComponentBase
{
public:

	Sht2D_OutGameAreaObjectDeleter(const tktkMath::Vector2& gameAreaLeftTopPos, const tktkMath::Vector2& gameAreaRightBottomPos);

public:

	void start();
	void update();

private:

	// ��ʔ͈͂̍�����W
	tktkMath::Vector2 m_gameAreaLeftTopPos;

	// ��ʔ͈͂̉E�����W
	tktkMath::Vector2 m_gameAreaRightBottomPos;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_OUT_GAME_AREA_OBJECT_DELETER_H_
