#ifndef USE_NODE_CHECK_BIT_FLAG_ARRAY_PTR_H_
#define USE_NODE_CHECK_BIT_FLAG_ARRAY_PTR_H_

#include <memory>
#include <vector>

namespace tktkContainer
{
	using UseNodeCheckBitFlagArraySharedPtr = std::shared_ptr<std::vector<unsigned int>>;

	using UseNodeCheckBitFlagArrayWeakPtr = std::shared_ptr<std::vector<unsigned int>>;
}
#endif // !USE_NODE_CHECK_BIT_FLAG_ARRAY_PTR_H_
