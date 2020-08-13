#ifndef BODY_2D_PTR_H_
#define BODY_2D_PTR_H_

#include <memory>

class Body2dBase;
using Body2dSharedPtr	= std::shared_ptr<Body2dBase>;
using Body2dWeakPtr		= std::weak_ptr<Body2dBase>;

#endif // !BODY_2D_PTR_H_