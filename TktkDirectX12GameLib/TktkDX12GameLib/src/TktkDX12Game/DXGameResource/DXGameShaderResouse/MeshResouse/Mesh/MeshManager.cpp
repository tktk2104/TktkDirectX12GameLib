#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/MeshManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Structs/DrawMeshShaderFilePaths.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/MeshData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshDrawFuncBaseArgs.h"

namespace tktk
{
	MeshManager::MeshManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_basicMeshArray(initParam)
	{
	}

	MeshManager::~MeshManager() = default;

	size_t MeshManager::craete(const MeshInitParam& initParam)
	{
		return m_basicMeshArray.create(initParam);
	}

	size_t MeshManager::copy(size_t originalHandle)
	{
		return m_basicMeshArray.create(*m_basicMeshArray.getMatchHandlePtr(originalHandle));
	}

	void MeshManager::setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
	{
		m_basicMeshArray.getMatchHandlePtr(meshHandle)->setMaterialHandle(materialSlot, materialHandle);
	}

	void MeshManager::clearInstanceParam(size_t handle)
	{
		m_basicMeshArray.getMatchHandlePtr(handle)->clearInstanceParam();
	}

	void MeshManager::addInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam)
	{
		m_basicMeshArray.getMatchHandlePtr(handle)->addInstanceVertParam(instanceParam);
	}

	void MeshManager::addInstanceBoneMatrix(size_t handle, const std::array<tktkMath::Matrix4, 128>& boneMatrix)
	{
		m_basicMeshArray.getMatchHandlePtr(handle)->addInstanceBoneMatrix(boneMatrix);
	}

	void MeshManager::writeShadowMap(size_t handle) const
	{
		// �V���h�E�}�b�v�ւ̏������݂��s��
		m_basicMeshArray.getMatchHandlePtr(handle)->writeShadowMap();
	}

	void MeshManager::writeShadowMapUseBone(size_t handle) const
	{
		// �������g���ăV���h�E�}�b�v�ւ̏������݂��s��
		m_basicMeshArray.getMatchHandlePtr(handle)->writeShadowMapUseBone();
	}

	void MeshManager::draw(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// ���b�V���̃��C�e�B���O�Ɏg�p���郉�C�g����萔�o�b�t�@�ɏ�������
		DX12GameManager::updateLightCBuffer(baseArgs.lightHandle);

		// ���b�V���̕`����s��
		m_basicMeshArray.getMatchHandlePtr(handle)->draw(baseArgs);
	}

	void MeshManager::drawUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// ���b�V���̃��C�e�B���O�Ɏg�p���郉�C�g����萔�o�b�t�@�ɏ�������
		DX12GameManager::updateLightCBuffer(baseArgs.lightHandle);

		// �X�L�j���O���b�V���̕`����s��
		m_basicMeshArray.getMatchHandlePtr(handle)->drawUseBone(baseArgs);
	}
}