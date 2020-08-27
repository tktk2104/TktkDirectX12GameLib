#ifndef SPHERE_MESH_DRAWER_H_
#define SPHERE_MESH_DRAWER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 球体メッシュ描画コンポーネント
	class SphereMeshDrawer
		: public ComponentBase
	{
	public:

		SphereMeshDrawer(float drawPriority, float radius, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor , unsigned int cameraHandle, unsigned int shadowMapCameraHandle, unsigned int lightHandle, unsigned int useRtvDescriptorHeapHandle);
	
	public:

		void start();
		void draw() const;

	public:

		const tktkMath::Color& getAlbedoColor() const;

		void setAlbedoColor(const tktkMath::Color& color);

	private:

		float						m_radius;
		tktkMath::Vector3			m_localPosition;
		tktkMath::Color				m_albedoColor;
		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_cameraHandle;
		unsigned int				m_shadowMapCameraHandle;
		unsigned int				m_lightHandle;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !SPHERE_MESH_DRAWER_H_