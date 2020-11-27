#ifndef ACT_3D_PLAYER_ATTACK_RANGE_GENERATOR_H_
#define ACT_3D_PLAYER_ATTACK_RANGE_GENERATOR_H_

#include <TktkDX12GameLib.h>

// �v���C���[�̍U��������o�������鏈�����s���R���|�[�l���g
class Act3D_PlayerAttackRangeGenerator
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerAttackRangeGenerator(float generateTimeSec, float deleteTimeSec, const tktkMath::Vector3& position, const tktkMath::Vector3& scale);

public:

	void start();
	void onEnable();
	void onDisable();
	void update();

private:

	// �U�����肪�o������܂ł̎���
	float				m_generateTimeSec;

	// �U�����肪���ł���܂ł̎���
	float				m_deleteTimeSec;

	// �U������̏o���A���ł��Ǘ����邽�߂̃^�C�}�[
	float				m_attackRangeSecTimer{ 0.0f };

	// �v���C���[�̍U������͈̓I�u�W�F�N�g
	tktk::GameObjectPtr m_attackRange;
};
#endif // !ACT_3D_PLAYER_ATTACK_RANGE_GENERATOR_H_