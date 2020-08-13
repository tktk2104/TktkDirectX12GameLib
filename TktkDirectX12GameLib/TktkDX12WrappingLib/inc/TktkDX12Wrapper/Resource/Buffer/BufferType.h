#ifndef BUFFER_TYPE_H_
#define BUFFER_TYPE_H_

namespace tktk
{
	enum class BufferType
	{
		vertex,
		index,
		constant,
		texture,
		renderTarget,
		depthStencil
	};
}
#endif // !BUFFER_TYPE_H_