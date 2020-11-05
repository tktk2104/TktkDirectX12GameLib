#ifndef SCENE_DATA_INIT_PARAM_H_
#define SCENE_DATA_INIT_PARAM_H_

#include <memory>
#include "SceneBase.h"
#include "SceneVTable.h"

namespace tktk
{
	struct SceneDataInitParam
	{
	public:

		template<class SceneType, class... Args>
		static SceneDataInitParam create(Args&&... constructorArgs)
		{
			return { &SceneVTableInitializer<SceneType>::m_vtable, std::make_shared<SceneType>(std::forward<Args>(constructorArgs)...) };
		}

	private:

		SceneDataInitParam(SceneVTable* vtablePtr, const std::shared_ptr<SceneBase>& scenePtr)
			: vtablePtr(vtablePtr)
			, scenePtr(scenePtr) {}

	public:

		SceneVTable*				vtablePtr;

		std::shared_ptr<SceneBase>	scenePtr;
	};
}
#endif // !SCENE_DATA_INIT_PARAM_H_