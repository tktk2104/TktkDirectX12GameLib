#ifndef SCENE_INIT_PARAM_H_
#define SCENE_INIT_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

/* SceneVTable, SceneVTableInitializer<> */
#include "SceneVTable.h"

namespace tktk
{
	class SceneBase;

	// ƒV[ƒ“‚ğì‚é‚½‚ß‚Ì‰Šú‰»î•ñ‚Ì\‘¢‘Ì
	struct SceneInitParam
	{
	public:

		template<class SceneType, class... Args>
		static SceneInitParam create(Args&&... constructorArgs)
		{
			return { &SceneVTableInitializer<SceneType>::m_vtable, std::make_shared<SceneType>(std::forward<Args>(constructorArgs)...) };
		}

	private:

		SceneInitParam(SceneVTable* vtablePtr, const std::shared_ptr<SceneBase>& scenePtr)
			: vtablePtr(vtablePtr)
			, scenePtr(scenePtr) {}

	public:

		SceneVTable*				vtablePtr;

		std::shared_ptr<SceneBase>	scenePtr;
	};
}
#endif // !SCENE_INIT_PARAM_H_