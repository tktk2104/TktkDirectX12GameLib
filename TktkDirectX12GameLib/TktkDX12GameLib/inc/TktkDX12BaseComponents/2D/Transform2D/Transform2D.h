#ifndef TRANSFORM_2D_H_
#define TRANSFORM_2D_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* funcUseType */
#include <TktkMath/Structs/Matrix3.h>

/* class member */
#include <TktkMath/Structs/Vector2.h>
#include "TraceParentType.h"

namespace tktk
{
	// �Q�����̎��g�̍��W�A��]�A�X�P�[�����Ǘ�����R���|�[�l���g
	class Transform2D
		: public ComponentBase
	{
	public:

		Transform2D(
			const tktkMath::Vector2& initPosition,	// �������W
			const tktkMath::Vector2& initScaleRate,	// �����X�P�[��
			float initRotationDeg,			// ������]
			TraceParentType traceType		// �e��Transform2D�Ƃ̊֌W���̎��
		);

	public:

		// <PolymorphismFunc>
		void awake();
		void start();
		void afterChangeParent(const GameObjectPtr& beforParent);

	public:

		// ���[���h���W���擾
		const tktkMath::Vector2& getWorldPosition() const;
		// ���[���h�X�P�[�����擾
		const tktkMath::Vector2& getWorldScaleRate() const;
		// ���[���h��]���擾
		float getWorldRotationDeg() const;

		// ���[�J�����W���擾
		const tktkMath::Vector2& getLocalPosition() const;
		// ���[�J���X�P�[�����擾
		const tktkMath::Vector2& getLocalScaleRate() const;
		// ���[�J����]���擾
		float getLocalRotationDeg() const;

		// ���[���h�̍s����v�Z
		tktkMath::Matrix3 calculateWorldMatrix() const;
		// ���[�J���̍s����v�Z
		tktkMath::Matrix3 calculateLocalMatrix() const;

		// ���[���h���W���w�蕪��������
		void addWorldPosition(const tktkMath::Vector2& position);
		// ���[���h��]���w�蕪��������
		void addWorldRotationDeg(float rotationDeg);

		// ���[�J�����W���w�蕪��������
		void addLocalPosition(const tktkMath::Vector2& position);
		// ���[�J���X�P�[�����w�蕪��������
		void addLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// ���[�J����]���w�蕪��������
		void addLocalRotationDeg(float rotationDeg);

		// ���[���h���W��ݒ�
		void setWorldPosition(const tktkMath::Vector2& position);
		// ���[���h��]��ݒ�
		void setWorldRotationDeg(float rotationDeg);

		// ���[�J�����W��ݒ�
		void setLocalPosition(const tktkMath::Vector2& position);
		// ���[�J���X�P�[����ݒ�
		void setLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// ���[�J����]��ݒ�
		void setLocalRotationDeg(float rotationDeg);

	private:

		// ������Transform2D��Ǐ]����̂Ɏg�p���郏�[���h�s����v�Z
		static tktkMath::Matrix3 calculateTraceUseMat(const ComponentPtr<Transform2D>& target, TraceParentType traceType);

		// ������Transform2D��Ǐ]����̂Ɏg�p����X�P�[���l���v�Z
		static tktkMath::Vector2 calculateTraceUseScale(const ComponentPtr<Transform2D>& target, TraceParentType traceType);

		// ������Transform2D��Ǐ]����̂Ɏg�p����t�X�P�[���l���v�Z
		static tktkMath::Vector2 calculateTraceUseInvScale(const ComponentPtr<Transform2D>& target, TraceParentType traceType);

	private:

		// �V�������[�J���s����w�肵�Ď��g�̃��[�J���̃g�����X�t�H�[�����X�V����
		void updateLocalTransform(const tktkMath::Matrix3& newLocalMat, const tktkMath::Vector2 newLocalScale);

		// �V�������[���h�s����w�肵�Ď��g�̃��[���h�̃g�����X�t�H�[�����X�V����
		void updateWorldTransform(const tktkMath::Matrix3& newWorldMat, const tktkMath::Vector2 newWorldScale);

		// �e��Transform2D���擾
		ComponentPtr<Transform2D> findParentTransform2D() const;

		// �S�Ă̎q����Transform2D���X�V����
		void updateAllChildTransform();

		// �w�肵���q����Transform2D���X�V����
		void updateChildTransform(const GameObjectPtr& child);

		//// �e��Transform2D��Ǐ]���邩�𔻒肷��
		//bool isTransformParentCheck(const ComponentPtr<Transform2D>& parentTransform2D);

		// �e��Transform2D�̒Ǐ]���J�n
		void enableParentTransform(const GameObjectPtr& curParent);

		// �e��Transform2D�̒Ǐ]���I��
		void disableParentTransform(const GameObjectPtr& beforParent);

		// �匳��Transform����S�Ă̎q�����X�V����i���|�C���^�Łj
		void findAndUpdateRootTransform(Transform2D* curTransform);

		// �匳��Transform����S�Ă̎q�����X�V����iCfpPtr�Łj
		void findAndUpdateRootTransform(const ComponentPtr<Transform2D>& curTransform);

	private:

		// ���[�J���̍��W
		tktkMath::Vector2 m_localPosition	{ tktkMath::Vector2_v::zero };
		// ���[�J���̃X�P�[��
		tktkMath::Vector2 m_localScaleRate	{ tktkMath::Vector2_v::one };
		// ���[�J���̉�]�i�x���@�j
		float m_localRotationDeg			{ 0.0f };

		// ���[���h�̍��W
		tktkMath::Vector2 m_worldPosition	{ tktkMath::Vector2_v::zero };
		// ���[���h�̃X�P�[��
		tktkMath::Vector2 m_worldScaleRate	{ tktkMath::Vector2_v::one };
		// ���[�J���̉�]�i�x���@�j
		float m_worldRotationDeg			{ 0.0f };

		// �e��Transform2D�Ƃ̊֌W��
		TraceParentType m_traceType;
	};
}
#endif // !TRANSFORM_2D_H_