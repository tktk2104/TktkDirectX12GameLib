#ifndef SHT_2D_PLAYER_NORMAL_BULLET_CREATOR_H_
#define SHT_2D_PLAYER_NORMAL_BULLET_CREATOR_H_

#include <TktkDX12GameLib.h>

// �v���C���[�ʏ�e���˃R���|�[�l���g
class Sht2D_PlayerNormalBulletCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerNormalBulletCreator() = default;

public:

	void start();
	void update();

private:

	// �e�̔��ˑ��x
	constexpr static float BulletSpeedPerSec	{ 1024.0f };

	// �e�̔��ˊԊu�i�b�j
	constexpr static float ShotIntervalTimeSec	{ 0.1f };

private:

	// �e�̔��ˊԊu�^�C�}�[�i�b�j
	float m_shotIntervalSecTimer{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_PLAYER_NORMAL_BULLET_CREATOR_H_