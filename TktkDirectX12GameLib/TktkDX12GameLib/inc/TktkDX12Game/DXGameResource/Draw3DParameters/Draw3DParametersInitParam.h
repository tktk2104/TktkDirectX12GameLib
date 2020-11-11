#ifndef DRAW_3D_PARAMETERS_INIT_PARAM_H_
#define DRAW_3D_PARAMETERS_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct Draw3DParametersInitParam
	{
		tktkContainer::ResourceContainerInitParam lightMgrParam;
		tktkContainer::ResourceContainerInitParam cameraMgrParam;
	};
}
#endif // !DRAW_3D_PARAMETERS_INIT_PARAM_H_