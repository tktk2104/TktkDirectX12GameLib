#ifndef SHT_2D_OBJECT_SPAWNER_H_
#define SHT_2D_OBJECT_SPAWNER_H_

#include <TktkDX12GameLib.h>

// �G�l�~�[�o���I�u�W�F�N�g
struct Sht2D_ObjectSpawner
{
	static tktk::GameObjectPtr create(const std::string& csvFilePath);
};
#endif // !SHT_2D_OBJECT_SPAWNER_H_
