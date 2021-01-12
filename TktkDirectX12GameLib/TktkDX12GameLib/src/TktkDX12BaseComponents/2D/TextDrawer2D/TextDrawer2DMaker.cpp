#include "TktkDX12BaseComponents/2D/TextDrawer2D/TextDrawer2DMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    TextDrawer2DMaker TextDrawer2DMaker::m_self;

    TextDrawer2DMaker& TextDrawer2DMaker::makeStart(GameObjectPtr user)
    {
        // �ϐ�������������
        m_self = TextDrawer2DMaker();

        // �����̃��[�U�[��ݒ�
        m_self.m_user = user;

        // ���g�̎Q�Ƃ�Ԃ�
        return m_self;
    }

    ComponentPtr<TextDrawer2D> TextDrawer2DMaker::create()
    {
        // �R���|�[�l���g���쐬����
        return m_user->createComponent<TextDrawer2D>(
            m_drawPriority,
            m_fontHandle,
            m_initText,
            m_centerRate,
            m_blendRate
            );
    }

    TextDrawer2DMaker& TextDrawer2DMaker::drawPriority(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_drawPriority = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::fontHandle(size_t value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_fontHandle = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::fontId(ResourceIdCarrier value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_fontHandle = DX12GameManager::getFontHandle(value);
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::initText(const std::string& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_initText = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::centerRate(const tktkMath::Vector2& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_centerRate = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::blendRate(const tktkMath::Color& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_blendRate = value;
        return *this;
    }
}