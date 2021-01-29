#ifndef EXPLOSION_2D_SCRIPT_H_
#define EXPLOSION_2D_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_ExplosionScript
	: public tktk::ComponentBase
{
public:

	// ��莞�Ԍ�Ɏ��g���E���R���|�[�l���g
	explicit Sht2D_ExplosionScript(float effectEndTimeSec);
	~Sht2D_ExplosionScript() = default;

public:

	// ���t���[���Ă΂��
	void update();

private:

	// �����I���^�C�}�[�i�b�j
	float m_effectEndSecTimer;
};
#endif // !EXPLOSION_2D_SCRIPT_H_