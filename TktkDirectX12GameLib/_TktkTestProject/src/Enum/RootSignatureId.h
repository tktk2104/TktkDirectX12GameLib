#ifndef ROOT_SIGNATURE_ID_H_
#define ROOT_SIGNATURE_ID_H_

#include "ToIntFunc.h"

enum class RootSignatureId
{
	VertexColorPolygon = 0U,
	Count
};

constexpr unsigned int RootSignatureNum = static_cast<unsigned int>(RootSignatureId::Count);

#endif // !ROOT_SIGNATURE_ID_H_