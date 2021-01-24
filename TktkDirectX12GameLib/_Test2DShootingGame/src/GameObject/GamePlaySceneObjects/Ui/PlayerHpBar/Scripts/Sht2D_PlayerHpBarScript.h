#ifndef SHT_2D_PLAYER_HP_BAR_SCRIPT_H_
#define SHT_2D_PLAYER_HP_BAR_SCRIPT_H_

#include <TktkDX12GameLib.h>
#include "../../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"

class Sht2D_PlayerHpBarScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerHpBarScript() = default;

public:

	void start();
	void update();

private:

	// �v���C���[�̑ϋv�͂̃R���|�[�l���g
	tktk::ComponentPtr<Sht2D_HealthPoint> m_healthPoint;

	// ���W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_PLAYER_HP_BAR_SCRIPT_H_