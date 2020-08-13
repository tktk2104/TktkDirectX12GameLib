#ifndef SYSTEM_DX_GAME_RESOURCE_ID_GETTER_H_
#define SYSTEM_DX_GAME_RESOURCE_ID_GETTER_H_

#include "IdType/SystemBasicMeshType.h"
#include "IdType/SystemBasicMeshMaterialType.h"
#include "IdType/SystemPostEffectMaterialType.h"
#include "../DXGameResourceNum.h"

namespace tktk
{
	class SystemDXGameResourceIdGetter
	{
	public:

		// コンストラクタ内で「resourceNum」の値を書き換えます
		SystemDXGameResourceIdGetter(DXGameResourceNum* resourceNum);

	public:

		unsigned int getSystemId(SystemBasicMeshType type)				const;
		unsigned int getSystemId(SystemBasicMeshMaterialType type)		const;
		unsigned int getSystemId(SystemPostEffectMaterialType type)		const;

	private:

		DXGameResourceNum m_basicDxGameResourceNum;
	};
}
#endif // !SYSTEM_DX_GAME_RESOURCE_ID_GETTER_H_
