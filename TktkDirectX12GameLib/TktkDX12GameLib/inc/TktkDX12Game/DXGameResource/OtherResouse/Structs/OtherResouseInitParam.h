#ifndef OTHER_RESOUSE_INIT_PARAM_H_
#define OTHER_RESOUSE_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct OtherResouseInitParam
	{
		tktkContainer::ResourceContainerInitParam sceneMgrParam;
		tktkContainer::ResourceContainerInitParam soundMgrParam;
	};
}
#endif // !OTHER_RESOUSE_INIT_PARAM_H_