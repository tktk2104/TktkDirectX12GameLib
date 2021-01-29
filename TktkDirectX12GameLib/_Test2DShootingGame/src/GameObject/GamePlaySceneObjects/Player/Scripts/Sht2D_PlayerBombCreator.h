#ifndef SHT_2D_PLAYER_BOMB_CREATOR_H_
#define SHT_2D_PLAYER_BOMB_CREATOR_H_

#include <TktkDX12GameLib.h>
#include "Sht2D_PlayerBulletCount.h"

// �v���C���[�{�����˃R���|�[�l���g
class Sht2D_PlayerBombCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBombCreator() = default;

public:

	void start();
	void update();

private:

	void createBomb();

	void explodeBomb();

private:

	// ���b�̃{���̈ړ����x
	constexpr static float				BombSpeedPerSec		{ 256.0f };

	// �{�����N���\�ɂȂ�܂ł̎��ԁi�b�j
	constexpr static float				BombActiveTimeSec	{ 1.0f };

	// �{���̔��ˊԊu�i�b�j
	constexpr static float				ShotIntervalTimeSec	{ 1.0f };

private:

	// �{���̔��ˊԊu�^�C�}�[
	float m_shotIntervalSecTimer{ 0.0f };

	// �{�����N������ׂ̃I�u�W�F�N�g�|�C���^
	tktk::GameObjectPtr m_targetBombObject;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;
};
#endif // !SHT_2D_PLAYER_BOMB_CREATOR_H_