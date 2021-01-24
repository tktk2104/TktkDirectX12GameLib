#ifndef SHT_2D_EXPLOSION_H_
#define SHT_2D_EXPLOSION_H_

#include <TktkDX12GameLib.h>

// �Q�����̔����G�t�F�N�g����邽�߂̍\����
struct Sht2D_Explosion
{
	// �����ɍ��W��n���ĂQ�����̔����G�t�F�N�g�����
	static tktk::GameObjectPtr create(
		const tktkMath::Vector2& position,
		const tktkMath::Vector2& posRandomRange,
		float intervalTimeSec,
		int totalNum,
		float effectEndTimeSec
	);
};
#endif // !SHT_2D_EXPLOSION_H_