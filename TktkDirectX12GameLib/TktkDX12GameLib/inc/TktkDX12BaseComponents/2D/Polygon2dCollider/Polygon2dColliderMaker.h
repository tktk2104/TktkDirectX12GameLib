#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include "Polygon2dCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class Polygon2dColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		Polygon2dColliderMaker() = default;
		Polygon2dColliderMaker(const Polygon2dColliderMaker& other) = default;
		Polygon2dColliderMaker& operator = (const Polygon2dColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static Polygon2dColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<Polygon2dCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		Polygon2dColliderMaker& collisionGroupType(CollisionGroupTypeCarrier value);

		// �����蔻��̑傫����ݒ�
		Polygon2dColliderMaker& vertexs(const std::vector<tktkMath::Vector2>& value);

		// �Փˑ���������o���������s�����H
		Polygon2dColliderMaker& isExtrude(bool value);

		// �����o����₷����ݒ�i�����j
		Polygon2dColliderMaker& extrudedRate(float value);

	private:

		// ���g�̃|�C���^
		static Polygon2dColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr					m_user					{ };
		CollisionGroupTypeCarrier		m_collisionGroupType	{ 0 };
		std::vector<tktkMath::Vector2>	m_vertexs				{};
		bool							m_isExtrude				{ false };
		float							m_extrudedRate			{ 0.0f };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_