#ifndef GAME_OBJECT_TAG_CARRIER_H_
#define GAME_OBJECT_TAG_CARRIER_H_

#include <TktkTemplateMetaLib/TypeCheck/isCastSignedInt32.h>

namespace tktk
{
	// �Q�[���I�u�W�F�N�g�^�O��ێ�����\����
	struct GameObjectTagCarrier
	{
	public:

		GameObjectTagCarrier() = default;

		// �Öٕϊ����������߂ɂ킴�Ɓuexplicit�v���O���Ă���
		template <class TagType, IsSignedInt32<TagType> = nullptr>
		GameObjectTagCarrier(TagType tag) : tag(static_cast<int>(tag)) {}

		// �s���Ȍ^��GameObjectTag�Ƃ��Ĉ������Ƃ���
		template <class TagType, IsNotSignedInt32<TagType> = nullptr>
		GameObjectTagCarrier(TagType tag) { static_assert(false, "GameObjectTag Fraud Type"); }

	public:

		// �����̃^�O�Ǝ��g�̃^�O�������������ʂ���
		template <class TagType, IsSignedInt32<TagType> = nullptr>
		bool isSame(TagType other) { return tag == static_cast<int>(other); }

		// �s���Ȍ^���r����
		template <class TagType, IsNotSignedInt32<TagType> = nullptr>
		bool isSame(TagType other) { static_assert(false, "GameObjectTag Fraud Type"); }

	public:

		bool operator==(const GameObjectTagCarrier& other) const { return tag == other.tag; }
		bool operator!=(const GameObjectTagCarrier& other) const { return tag != other.tag; }

	public:

		int tag{};
	};
}

// �uGameObjectTagCarrier�v���n�b�V���ɑΉ�������
template<>
struct std::hash<tktk::GameObjectTagCarrier>
{
	size_t operator()(const tktk::GameObjectTagCarrier& data) const { return std::hash<int>()(data.tag); }
};
#endif // !GAME_OBJECT_TAG_CARRIER_H_