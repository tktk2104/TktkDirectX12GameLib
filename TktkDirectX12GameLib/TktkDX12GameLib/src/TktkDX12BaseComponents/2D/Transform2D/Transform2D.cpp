#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include <algorithm>

namespace tktk
{
	Transform2D::Transform2D(const tktkMath::Vector2& initPosition, const tktkMath::Vector2& initScaleRate, float initRotationDeg, TraceParentType traceType)
		: m_localPosition(initPosition)
		, m_localScaleRate(initScaleRate)
		, m_localRotationDeg(initRotationDeg)
		, m_traceType(traceType)
	{
	}

	void Transform2D::awake()
	{
		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Vector2 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseScale));
	}

	void Transform2D::start()
	{
		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Vector2 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseScale));
	}

	void Transform2D::afterChangeParent(const GameObjectPtr& beforParent)
	{
		auto curParent = getGameObject()->getParent();
		if (beforParent.expired() && !curParent.expired()) enableParentTransform(curParent);
		if (!beforParent.expired() && curParent.expired()) disableParentTransform(beforParent);
	}

	const tktkMath::Vector2& Transform2D::getWorldPosition() const
	{
		return m_worldPosition;
	}

	const tktkMath::Vector2& Transform2D::getWorldScaleRate() const
	{
		return m_worldScaleRate;
	}

	float Transform2D::getWorldRotationDeg() const
	{
		return m_worldRotationDeg;
	}

	const tktkMath::Vector2& Transform2D::getLocalPosition() const
	{
		return m_localPosition;
	}

	const tktkMath::Vector2& Transform2D::getLocalScaleRate() const
	{
		return m_localScaleRate;
	}

	float Transform2D::getLocalRotationDeg() const
	{
		return m_localRotationDeg;
	}

	tktkMath::Matrix3 Transform2D::calculateWorldMatrix() const
	{
		tktkMath::Matrix3 worldMatrix
			= tktkMath::Matrix3::createScale(m_worldScaleRate)
			* tktkMath::Matrix3::createRotation(m_worldRotationDeg)
			* tktkMath::Matrix3::createTranslation(m_worldPosition);

		return worldMatrix;
	}

	tktkMath::Matrix3 Transform2D::calculateLocalMatrix() const
	{
		tktkMath::Matrix3 localMatrix
			= tktkMath::Matrix3::createScale(m_localScaleRate)
			* tktkMath::Matrix3::createRotation(m_localRotationDeg)
			* tktkMath::Matrix3::createTranslation(m_localPosition);

		return localMatrix;
	}

	void Transform2D::addWorldPosition(const tktkMath::Vector2& position)
	{
		setWorldPosition(m_worldPosition + position);
	}

	void Transform2D::addWorldRotationDeg(float rotationDeg)
	{
		setWorldRotationDeg(m_localRotationDeg + rotationDeg);
	}

	void Transform2D::addLocalPosition(const tktkMath::Vector2& position)
	{
		setLocalPosition(m_localPosition + position);
	}

	void Transform2D::addLocalScaleRate(const tktkMath::Vector2& scaleRate)
	{
		setLocalScaleRate(m_localScaleRate + scaleRate);
	}

	void Transform2D::addLocalRotationDeg(float rotationDeg)
	{
		setLocalRotationDeg(m_localRotationDeg + rotationDeg);
	}

	void Transform2D::setWorldPosition(const tktkMath::Vector2& position)
	{
		m_worldPosition = position;

		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getWorldScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setWorldRotationDeg(float rotationDeg)
	{
		m_worldRotationDeg = rotationDeg;

		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getWorldScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setLocalPosition(const tktkMath::Vector2& position)
	{
		m_localPosition = position;

		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setLocalScaleRate(const tktkMath::Vector2& scaleRate)
	{
		m_localScaleRate = scaleRate;

		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setLocalRotationDeg(float rotationDeg)
	{
		m_localRotationDeg = rotationDeg;
		
		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	tktkMath::Vector2 Transform2D::calculateWorldUp() const
	{
		return calculateWorldMatrix().calculateUp();
	}

	tktkMath::Vector2 Transform2D::calculateWorldRight() const
	{
		return calculateWorldMatrix().calculateRight();
	}

	tktkMath::Vector2 Transform2D::calculateLocalUp() const
	{
		return calculateLocalMatrix().calculateUp();
	}

	tktkMath::Vector2 Transform2D::calculateLocalRight() const
	{
		return calculateLocalMatrix().calculateRight();
	}

	tktkMath::Matrix3 Transform2D::calculateTraceUseMat(const ComponentPtr<Transform2D>& target, TraceParentType traceType)
	{
		if (target.expired()) return tktkMath::Matrix3_v::identity;

		tktkMath::Matrix3 traceUseMatrix = tktkMath::Matrix3_v::identity;

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::traceScale)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix3::createScale(target->getWorldScaleRate());
		}

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::traceRotation)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix3::createRotation(target->getWorldRotationDeg());
		}

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::tracePos)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix3::createTranslation(target->getWorldPosition());
		}
		return traceUseMatrix;
	}

	tktkMath::Vector2 Transform2D::calculateTraceUseScale(const ComponentPtr<Transform2D>& target, TraceParentType traceType)
	{
		if (target.expired()) return tktkMath::Vector2_v::one;

		tktkMath::Vector2 traceUseScale = tktkMath::Vector2_v::one;

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::traceScale)) != 0)
		{
			traceUseScale = target->getWorldScaleRate();
		}
		return traceUseScale;
	}

	tktkMath::Vector2 Transform2D::calculateTraceUseInvScale(const ComponentPtr<Transform2D>& target, TraceParentType traceType)
	{
		tktkMath::Vector2 traceUseInvScale = calculateTraceUseScale(target, traceType);

		return tktkMath::Vector2(
			1.0f / traceUseInvScale.x,
			1.0f / traceUseInvScale.y
		);
	}

	void Transform2D::updateLocalTransform(const tktkMath::Matrix3& newLocalMat, const tktkMath::Vector2 newLocalScale)
	{
		m_localPosition		= newLocalMat.calculateTranslation();
		m_localRotationDeg	= newLocalMat.calculateRotation();
		m_localScaleRate	= newLocalScale;
	}

	void Transform2D::updateWorldTransform(const tktkMath::Matrix3& newWorldMat, const tktkMath::Vector2 newWorldScale)
	{
		m_worldPosition		= newWorldMat.calculateTranslation();
		m_worldRotationDeg	= newWorldMat.calculateRotation();
		m_worldScaleRate	= newWorldScale;
	}

	ComponentPtr<Transform2D> Transform2D::findParentTransform2D() const
	{
		GameObjectPtr parent = getGameObject()->getParent();
		if (parent.expired()) return ComponentPtr<Transform2D>();
		return parent->getComponent<Transform2D>();
	}

	void Transform2D::updateAllChildTransform()
	{
		auto childList = getGameObject()->getChildren();

		std::for_each(
			std::begin(childList),
			std::end(childList),
			[this](const auto& node) { updateChildTransform(node); }
		);
	}

	void Transform2D::updateChildTransform(const GameObjectPtr& child)
	{
		auto childTransform = child->getComponent<Transform2D>();
		if (childTransform.expired()) return;

		auto parentTransform = childTransform->findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseMat = calculateTraceUseMat(parentTransform, childTransform->m_traceType);
		tktkMath::Vector2 parentTraceUseScale = calculateTraceUseScale(parentTransform, childTransform->m_traceType);
		childTransform->updateWorldTransform(
			childTransform->calculateLocalMatrix() * parentTraceUseMat,
			tktkMath::Vector2::scale(childTransform->getLocalScaleRate(), parentTraceUseScale)
		);

		childTransform->updateAllChildTransform();
	}

	//bool Transform2D::isTransformParentCheck(const ComponentPtr<Transform2D>& parentTransform2D)
	//{
	//	if (parentTransform2D.expired())
	//	{
	//		if (m_isTransformParent) disableParentTransform();
	//		return false;
	//	}
	//	if (!m_isTransformParent) enableParentTransform();
	//	return true;
	//}

	void Transform2D::enableParentTransform(const GameObjectPtr& curParent)
	{
		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getWorldScaleRate(), parentTraceUseInvScale));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseScale));

		findAndUpdateRootTransform(this);
	}

	void Transform2D::disableParentTransform(const GameObjectPtr& beforParent)
	{
		auto parentTransform = findParentTransform2D();
		tktkMath::Matrix3 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Matrix3 parentTraceUseInvMat = tktkMath::Matrix3::calculateInvert(calculateTraceUseMat(parentTransform, m_traceType));
		tktkMath::Vector2 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		tktkMath::Vector2 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseMat, tktkMath::Vector2::scale(getWorldScaleRate(), parentTraceUseScale));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseInvMat, tktkMath::Vector2::scale(getLocalScaleRate(), parentTraceUseInvScale));

		findAndUpdateRootTransform(this);
	}

	void Transform2D::findAndUpdateRootTransform(Transform2D* curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform2D();

		if (curParentTransform.expired())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}

	void Transform2D::findAndUpdateRootTransform(const ComponentPtr<Transform2D>& curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform2D();

		if (curParentTransform.expired())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}
}