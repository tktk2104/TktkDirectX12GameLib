#ifndef SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_
#define SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ���������o��������R���|�[�l���g
class Sht2D_StreamingLineSpawnerScript
	: public tktk::ComponentBase
{
public:

	Sht2D_StreamingLineSpawnerScript() = default;

public:

	void update();

private:

	// �������̖��b�̈ړ����x
	constexpr static tktkMath::Vector2	VelocityPerSec					{ 0.0f, 1024.0f };

	// �P�t���[���ŏo�����闬�����̐��i���b�̐��ł͂Ȃ��̂Œ��Ӂj
	constexpr static size_t				SpawnStreamingLineCountPerFrame { 4U };
};
#endif // !SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_