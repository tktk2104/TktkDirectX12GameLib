#ifndef SPHERE_MESH_DRAWER_H_
#define SPHERE_MESH_DRAWER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "SphereMeshDrawerUseResourceHandles.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// ���̃��b�V���`��R���|�[�l���g
	class SphereMeshDrawer
		: public ComponentBase
	{
	public:

		SphereMeshDrawer(float drawPriority, float radius, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const SphereMeshDrawerUseResourceHandles& useResourceHandles);
	
	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		const tktkMath::Color& getAlbedoColor() const;

		void setAlbedoColor(const tktkMath::Color& color);

	private:

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V
		void updateTransformCbuffer() const;

		// �V���h�E�}�b�v�p�̒萔�o�b�t�@�̍X�V
		void updateShadowMapCbuffer() const;

	private:

		float				m_radius;
		tktkMath::Vector3	m_localPosition;
		tktkMath::Color		m_albedoColor;
		unsigned int		m_createCopyTransformCbufferHandle		{ 0U };
		unsigned int		m_createCopyShadowMapCbufferHandle		{ 0U };
		unsigned int		m_createCopyMonoColorMeshCbufferHandle	{ 0U };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles;
		ComponentPtr<Transform3D>			m_transform{ };
	};
}
#endif // !SPHERE_MESH_DRAWER_H_