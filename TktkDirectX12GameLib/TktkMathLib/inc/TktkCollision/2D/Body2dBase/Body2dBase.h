#ifndef BODY_2D_BASE_H_
#define BODY_2D_BASE_H_

#include "../../../TktkMath/Structs/Matrix3.h"
#include "ShapeType2D.h"
#include "HitInfo2D.h"

class Body2dBase
{
public:

	Body2dBase(
		ShapeType2D shapeType,
		const tktkMath::Matrix3 & localMatrix
	);

	virtual ~Body2dBase();

public:

	virtual bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const = 0;

public:

	void transform(const tktkMath::Matrix3& world);

	tktkMath::Matrix3 calculatePose() const;

	const tktkMath::Matrix3& getWorldMatrix() const;

	const tktkMath::Matrix3& getLocalMatrix() const;
	void setLocalMatrix(const tktkMath::Matrix3 & localMatrix);

	ShapeType2D getShapeType() const;

private:

	// 図形の種類
	ShapeType2D m_shapeType;

	// ワールドの行列
	tktkMath::Matrix3 m_worldMatrix;

	// ローカルの行列
	tktkMath::Matrix3 m_localMatrix;
};
#endif // !BODY_2D_BASE_H_