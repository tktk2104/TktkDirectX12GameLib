#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeyboardInputGetter.h"

#include <algorithm>

namespace tktk
{
	KeyboardInputGetter::KeyboardInputGetter(LPDIRECTINPUT8 input, HWND handle)
	{
		// ���ꂼ��̃L�[���͏�������������
		m_curKeys = std::vector<unsigned char>(KeyDataArraySize, 0U);
		m_preKeys = std::vector<unsigned char>(KeyDataArraySize, 0U);

		// �f�t�H���g�̃V�X�e���L�[�{�[�h���g�p����ݒ�Ńf�o�C�X���쐬
		input->CreateDevice(GUID_SysKeyboard, &m_inputDevice, NULL);

		// �L�[�{�[�h�̓��̓f�o�C�X�ł��鎖��ݒ�
		m_inputDevice->SetDataFormat(&c_dfDIKeyboard);

		// �L�[�{�[�h�̔r��������Z�b�g����
		m_inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

		// ����J�n
		m_inputDevice->Acquire();
	}

	KeyboardInputGetter::~KeyboardInputGetter()
	{
		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void KeyboardInputGetter::update()
	{
		// �O�t���[���̓��͏󋵂��X�V����
		m_preKeys.swap(m_curKeys);

		// ���͂̎擾�����݂�
		HRESULT ret = m_inputDevice->GetDeviceState(KeyDataByteSize, m_curKeys.data());

		// ���͓��삪��~���Ă����ꍇ
		if (FAILED(ret))
		{
			// ������ĊJ���čĎ擾�����݂�
			m_inputDevice->Acquire();
			m_inputDevice->GetDeviceState(KeyDataByteSize, m_curKeys.data());
		}
	}

	bool KeyboardInputGetter::isPush(KeybordKeyType keyType) const
	{
		return (m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80);
	}

	bool KeyboardInputGetter::isTrigger(KeybordKeyType keyType) const
	{
		return ((m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80) && !(m_preKeys.at(static_cast<unsigned int>(keyType)) & 0x80));
	}
}