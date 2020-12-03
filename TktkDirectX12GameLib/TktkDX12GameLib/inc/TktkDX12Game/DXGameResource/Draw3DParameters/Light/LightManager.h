#ifndef LIGHT_H_
#define LIGHT_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	class LightData;

	// �uLightData�v���Ǘ�����N���X
	class LightManager
	{
	public:

		explicit LightManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~LightManager();

	public:

		// �uLightData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ���C�g���̒萔�o�b�t�@���X�V����
		void updateLightCBuffer(size_t handle) const;

		// �w��̃��C�g�̊�����ݒ肷��
		void setAmbient(size_t handle, const tktkMath::Color& ambient);

		// �w��̃��C�g�̊g�U���ˌ���ݒ肷��
		void setDiffuse(size_t handle, const tktkMath::Color& diffuse);

		// �w��̃��C�g�̋��ʔ��ˌ���ݒ肷��
		void setSpeqular(size_t handle, const tktkMath::Color& speqular);

		// �w��̃��C�g�̍��W��ݒ肷��
		void setPosition(size_t handle, const tktkMath::Vector3& position);

	private:

		tktkContainer::ResourceContainer<LightData> m_lightArray;
	};
}
#endif // !LIGHT_H_