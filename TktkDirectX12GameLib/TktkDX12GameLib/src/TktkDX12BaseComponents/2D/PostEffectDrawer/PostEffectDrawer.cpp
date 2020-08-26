#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	PostEffectDrawer::PostEffectDrawer(float drawPriority, unsigned int postEffectMaterialId, unsigned int useRtvDescriptorHeapHandle)
		: ComponentBase(drawPriority)
		, m_useRtvDescriptorHeapHandle(useRtvDescriptorHeapHandle)
		, m_postEffectMaterialId(postEffectMaterialId)
	{
	}

	void PostEffectDrawer::draw() const
	{
		// �|�X�g�G�t�F�N�g�̕`��ɕK�v�Ȓl���\���̂ɂ܂Ƃ߂�
		PostEffectMaterialDrawFuncArgs drawFuncArgs{};
		drawFuncArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		drawFuncArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapHandle	= m_useRtvDescriptorHeapHandle;

		// �|�X�g�G�t�F�N�g�̕`����s��
		DX12GameManager::drawPostEffect(m_postEffectMaterialId, drawFuncArgs);

		// TODO : �����_�[�^�[�Q�b�g�̃N���A�����͉�
		DX12GameManager::setRtv(0U, 0U, 1U);
		DX12GameManager::clearRtv(0U, 0U, tktkMath::Color_v::red);
		DX12GameManager::unSetRtv(0U, 0U, 1U);
	}
}