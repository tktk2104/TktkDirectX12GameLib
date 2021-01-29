#ifndef SHT_2D_FLAME_SCRIPT_H_
#define SHT_2D_FLAME_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ���G�t�F�N�g�̃A�j���[�V�����R���|�[�l���g
class Sht2D_FlameScript
	: public tktk::ComponentBase
{
public:
	
	Sht2D_FlameScript() = default;

public:

	void start();
	void update();

private:

	// �ő�̂������X�P�[��
	constexpr static float MaxYScaleRate{ 1.4f };

	// �X�P�[�����O�^�C�}�[�̍ő�l�i�b�j
	constexpr static float ScalingMaxTimeSec{ 0.3f };

private:

	// �X�P�[�����O�p�^�C�}�[�i�b�j
	float									m_scalingSecTimer{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D>	m_transform;
};
#endif // !SHT_2D_FLAME_SCRIPT_H_