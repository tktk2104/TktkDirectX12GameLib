#ifndef BASIC_MESH_DATA_H_
#define BASIC_MESH_DATA_H_

#include <vector>
#include "BasicMeshInitParam.h"
#include "../Structs/Subset.h"
#include "../../Structs/MeshDrawFuncBaseArgs.h"
#include "../../Structs/MeshPrimitiveTopology.h"

namespace tktk
{
	// �ʏ탁�b�V�������Ǘ�����N���X
	class BasicMeshData
	{
	public:

		explicit BasicMeshData(const BasicMeshInitParam& initParam);

		// �R�s�[�R���X�g���N�^
		BasicMeshData(const BasicMeshData& other);

		// ���[�u�R���X�g���N�^
		BasicMeshData(BasicMeshData&& other) noexcept;

		~BasicMeshData() = default;

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
#endif // !BASIC_MESH_DATA_H_