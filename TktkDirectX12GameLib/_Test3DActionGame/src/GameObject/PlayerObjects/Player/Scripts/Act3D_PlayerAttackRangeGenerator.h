#ifndef ACT_3D_PLAYER_ATTACK_RANGE_GENERATOR_H_
#define ACT_3D_PLAYER_ATTACK_RANGE_GENERATOR_H_

#include <TktkDX12GameLib.h>

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

	float				m_generateTimeSec;
	float				m_deleteTimeSec;
	float				m_attackRangeSecTimer{ 0.0f };
	tktk::GameObjectPtr m_attackRange;
};
#endif // !ACT_3D_PLAYER_ATTACK_RANGE_GENERATOR_H_