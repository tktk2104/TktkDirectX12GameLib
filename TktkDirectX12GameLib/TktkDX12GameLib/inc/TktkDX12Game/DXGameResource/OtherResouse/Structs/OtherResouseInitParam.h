#ifndef OTHER_RESOUSE_INIT_PARAM_H_
#define OTHER_RESOUSE_INIT_PARAM_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include "../Font/Structs/FontManagerInitParam.h"

namespace tktk
{
	struct OtherResouseInitParam
	{
		tktkContainer::ResourceContainerInitParam	sceneMgrParam;
		tktkContainer::ResourceContainerInitParam	soundMgrParam;
		FontManagerInitParam						fontMgrParam;
	};
}
#endif // !OTHER_RESOUSE_INIT_PARAM_H_