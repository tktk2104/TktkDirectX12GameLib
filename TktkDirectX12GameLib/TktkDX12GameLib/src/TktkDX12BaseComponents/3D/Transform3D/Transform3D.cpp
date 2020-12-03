#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"

#include <algorithm>
#include <TktkMath/Structs/Vector2.h>
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	Transform3D::Transform3D(const tktkMath::Vector3& initPosition, const tktkMath::Vector3& initScaleRate, const tktkMath::Quaternion& initRotation, TraceParentType traceType)
		: m_localPosition(initPosition)
		, m_localScaleRate(initScaleRate)
		, m_localRotation(initRotation)
		, m_traceType(traceType)
	{
	}

	void Transform3D::start()
	{
		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
	}

	void Transform3D::afterChangeParent(const GameObjectPtr& beforParent)
	{
		auto curParent = getGameObject()->getParent();
		if (beforParent.expired() && !curParent.expired()) enableParentTransform(curParent);
		if (!beforParent.expired() && curParent.expired()) disableParentTransform(beforParent);
	}

	const tktkMath::Vector3& Transform3D::getWorldPosition() const
	{
		return m_worldPosition;
	}

	const tktkMath::Vector3& Transform3D::getWorldScaleRate() const
	{
		return m_worldScaleRate;
	}

	const tktkMath::Quaternion& Transform3D::getWorldRotation() const
	{
		return m_worldRotation;
	}

	tktkMath::Vector3 Transform3D::calculateWorldEulerAngles() const
	{
		return getWorldRotation().calculateEulerAngle();
	}

	const tktkMath::Vector3& Transform3D::getLocalPosition() const
	{
		return m_localPosition;
	}

	const tktkMath::Vector3& Transform3D::getLocalScaleRate() const
	{
		return m_localScaleRate;
	}

	const tktkMath::Quaternion& Transform3D::getLocalRotation() const
	{
		return m_localRotation;
	}

	tktkMath::Vector3 Transform3D::calculateLocalEulerAngles() const
	{
		return getLocalRotation().calculateEulerAngle();
	}

	tktkMath::Matrix4 Transform3D::calculateWorldMatrix() const
	{
		return tktkMath::Matrix4::createTRS(m_worldPosition, m_worldRotation, m_worldScaleRate);
	}

	tktkMath::Matrix4 Transform3D::calculateLocalMatrix() const
	{
		return tktkMath::Matrix4::createTRS(m_localPosition, m_localRotation, m_localScaleRate);
	}

	void Transform3D::addWorldPosition(const tktkMath::Vector3& position)
	{
		setWorldPosition(m_worldPosition + position);
	}

	void Transform3D::addWorldRotation(const tktkMath::Quaternion& rotation)
	{
		setWorldRotation(m_localRotation + rotation);
	}

	void Transform3D::addWorldEulerAngles(const tktkMath::Vector3& eulerAngles)
	{
		setWorldRotation(m_localRotation * tktkMath::Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::addLocalPosition(const tktkMath::Vector3& position)
	{
		setLocalPosition(m_localPosition + position);
	}

	void Transform3D::addLocalScaleRate(const tktkMath::Vector3& scaleRate)
	{
		setLocalScaleRate(m_localScaleRate + scaleRate);
	}

	void Transform3D::addLocalRotation(const tktkMath::Quaternion& rotation)
	{
		setLocalRotation(m_localRotation * rotation);
	}

	void Transform3D::addLocalEulerAngles(const tktkMath::Vector3& eulerAngles)
	{
		setLocalRotation(m_localRotation * tktkMath::Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::setWorldPosition(const tktkMath::Vector3& position)
	{
		m_worldPosition = position;

		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		tktkMath::Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, tktkMath::Vector3::scale(getWorldScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setWorldRotation(const tktkMath::Quaternion& rotation)
	{
		m_worldRotation = rotation;

		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		tktkMath::Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, tktkMath::Vector3::scale(getWorldScaleRate(), parentTraceUseInvScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setWorldEulerAngles(const tktkMath::Vector3& eulerAngles)
	{
		setWorldRotation(tktkMath::Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::setWorldAxisAngle(const tktkMath::Vector3& axis, float degree)
	{
		setWorldRotation(tktkMath::Quaternion::createFromAxisAngle(axis, degree));
	}

	void Transform3D::setLocalPosition(const tktkMath::Vector3& position)
	{
		m_localPosition = position;

		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setLocalScaleRate(const tktkMath::Vector3& scaleRate)
	{
		m_localScaleRate = scaleRate;

		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setLocalRotation(const tktkMath::Quaternion& rotation)
	{
		m_localRotation = rotation;

		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector3::scale(getLocalScaleRate(), parentTraceUseScale));
		findAndUpdateRootTransform(this);
	}

	void Transform3D::setLocalEulerAngles(const tktkMath::Vector3& eulerAngles)
	{
		setLocalRotation(tktkMath::Quaternion::createFromEulerAngle(eulerAngles));
	}

	void Transform3D::setLocalAxisAngle(const tktkMath::Vector3& axis, float degree)
	{
		setLocalRotation(tktkMath::Quaternion::createFromAxisAngle(axis, degree));
	}

	tktkMath::Vector3 Transform3D::calculateWorldForwardLH() const
	{
		return calculateWorldMatrix().calculateForwardLH();
	}

	tktkMath::Vector3 Transform3D::calculateWorldForwardRH() const
	{
		return calculateWorldMatrix().calculateForwardRH();
	}

	tktkMath::Vector3 Transform3D::calculateWorldRight() const
	{
		return calculateWorldMatrix().calculateRight();
	}

	tktkMath::Vector3 Transform3D::calculateWorldUp() const
	{
		return calculateWorldMatrix().calculateUp();
	}

	tktkMath::Vector3 Transform3D::calculateLocalForwardLH() const
	{
		return calculateLocalMatrix().calculateForwardLH();
	}

	tktkMath::Vector3 Transform3D::calculateLocalForwardRH() const
	{
		return calculateLocalMatrix().calculateForwardRH();
	}

	tktkMath::Vector3 Transform3D::calculateLocalRight() const
	{
		return calculateLocalMatrix().calculateRight();
	}

	tktkMath::Vector3 Transform3D::calculateLocalUp() const
	{
		return calculateLocalMatrix().calculateUp();
	}

	void Transform3D::setWorldForwardLH(const tktkMath::Vector3& forward)
	{
		setWorldRotation(tktkMath::Quaternion::createLookRotation(forward));
	}

	void Transform3D::setWorldForwardRH(const tktkMath::Vector3& forward)
	{
		setWorldRotation(tktkMath::Quaternion::createLookRotation(forward));
	}

	void Transform3D::setWorldRight(const tktkMath::Vector3& right)
	{
		setWorldRotation(tktkMath::Quaternion::createFromToRotation(tktkMath::Vector3_v::right, right));
	}

	void Transform3D::setWorldUp(const tktkMath::Vector3& up)
	{
		setWorldRotation(tktkMath::Quaternion::createFromToRotation(tktkMath::Vector3_v::zero, up));
	}

	void Transform3D::setLocalForwardLH(const tktkMath::Vector3& forward)
	{
		setLocalRotation(tktkMath::Quaternion::createLookRotation(forward));
	}

	void Transform3D::setLocalForwardRH(const tktkMath::Vector3& forward)
	{
		setLocalRotation(tktkMath::Quaternion::createLookRotation(forward));
	}

	void Transform3D::setLocalRight(const tktkMath::Vector3& right)
	{
		setLocalRotation(tktkMath::Quaternion::createFromToRotation(tktkMath::Vector3_v::right, right));
	}

	void Transform3D::setLocalUp(const tktkMath::Vector3& up)
	{
		setLocalRotation(tktkMath::Quaternion::createFromToRotation(tktkMath::Vector3_v::zero, up));
	}

	void Transform3D::lookAt(const ComponentPtr<Transform3D>& target)
	{
#ifdef _DEBUG
		if (target.expired())
		{
			throw std::runtime_error("target Transform3D not found");
		}
#endif // _DEBUG
		tktkMath::Vector3 targetPosition = target->getWorldPosition();

		lookAt(targetPosition);
	}

	void Transform3D::lookAt(const tktkMath::Vector3& target)
	{
		auto lookAtRotation = (getWorldPosition() - target);

		tktkMath::Vector3 horizontalLookAtRotation	{ lookAtRotation.x,	0.0f,				lookAtRotation.z };
		tktkMath::Vector3 verticalLookAtRotation	{ 0.0f,				lookAtRotation.y,	tktkMath::Vector2(lookAtRotation.x, lookAtRotation.z).length() };

		setWorldRotation(tktkMath::Quaternion::createLookRotation(horizontalLookAtRotation) * tktkMath::Quaternion::createLookRotation(verticalLookAtRotation));
	}

	void Transform3D::rotateAround(const tktkMath::Vector3& worldPoint, const tktkMath::Vector3& axis, float angle)
	{
		tktkMath::Vector3 relativeSelfWorldPos = m_worldPosition - worldPoint;

		setWorldPosition(relativeSelfWorldPos * tktkMath::Quaternion::createFromAxisAngle(axis, angle) + worldPoint);
	}

	/*Matrix4 Transform3D::calculateLocalToWorldMatrix() const
	{
		return Matrix4::createTranslation(-m_worldPosition);
	}

	Matrix4 Transform3D::calculateWorldToLocalMatrix() const
	{
		return calculateLocalToWorldMatrix().inverse();
	}*/

	tktkMath::Matrix4 Transform3D::calculateTraceUseMat(const ComponentPtr<Transform3D>& target, TraceParentType traceType)
	{
		if (target.expired()) return tktkMath::Matrix4_v::identity;

		tktkMath::Matrix4 traceUseMatrix = tktkMath::Matrix4_v::identity;

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::traceScale)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix4::createScale(target->getWorldScaleRate());
		}

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::traceRotation)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix4::createFromQuaternion(target->getWorldRotation());
		}

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::tracePos)) != 0)
		{
			traceUseMatrix *= tktkMath::Matrix4::createTranslation(target->getWorldPosition());
		}
		return traceUseMatrix;
	}

	tktkMath::Vector3 Transform3D::calculateTraceUseScale(const ComponentPtr<Transform3D>& target, TraceParentType traceType)
	{
		if (target.expired()) return tktkMath::Vector3_v::one;

		tktkMath::Vector3 traceUseScale = tktkMath::Vector3_v::one;

		if ((static_cast<unsigned int>(traceType) & static_cast<unsigned int>(TraceParentType::traceScale)) != 0)
		{
			traceUseScale = target->getWorldScaleRate();
		}
		return traceUseScale;
	}

	tktkMath::Vector3 Transform3D::calculateTraceUseInvScale(const ComponentPtr<Transform3D>& target, TraceParentType traceType)
	{
		tktkMath::Vector3 traceUseInvScale = calculateTraceUseScale(target, traceType);

		return tktkMath::Vector3(
			1.0f / traceUseInvScale.x,
			1.0f / traceUseInvScale.y,
			1.0f / traceUseInvScale.z
		);
	}

	void Transform3D::updateLocalTransform(const tktkMath::Matrix4& newLocalMat, const tktkMath::Vector3 newLocalScale)
	{
		m_localPosition = newLocalMat.calculateTranslation();
		m_localRotation = newLocalMat.calculateRotation();
		m_localScaleRate = newLocalScale;
	}

	void Transform3D::updateWorldTransform(const tktkMath::Matrix4& newWorldMat, const tktkMath::Vector3 newWorldScale)
	{
		m_worldPosition = newWorldMat.calculateTranslation();
		m_worldRotation = newWorldMat.calculateRotation();
		m_worldScaleRate = newWorldScale;
	}

	/*Matrix4 Transform3D::calculateTraceUseInvMat()
	{
		Matrix4 traceUseInvMatrix = Matrix4::identity;

		if ((m_traceType & TRACE_PARENT_POS) != 0)
		{
			traceUseInvMatrix *= Matrix4::createTranslation(-getWorldPosition());
		}

		if ((m_traceType & TRACE_PARENT_ROTATION) != 0)
		{
			traceUseInvMatrix *= Matrix4::createFromQuaternion(Quaternion::calculateInvert(getWorldRotation()));
		}

		if ((m_traceType & TRACE_PARENT_SCALE) != 0)
		{
			traceUseInvMatrix *= Matrix4::createScale(Vector3(1.0f / getWorldScaleRate().x, 1.0f / getWorldScaleRate().y, 1.0f / getWorldScaleRate().z));
		}
		return traceUseInvMatrix;
	}*/

	ComponentPtr<Transform3D> Transform3D::findParentTransform3D() const
	{
		GameObjectPtr parent = getGameObject()->getParent();
		if (parent.expired()) return ComponentPtr<Transform3D>();
		return parent->getComponent<Transform3D>();
	}

	void Transform3D::updateAllChildTransform()
	{
		auto childList = getGameObject()->getChildren();

		std::for_each(
			std::begin(childList),
			std::end(childList),
			[this](const auto& node) { updateChildTransform(node); }
		);
	}

	void Transform3D::updateChildTransform(const GameObjectPtr& child)
	{
		auto childTransform = child->getComponent<Transform3D>();
		if (childTransform.expired()) return;

		auto parentTransform = childTransform->findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, childTransform->m_traceType);
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, childTransform->m_traceType);
		childTransform->updateWorldTransform(
			childTransform->calculateLocalMatrix() * parentTraceUseMat,
			tktkMath::Vector3::scale(childTransform->getLocalScaleRate(), parentTraceUseScale)
		);

		childTransform->updateAllChildTransform();
	}

	void Transform3D::enableParentTransform(const GameObjectPtr& curParent)
	{
		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		tktkMath::Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseInvMat, tktkMath::Vector3::scale(getWorldScaleRate(), parentTraceUseInvScale));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseMat, tktkMath::Vector3::scale(getLocalScaleRate(), parentTraceUseScale));

		findAndUpdateRootTransform(this);
	}

	void Transform3D::disableParentTransform(const GameObjectPtr& beforParent)
	{
		auto parentTransform = findParentTransform3D();
		tktkMath::Matrix4 parentTraceUseMat = calculateTraceUseMat(parentTransform, m_traceType);
		tktkMath::Matrix4 parentTraceUseInvMat = calculateTraceUseMat(parentTransform, m_traceType).calculateInvert();
		tktkMath::Vector3 parentTraceUseScale = calculateTraceUseScale(parentTransform, m_traceType);
		tktkMath::Vector3 parentTraceUseInvScale = calculateTraceUseInvScale(parentTransform, m_traceType);
		updateLocalTransform(calculateWorldMatrix() * parentTraceUseMat, tktkMath::Vector3::scale(getWorldScaleRate(), parentTraceUseScale));
		updateWorldTransform(calculateLocalMatrix() * parentTraceUseInvMat, tktkMath::Vector3::scale(getLocalScaleRate(), parentTraceUseInvScale));

		findAndUpdateRootTransform(this);
	}

	void Transform3D::findAndUpdateRootTransform(Transform3D* curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform3D();

		if (curParentTransform.expired())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}

	void Transform3D::findAndUpdateRootTransform(const ComponentPtr<Transform3D>& curTransform)
	{
		auto curParentTransform = curTransform->findParentTransform3D();

		if (curParentTransform.expired())
		{
			curTransform->updateAllChildTransform();
			return;
		}
		findAndUpdateRootTransform(curParentTransform);
	}
}