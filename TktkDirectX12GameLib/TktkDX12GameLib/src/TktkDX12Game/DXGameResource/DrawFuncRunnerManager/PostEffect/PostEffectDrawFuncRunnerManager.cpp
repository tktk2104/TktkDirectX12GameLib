#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/PostEffect/PostEffectDrawFuncRunnerManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunner.h"

#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/DrawGameAreaCBufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/BasicPostEffectCBufferData.h"

namespace tktk
{
    PostEffectDrawFuncRunnerManager::PostEffectDrawFuncRunnerManager(const tktkContainer::ResourceContainerInitParam& initParam)
        : m_drawFuncRunnerList(initParam)
    {
    }

	// �f�X�g���N�^���C�����C��������
	PostEffectDrawFuncRunnerManager::~PostEffectDrawFuncRunnerManager() = default;

	void PostEffectDrawFuncRunnerManager::createSystemResource()
	{
		// �`��G���A�`��p�̃|�X�g�G�t�F�N�g�}�e���A�������
		createDrawGameAreaDrawFuncRunner();

		// �����������s��Ȃ��|�X�g�G�t�F�N�g�}�e���A�������
		createNotPostEffectDrawFuncRunner();

		// ���m�N���`��p�̃|�X�g�G�t�F�N�g�}�e���A�������
		createPostEffectMonochromeDrawFuncRunner();

		// ���]�F�`��p�̃|�X�g�G�t�F�N�g�}�e���A�������
		createPostEffectNegativeDrawFuncRunner();

		// ���ω��ڂ����`��p�̃|�X�g�G�t�F�N�g�}�e���A�������
		createPostEffectAveragingBlurDrawFuncRunner();

		// �G���{�X���H�`��p�̃|�X�g�G�t�F�N�g�}�e���A�������
		createPostEffectEmbossDrawFuncRunner();

		// �V���[�v�l�X���H�`��p�̃|�X�g�G�t�F�N�g�}�e���A�������
		createPostEffectSharpnessDrawFuncRunner();
	}

	size_t PostEffectDrawFuncRunnerManager::create(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam)
    {
		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����
		auto drawFuncRunner = DX12GameManager::createComponent<PostEffectDrawFuncRunner>(GameObjectPtr(), postEffectMaterialHandle, initParam);

		// �ŏ��͔�A�N�e�B�u���
		drawFuncRunner->setActive(false);

		// �Ǘ��R���e�i�ɒǉ�����
        return m_drawFuncRunnerList.create(drawFuncRunner);
    }

    void PostEffectDrawFuncRunnerManager::startPostEffect(size_t handle)
    {
		// �����������s��Ȃ��|�X�g�G�t�F�N�g�̎��s�R���|�[�l���g���A�N�e�B�u�ɂ���
		m_notPostEffectDrawFuncRunner->setActive(false);

		// �w��̃|�X�g�G�t�F�N�g�̎��s�R���|�[�l���g���A�N�e�B�u�ɂ���
		(*m_drawFuncRunnerList.getMatchHandlePtr(handle))->setActive(true);
    }

    void PostEffectDrawFuncRunnerManager::stopPostEffect()
    {
		// �S�Ẵ|�X�g�G�t�F�N�g�̎��s�R���|�[�l���g���A�N�e�B�u�ɂ���
		for (const auto& node : m_drawFuncRunnerList) node->setActive(false);

		// �����������s��Ȃ��|�X�g�G�t�F�N�g�̎��s�R���|�[�l���g���A�N�e�B�u�ɂ���
		m_notPostEffectDrawFuncRunner->setActive(true);
    }

