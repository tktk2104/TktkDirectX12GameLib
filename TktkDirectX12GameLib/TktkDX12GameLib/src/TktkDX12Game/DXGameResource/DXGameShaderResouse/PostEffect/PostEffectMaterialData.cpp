#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialDrawFuncArgs.h"

namespace tktk
{
	PostEffectMaterialData::PostEffectMaterialData(const PostEffectMaterialInitParam& initParam)
		: m_usePipeLineStateHandle(initParam.usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(initParam.useDescriptorHeapHandle)
		, m_autoClearRtvDescriptorHeapHandleArray(initParam.autoClearRtvDescriptorHeapHandleArray)
	{
	}

	PostEffectMaterialData::PostEffectMaterialData(PostEffectMaterialData&& other) noexcept
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
		, m_autoClearRtvDescriptorHeapHandleArray(std::move(other.m_autoClearRtvDescriptorHeapHandleArray))
	{
	}

	void PostEffectMaterialData::drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// �����_�[�^�[�Q�b�g��ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (drawFuncArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �`��Ŏg�p����p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(m_usePipeLineStateHandle);

		// �`��Ŏg�p����f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapHandle} });

		// �g���C�A���O���X�g���b�v�ŕ`�悷��
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// �|���S���̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite));

		// �|���S���̃C���f�b�N�X�o�b�t�@��ݒ肷��
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

		// �h���[�R�[��
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// �`���ɃN���A���郌���_�[�^�[�Q�b�g�r���[�p�̃f�B�X�N���v�^�q�[�v�̃n���h�������񂷂�
		for (const auto& node : m_autoClearRtvDescriptorHeapHandleArray)
		{
			DX12GameManager::setRtv(node, 0U, 1U);
			DX12GameManager::clearRtv(node, 0U);
			DX12GameManager::unSetRtv(node, 0U, 1U);
		}
	}
}