#ifndef SHT_2D_PLAYER_MISSILE_COUNTER_SCRIPT_H_
#define SHT_2D_PLAYER_MISSILE_COUNTER_SCRIPT_H_

#include <vector>
#include <TktkDX12GameLib.h>
#include "../../../Player/Scripts/Sht2D_PlayerBulletCount.h"

// �v���C���[�~�T�C���̎c�e�������A�C�R����\������R���|�[�l���g
class Sht2D_PlayerMissileCounterScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMissileCounterScript() = default;

public:

	void start();
	void update();

private:

	// �v���C���[�~�T�C���̎c�e�A�C�R���̕`�悘���W�Ԋu
	constexpr static float MissileIconXInterval{ -40.0f };

private:

	// �v���C���[�̎c�e���̃R���|�[�l���g
	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;

	// �v���C���[�~�T�C���̎c�e�A�C�R���I�u�W�F�N�g�z��
	std::vector<tktk::GameObjectPtr> m_missileIconObjectArray;
};
#endif // !SHT_2D_PLAYER_MISSILE_COUNTER_SCRIPT_H_
