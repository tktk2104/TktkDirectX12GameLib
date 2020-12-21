#ifndef OTHER_RESOUSE_INIT_PARAM_H_
#define OTHER_RESOUSE_INIT_PARAM_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct OtherResouseInitParam
	{
		tktkContainer::ResourceContainerInitParam sceneMgrParam;
		tktkContainer::ResourceContainerInitParam soundMgrParam;
		tktkContainer::ResourceContainerInitParam fontMgrParam;

		tktkMath::Vector2 textTextureSize{ 4096.0f, 256.0f };
	};
}
#endif // !OTHER_RESOUSE_INIT_PARAM_H_