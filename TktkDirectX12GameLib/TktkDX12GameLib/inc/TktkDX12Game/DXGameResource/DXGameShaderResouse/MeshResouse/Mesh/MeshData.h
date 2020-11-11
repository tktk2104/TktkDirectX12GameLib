#ifndef MESH_DATA_H_
#define MESH_DATA_H_

/* class member */
#include <vector>
#include "Structs/MeshPrimitiveTopology.h"

namespace tktk
{
	struct MeshInitParam;
	struct Subset;
	struct MeshDrawFuncBaseArgs;

	// �ʏ탁�b�V�������Ǘ�����N���X
	class MeshData
	{
	public:

		explicit MeshData(const MeshInitParam& initParam);

		// �R�s�[�R���X�g���N�^
		MeshData(const MeshData& other);

		// ���[�u�R���X�g���N�^
		MeshData(MeshData&& other) noexcept;

		~MeshData() = default;

	public:

		// �g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(size_t materialSlot, size_t materialHandle);

		// �V���h�E�}�b�v����������
		void writeShadowMap() const;

		// �ʏ탁�b�V����`�悷��
		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		size_t m_useVertexBufferHandle{ 0U };
		size_t m_useIndexBufferHandle{ 0U };

		size_t m_indexNum;

		MeshPrimitiveTopology m_primitiveTopology;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !MESH_DATA_H_