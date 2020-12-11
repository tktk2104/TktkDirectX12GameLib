#ifndef DRAW_FUNC_RUNNER_MANAGER_INIT_PARAM_H_
#define DRAW_FUNC_RUNNER_MANAGER_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct DrawFuncRunnerManagerInitParam
	{
		tktkContainer::ResourceContainerInitParam postEffectDrawFuncRunnerMgrParam;
		tktkContainer::ResourceContainerInitParam billboardDrawFuncRunnerMgrParam;
		tktkContainer::ResourceContainerInitParam meshDrawFuncRunnerMgrParam;
	};
}
#endif // !DRAW_FUNC_RUNNER_MANAGER_INIT_PARAM_H_