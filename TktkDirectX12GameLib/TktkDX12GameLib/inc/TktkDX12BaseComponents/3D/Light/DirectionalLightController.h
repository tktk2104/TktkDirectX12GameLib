#ifndef DIRECTIONAL_LIGHT_CONTROLLER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_H_

#include <TktkMath/Structs/Vector3.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// �f�B���N�V���i�����C�g����R���|�[�l���g
	class DirectionalLightController
		: public ComponentBase
	{
	public:

		DirectionalLightController(
			unsigned int lightHandle,
			const tktkMath::Vector3& direction,
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular
		);

	public:

		void start();
		void afterCollide();

	public:

		// ���C�g�̕�����ݒ肷��
		void setDirection(const tktkMath::Vector3& direction);

		// ������ݒ肷��
		void setAmbient(const tktkMath::Color& ambient);

		// �g�U���ˌ���ݒ肷��
		void setDiffuse(const tktkMath::Color& diffuse);

		// ���ʔ��ˌ���ݒ肷��
		void setSpeqular(const tktkMath::Color& speqular);

	private:

		// ���C�g�����X�V����
		void updateLight();

	private:

		unsigned int				m_lightHandle;
		tktkMath::Vector3			m_direction;
		tktkMath::Color				m_ambient;
		tktkMath::Color				m_diffuse;
		tktkMath::Color				m_speqular;
	};
}
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_H_
