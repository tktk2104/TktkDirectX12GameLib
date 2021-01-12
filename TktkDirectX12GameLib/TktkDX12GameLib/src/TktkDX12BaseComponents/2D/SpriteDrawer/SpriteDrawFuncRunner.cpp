#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawFuncRunner.h"

#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawFuncRunnerInitParam.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	SpriteDrawFuncRunner::SpriteDrawFuncRunner(size_t spriteHandle, const SpriteDrawFuncRunnerInitParam& initParam)
		: ComponentBase(initParam.m_drawPriority)
		, m_spriteHandle(spriteHandle)
		, m_rtvDescriptorHeapHandle(initParam.m_rtvDescriptorHeapHandle)
	{
	}

	void SpriteDrawFuncRunner::update()
	{
		DX12GameManager::clearSpriteInstanceParam(m_spriteHandle);
	}

	void SpriteDrawFuncRunner::draw() const
	{
		// �w�肵�X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l�𒸓_�o�b�t�@�ɏ�������
		DX12GameManager::updateSpriteInstanceParam(m_spriteHandle);

		SpriteMaterialDrawFuncArgs baseArgs{};
		baseArgs.viewportHandle				= DX12GameManager::getSystemHandle(SystemViewportType::Basic);
		baseArgs.scissorRectHandle			= DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);
		baseArgs.rtvDescriptorHeapHandle	= m_rtvDescriptorHeapHandle;

		DX12GameManager::drawSprite(m_spriteHandle, baseArgs);
	}
}