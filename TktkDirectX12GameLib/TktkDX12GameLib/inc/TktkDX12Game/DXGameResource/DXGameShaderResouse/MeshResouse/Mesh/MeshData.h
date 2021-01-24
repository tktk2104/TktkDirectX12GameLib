#ifndef MESH_DATA_H_
#define MESH_DATA_H_

/* class member */
#include <array>
#include <vector>
#include <forward_list>
#include <TktkMath/Structs/Matrix4.h>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>
#include <TktkDX12Wrapper/Resource/Buffer/CopySourceDataCarrier.h>

namespace tktk
{
	struct MeshInitParam;
	struct Subset;
	struct MeshDrawFuncBaseArgs;

	// ���b�V�������Ǘ�����N���X
	class MeshData
	{
	public:

		explicit MeshData(const MeshInitParam& initParam);

		// �R�s�[�R���X�g���N�^
		MeshData(const MeshData& other);

		// ���[�u�R���X�g���N�^
		MeshData(MeshData&& other) noexcept;

		~MeshData();

	public:

		// �g�p���Ă���}�e���A�����X�V����
		void setMaterialHandle(size_t materialSlot, size_t materialHandle);

		// ���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam();

		// ���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceVertParam(const CopySourceDataCarrier& instanceParam);

		// �X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
		void addInstanceBoneMatrix(const std::array<tktkMath::Matrix4, 128>& boneMatrix);

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		void updateInstanceParamVertBuffer() const;

		// �����������e�N�X�`���o�b�t�@���X�V����
		void updateBoneMatrixTextureBuffer() const;

		// �V���h�E�}�b�v����������
		void writeShadowMap() const;

		// �������g���ăV���h�E�}�b�v����������
		void writeShadowMapUseBone() const;
		
		// ���b�V�����C���X�^���X�`�悷��
		void draw(const MeshDrawFuncBaseArgs& baseArgs) const;

		// �X�L�j���O���b�V�����C���X�^���X�`�悷��
		void drawUseBone(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		// ���b�V���̒��_�o�b�t�@�̃n���h��
		size_t m_useVertexBufferHandle			{ 0U };

		// ���b�V���̃C���f�b�N�X�o�b�t�@�̃n���h��
		size_t m_useIndexBufferHandle			{ 0U };

		// �C���X�^���X�����������_�o�b�t�@�̃n���h��
		size_t m_instanceParamVertexBufferHandle{ 0U };

		// �C���X�^���X�����������_�o�b�t�@���X�V����o�b�t�@�̃n���h��
		size_t m_instanceParamUplaodBufferHandle{ 0U };

		// �����������e�N�X�`���o�b�t�@�̃n���h��
		size_t m_boneMatrixTextureBufferHandle	{ 0U };

		// ���b�V���̑��C���f�b�N�X��
		size_t m_indexNum;

		// ���b�V���̒��_���̌`��
		PrimitiveTopology				m_primitiveTopology;

		// ���b�V�����g�p���Ă���}�e���A���ƑΉ�����C���f�b�N�X���̑g�ݍ��킹�̈ꗗ
		std::vector<Subset>				m_materialSlots;

		// �C���X�^���X�`��p�̒��_�o�b�t�@�̌^�̃T�C�Y
		size_t							m_instanceVertParamTypeSize;

		// �C���X�^���X�`�悷�鎞�̍ő�C���X�^���X��
		size_t							m_maxInstanceCount;

		// ��x�ɕ`�悷��C���X�^���X��
		size_t							m_instanceCount{ 0U };

		// �C���X�^���X���̔z��
		std::forward_list<std::vector<unsigned char>>			m_instanceVertParamList;
		std::forward_list<std::array<tktkMath::Matrix4, 128U>>	m_instanceBoneMatrixList;
	};
}
#endif // !MESH_DATA_H_