#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	BillboardDrawerMaker BillboardDrawerMaker::m_self;

	BillboardDrawerMaker& BillboardDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BillboardDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BillboardDrawer> BillboardDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<BillboardDrawer>(
			m_billboardMaterialHandle,
			m_centerRate,
			m_blendRate,
			m_clippingLeftTopPos,
			m_clippingSize
			);
	}

	BillboardDrawerMaker& BillboardDrawerMaker::billboardMaterialHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_billboardMaterialHandle = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::billboardMaterialId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(value);
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_centerRate = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::blendRate(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_blendRate = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::clippingLeftTopPos(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_clippingLeftTopPos = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::notClippingUseHandle(size_t billboarddMaterialHandle)
	{
		// �r���{�[�h�n���h������e�N�X�`���T�C�Y���擾���A�N���b�s���O�T�C�Y�ɐݒ肷��
		const auto& textureSize = DX12GameManager::getBillboardTextureSize(billboarddMaterialHandle);
		m_clippingSize = { textureSize.x, textureSize.y };
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::notClippingUseId(ResourceIdCarrier billboarddMaterialId)
	{
		// �r���{�[�hId����e�N�X�`���T�C�Y���擾���A�N���b�s���O�T�C�Y�ɐݒ肷��
		const auto& textureSize = DX12GameManager::getBillboardTextureSize(DX12GameManager::getBillboardMaterialHandle(billboarddMaterialId));
		m_clippingSize = { textureSize.x, textureSize.y };
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::clippingSize(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_clippingSize = value;
		return *this;
	}
}