#ifndef SHT_2D_PLAYER_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// �v���C���[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
class Sht2D_PlayerCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerCollisionReaction() = default;

public:

	void update();


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    ���uonCollisionEnter(otherObject)�v�A�uonCollisionStay(otherObject)�v�A�uonCollisionExit(otherObject)�v�ŏՓˎ��̏����������ł��܂��B
	���@���ꂼ��A�u�ՓˊJ�n���v�A�u�Փ˒��v�A�u�ՓˏI�����v�̃^�C�~���O�ŌĂ΂�A�����ŏՓˑ���̃I�u�W�F�N�g���擾�ł��܂��B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	void onCollisionEnter(const tktk::GameObjectPtr & other);
	void onCollisionStay(const tktk::GameObjectPtr & other);

private:

	// �����G�t�F�N�g�̏o���Ԋu�i�b�j
	constexpr static float CreateExplosionIntervalTimeSec{ 0.5f };

private:

	// �����G�t�F�N�g�̏o���Ԋu�^�C�}�[�i�b�j
	float m_createExplosionIntervalSecTimer{ 0.0f };
};
#endif // !SHT_2D_PLAYER_COLLISION_REACTION_H_
