#ifndef ACT_3D_PLAYER_H_
#define ACT_3D_PLAYER_H_

#include <TktkDX12GameLib.h>

// プレイヤーオブジェクト
struct Act3D_Player
{
public:

	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation);

private:

	static tktk::GameObjectPtr createCamera(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation);
};
#endif // !ACT_3D_PLAYER_H_