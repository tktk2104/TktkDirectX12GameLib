#ifndef LIGHT_H_
#define LIGHT_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "LightData.h"

namespace tktk
{
	// �uLightData�v���Ǘ�����N���X
	class Light
	{
	public:

		explicit Light(const tktkContainer::ResourceContainerInitParam& initParam);
		~Light() = default;

	public:

		// �uLightData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer(unsigned int handle) const;

		// �w��̃��C�g�̊�����ݒ肷��
		void setAmbient(unsigned int handle, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		void setDiffuse(unsigned int handle, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		void setSpeqular(unsigned int handle, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		void setPosition(unsigned int handle, const tktkMath::Vector3& position);

	private:

		tktkContainer::ResourceContainer<LightData> m_lightArray;
	};
}
#endif // !LIGHT_H_