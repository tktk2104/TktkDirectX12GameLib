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

	public:

		// �g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(unsigned int materialSlot, unsigned int materialHandle);

		// �V���h�E�}�b�v����������
		void writeShadowMap() const;

		// �ʏ탁�b�V����`�悷��
		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		unsigned int m_useVertexBufferHandle;
		unsigned int m_useIndexBufferHandle;

		unsigned int m_indexNum;

		MeshPrimitiveTopology m_primitiveTopology;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_