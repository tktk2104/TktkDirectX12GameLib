#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunnerInitParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PostEffectDrawFuncRunnerInitParam PostEffectDrawFuncRunnerInitParam::m_self;

	PostEffectDrawFuncRunnerInitParam& PostEffectDrawFuncRunnerInitParam::create()
	{
		m_self = PostEffectDrawFuncRunnerInitParam();

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓Q�[���`��G���A
		m_self.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		return m_self;
	}
}