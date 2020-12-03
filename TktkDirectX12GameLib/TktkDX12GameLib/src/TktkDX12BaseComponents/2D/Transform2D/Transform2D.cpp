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

	void Transform2D::start()
	{
		if (!getGameObject()->getParent().expired()) m_isTransformParent = true;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
	}

	void Transform2D::update()
	{
		isTransformParentCheck(findParentTransform2D());
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

	void Transform2D::addWorldScaleRate(const tktkMath::Vector2& scaleRate)
	{
		setWorldScaleRate(m_worldScaleRate + scaleRate);
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
		updateLocalTransform(calculateWorldMatrix() * tktkMath::Matrix3::calculateInvert(calculateParentTraceUseMat()));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setWorldScaleRate(const tktkMath::Vector2& scaleRate)
	{
		m_worldScaleRate = scaleRate;
		updateLocalTransform(calculateWorldMatrix() * tktkMath::Matrix3::calculateInvert(calculateParentTraceUseMat()));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setWorldRotationDeg(float rotationDeg)
	{
		m_worldRotationDeg = rotationDeg;
		updateLocalTransform(calculateWorldMatrix() * tktkMath::Matrix3::calculateInvert(calculateParentTraceUseMat()));
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setLocalPosition(const tktkMath::Vector2& position)
	{
		m_localPosition = position;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setLocalScaleRate(const tktkMath::Vector2& scaleRate)
	{
		m_localScaleRate = scaleRate;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
		findAndUpdateRootTransform(this);
	}

	void Transform2D::setLocalRotationDeg(float rotationDeg)
	{
		m_localRotationDeg = rotationDeg;
		updateWorldTransform(calculateLocalMatrix() * calculateParentTraceUseMat());
		findAndUpdateRootTransform(this);
	}

	void Transform2D::updateLocalTransform(const tktkMath::Matrix3& newLocalMat)
	{
		m_localPosition = newLocalMat.calculateTranslation();
		m_localScaleRate = newLocalMat.calculateScale();
		m_localRotationDeg = newLocalMat.calculateRotation();
	}

	void Transform2D::updateWorldTransform(const tktkMath::Matrix3& newWorldMat)
	{
		m_worldPosition = newWorldMat.calculateTranslation();
		m_worldScaleRate = newWorldMat.calculateScale();
		m_worldRotationDeg = newWorldMat.calculateRotation();
	}

	tktkMath::Matrix3 Transform2D::calculateParentTraceUseMat()
	{
		auto parentTransform2D = findParentTransform2D();

		if (!isTransformParentCheck(parentTransform2D)) return tktkMath::Matrix3_v::identity;

		tktkMath::Matrix3 traceUseMatrix = tktkMath::Matrix3_v::identity;

		if ((static_cast<unsigned int>(m_traceType) & static_cast<unsigned int>(TraceParentType::traceScale)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix3::createScale(parentTransform2D->getWorldScaleRate());
		}

		if ((static_cast<unsigned int>(m_traceType) & static_cast<unsigned int>(TraceParentType::traceRotation)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix3::createRotation(parentTransform2D->getWorldRotationDeg());
		}

		if ((static_cast<unsigned int>(m_traceType) & static_cast<unsigned int>(TraceParentType::tracePos)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix3::createTranslation(parentTransform2D->getWorldPosition());
		}
		return traceUseMatrix;
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
		childTransform->updateWorldTransform(
			childTransform->calculateLocalMatrix() * childTransform->calculateParentTraceUseMat()
		);
		childTransform->updateAllChildTransform();
	}

	bool Transform2D::isTransformParentCheck(const ComponentPtr<Transform2D>& parentTransform2D)
	{
		if (parentTransform2D.expired())
		{
			if (m_isTransformParent) disableParentTransform();
			return false;
		}
		if (!m_isTransformParent) enableParentTransform();
		return true;
	}

	void Transform2D::enableParentTransform()
	{
		m_isTransformParent = true;
		auto parentTraceUseMat = calculateParentTraceUseMat();
		updateLocalTransform(calculateLocalMatrix() * tktkMath::Matrix3::calculateInvert(parentTraceUseMat));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat);

		findAndUpdateRootTransform(this);
	}

	void Transform2D::disableParentTransform()
	{
		m_isTransformParent = false;
		updateLocalTransform(calculateWorldMatrix());
		updateAllChildTransform();
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