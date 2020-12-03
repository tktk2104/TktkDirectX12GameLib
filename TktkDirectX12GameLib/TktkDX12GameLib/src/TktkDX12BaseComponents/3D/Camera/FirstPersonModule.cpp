#include "TktkDX12BaseComponents/3D/Camera/FirstPersonModule.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	FirstPersonModule::FirstPersonModule(
		float rotateDegSpeedPerSec,
		float moveSpeedPerSec,
		bool alwaysMoveForward,
		bool enableUpDownKey
	)
		: m_rotateDegSpeedPerSec(rotateDegSpeedPerSec)
		, m_moveSpeedPerSec(moveSpeedPerSec)
		, m_alwaysMoveForward(alwaysMoveForward)
		, m_enableUpDownKey(enableUpDownKey)
	{
	}

	void FirstPersonModule::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("FirstPersonModule Transform3D not found");
		}
	}

	void FirstPersonModule::update()
	{
		rotate();

		if (m_enableUpDownKey) moveVertical();

		moveHorizontal();
	}

	float FirstPersonModule::getRotateDegSpeedPerSec()
	{
		return m_rotateDegSpeedPerSec;
	}

	void FirstPersonModule::setRotateDegSpeedPerSec(float deg)
	{
		m_rotateDegSpeedPerSec = deg;
	}

	float FirstPersonModule::getMoveSpeedPerSec()
	{
		return m_moveSpeedPerSec;
	}

	void FirstPersonModule::setMoveSpeedPerSec(float speed)
	{
		m_moveSpeedPerSec = speed;
	}

	bool FirstPersonModule::getAlwaysMoveForward()
	{
		return m_alwaysMoveForward;
	}

	void FirstPersonModule::setAlwaysMoveForward(bool flag)
	{
		m_alwaysMoveForward = flag;
	}

	bool FirstPersonModule::getEnableUpDownKey()
	{
		return m_enableUpDownKey;
	}

	void FirstPersonModule::setEnableUpDownKey(bool flag)
	{
		m_enableUpDownKey = flag;
	}

	void FirstPersonModule::rotate()
	{
		tktkMath::Vector3 rotationEuler = m_transform->calculateWorldEulerAngles();

		if (DX12GameManager::isPush(KeybordKeyType::key_Left))	rotationEuler.y -= m_rotateDegSpeedPerSec * DX12GameManager::deltaTime();
		if (DX12GameManager::isPush(KeybordKeyType::key_Right))	rotationEuler.y += m_rotateDegSpeedPerSec * DX12GameManager::deltaTime();
		if (DX12GameManager::isPush(KeybordKeyType::key_Up))	rotationEuler.x -= m_rotateDegSpeedPerSec * DX12GameManager::deltaTime();
		if (DX12GameManager::isPush(KeybordKeyType::key_Down))	rotationEuler.x += m_rotateDegSpeedPerSec * DX12GameManager::deltaTime();

		if (rotationEuler.x > 89.0f && rotationEuler.x < 180.0f)	rotationEuler.x = 89.0f;
		if (rotationEuler.x > 180.0f && rotationEuler.x < 271.0f)	rotationEuler.x = 271.0f;

		m_transform->setWorldEulerAngles(rotationEuler);
	}

	void FirstPersonModule::moveHorizontal()
	{
		tktkMath::Matrix4 worldMat = tktkMath::Matrix4_v::identity;

		if (m_alwaysMoveForward)
		{
			worldMat = m_transform->calculateWorldMatrix();
		}
		else
		{
			tktkMath::Vector3 cameraRote = m_transform->calculateWorldEulerAngles();

			worldMat = tktkMath::Matrix4::createTRS(
				m_transform->getWorldPosition(),
				tktkMath::Quaternion::createFromEulerAngle({ 0.0f, cameraRote.y, 0.0f }),
				m_transform->getWorldScaleRate()
			);
		}
		tktkMath::Vector3 moveVel = tktkMath::Vector3_v::zero;

		if (DX12GameManager::isPush(KeybordKeyType::key_W))	moveVel =  worldMat.calculateForwardLH();
		if (DX12GameManager::isPush(KeybordKeyType::key_S))	moveVel = -worldMat.calculateForwardLH();
		if (DX12GameManager::isPush(KeybordKeyType::key_A))	moveVel = -worldMat.calculateRight();
		if (DX12GameManager::isPush(KeybordKeyType::key_D))	moveVel =  worldMat.calculateRight();

		moveVel *= m_moveSpeedPerSec * DX12GameManager::deltaTime();
		m_transform->addWorldPosition(moveVel);
	}

	void FirstPersonModule::moveVertical()
	{
		float verticalMoveVel = 0.0f;

		if (DX12GameManager::isPush(KeybordKeyType::key_Space)) verticalMoveVel = 1.0f;
		if (DX12GameManager::isPush(KeybordKeyType::key_Lshift) || DX12GameManager::isPush(KeybordKeyType::key_Rshift)) verticalMoveVel = -1.0f;

		verticalMoveVel *= m_moveSpeedPerSec * DX12GameManager::deltaTime();
		m_transform->addWorldPosition({ 0.0f, verticalMoveVel, 0.0f });
	}
}