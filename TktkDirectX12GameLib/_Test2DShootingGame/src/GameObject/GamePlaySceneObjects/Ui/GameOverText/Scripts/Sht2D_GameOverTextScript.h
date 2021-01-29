#ifndef SHT_2D_GAME_OVER_TEXT_SCRIPT_H_
#define SHT_2D_GAME_OVER_TEXT_SCRIPT_H_

#include <TktkDX12GameLib.h>

// �Q�[���I�[�o�[���̃V�[���J�ڃR���|�[�l���g
class Sht2D_GameOverTextScript
	: public tktk::ComponentBase
{
public:

	Sht2D_GameOverTextScript() = default;

public:

	void start();
	void update();

private:

	// ���b�̂������ړ����x
	constexpr static float MoveYSpeedPerSec{ 128.0f };

private:

	// �e�L�X�g�̈ړ����I��������H
	bool m_textMoveEnd{ false };

	// ���W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_GAME_OVER_TEXT_SCRIPT_H_