	void PostEffectDrawFuncRunnerManager::createDrawGameAreaDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::DrawGameArea);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::DrawGameArea);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// �Q�[����ʂ̑傫�����擾
		const auto& screenSize			= DX12GameManager::getScreenSize();

		// �Q�[���`��G���A�̑傫�����擾
		const auto& drawGameAreaSize	= DX12GameManager::getDrawGameAreaSize();

		// ���^�[�{�b�N�X�i�Q�[����ʂ̗]���̑傫���j
		auto letterBoxSize = tktkMath::Vector2_v::zero;

		// ���^�[�{�b�N�X�̑傫�����v�Z����
		if (screenSize.x / drawGameAreaSize.x >= screenSize.y / drawGameAreaSize.y)
		{
			letterBoxSize.x = (screenSize.x - (screenSize.y * drawGameAreaSize.x / drawGameAreaSize.y)) / 2;
		}
		else
		{
			letterBoxSize.y = (screenSize.y - (screenSize.x * drawGameAreaSize.y / drawGameAreaSize.x)) / 2;
		}

		// �Q�[���`��G���A�`��p�|�X�g�G�t�F�N�g�p�̒萔�o�b�t�@�̏����l�����߂�
		DrawGameAreaCBufferData drawGameAreaCbufferData{};
		drawGameAreaCbufferData.drawGameAreaSizeRate = { 1.0f - (letterBoxSize.x / screenSize.x * 2.0f), 1.0f - (letterBoxSize.y / screenSize.y * 2.0f) };

		// �|�X�g�G�t�F�N�g�}�e���A���ɐV�����p�����[�^��ǉ�����
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle, 
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::DrawGameArea), std::make_shared<DrawGameAreaCBufferData>(drawGameAreaCbufferData))
		);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::DrawGameArea, createdHandle);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.drawPriority			= 10000.0f;
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����
		m_drawGameAreaDrawFuncRunner = DX12GameManager::createComponent<PostEffectDrawFuncRunner>(GameObjectPtr(), createdHandle, drawFuncRunnerInitParam);
	}

	void PostEffectDrawFuncRunnerManager::createNotPostEffectDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				=  DX12GameManager::getSystemHandle(SystemPipeLineStateType::NotPostEffect);
		materialInitParam.useDescriptorHeapHandle				=  DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::NotPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::NotPostEffect, createdHandle);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����
		m_notPostEffectDrawFuncRunner = DX12GameManager::createComponent<PostEffectDrawFuncRunner>(GameObjectPtr(), createdHandle, drawFuncRunnerInitParam);
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectMonochromeDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectMonochrome);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Monochrome, createdHandle);

		// �ʏ�̃|�X�g�G�t�F�N�g�p�̒萔�o�b�t�@�̏����l�����߂�
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// �|�X�g�G�t�F�N�g�}�e���A���ɐV�����p�����[�^��ǉ�����
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����A�V�X�e��ID�ƌ��т���
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Monochrome, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectNegativeDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectNegative);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Negative, createdHandle);

		// �ʏ�̃|�X�g�G�t�F�N�g�p�̒萔�o�b�t�@�̏����l�����߂�
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// �|�X�g�G�t�F�N�g�}�e���A���ɐV�����p�����[�^��ǉ�����
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����A�V�X�e��ID�ƌ��т���
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Negative, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectAveragingBlurDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectAveragingBlur);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::AveragingBlur, createdHandle);

		// �ʏ�̃|�X�g�G�t�F�N�g�p�̒萔�o�b�t�@�̏����l�����߂�
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// �|�X�g�G�t�F�N�g�}�e���A���ɐV�����p�����[�^��ǉ�����
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����A�V�X�e��ID�ƌ��т���
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::AveragingBlur, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectEmbossDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectEmbossing);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Embossing, createdHandle);

		// �ʏ�̃|�X�g�G�t�F�N�g�p�̒萔�o�b�t�@�̏����l�����߂�
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// �|�X�g�G�t�F�N�g�}�e���A���ɐV�����p�����[�^��ǉ�����
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����A�V�X�e��ID�ƌ��т���
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Embossing, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectSharpnessDrawFuncRunner()
	{
		// �|�X�g�G�t�F�N�g�}�e���A�������ׂ̏������\���̂����
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectSharpness);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// �|�X�g�G�t�F�N�g�}�e���A�������
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ������|�X�g�G�t�F�N�g�}�e���A���ƃV�X�e��ID�����т���
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Sharpness, createdHandle);

		// �ʏ�̃|�X�g�G�t�F�N�g�p�̒萔�o�b�t�@�̏����l�����߂�
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// �|�X�g�G�t�F�N�g�}�e���A���ɐV�����p�����[�^��ǉ�����
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����ׂ̏������\���̂����
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// �|�X�g�G�t�F�N�g�`��R���|�[�l���g�����A�V�X�e��ID�ƌ��т���
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Sharpness, create(createdHandle, drawFuncRunnerInitParam));
	}
}