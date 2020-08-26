#ifndef SPHERE_MESH_DRAWER_H_
#define SPHERE_MESH_DRAWER_H_

#include <TktkMath/Structs/Color.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 球体メッシュ描画コンポーネント
	class SphereMeshDrawer
		: public ComponentBase
	{
	public:

		SphereMeshDrawer(float drawPriority, float radius, const tktkMath::Color& albedoColor , unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapHandle);
	
	public:

		void start();
		void draw() const;

	public:

		const tktkMath::Color& getAlbedoColor() const;

		void setAlbedoColor(const tktkMath::Color& color);

	private:

		float						m_radius;
		tktkMath::Color				m_albedoColor;
		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_cameraId;
		unsigned int				m_shadowMapCameraId;
		unsigned int				m_lightId;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !SPHERE_MESH_DRAWER_H_