#ifndef FONT_MANAGER_INIT_PARAM_H_
#define FONT_MANAGER_INIT_PARAM_H_

/* ResourceContainerInitParam */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	struct FontManagerInitParam
	{
		tktkContainer::ResourceContainerInitParam	containerInitParam			{  };
		unsigned int								fontHeight					{ 0U };
		unsigned int								textTextureWidth			{ 0U };
		size_t										textSpriteMaxInstanceCount	{ 0U };
	};
}
#endif // !FONT_MANAGER_INIT_PARAM_H_