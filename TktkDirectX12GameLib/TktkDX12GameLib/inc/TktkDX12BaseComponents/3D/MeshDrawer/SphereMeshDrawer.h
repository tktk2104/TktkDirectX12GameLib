#ifndef SPHERE_MESH_DRAWER_H_
#define SPHERE_MESH_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "SphereMeshDrawerUseResourceHandles.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// 球体メッシュ描画コンポーネント
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

		// 座標変換用の定数バッファの更新
		void updateTransformCbuffer() const;

		// シャドウマップ用の定数バッファの更新
		void updateShadowMapCbuffer() const;

	private:

		float				m_radius;
		tktkMath::Vector3	m_localPosition;
		tktkMath::Color		m_albedoColor;
		size_t				m_createUploadTransformCbufferHandle		{ 0U };
		size_t				m_createUploadShadowMapCbufferHandle		{ 0U };
		size_t				m_createUploadMonoColorMeshCbufferHandle	{ 0U };
		SphereMeshDrawerUseResourceHandles	m_useResourceHandles;
		ComponentPtr<Transform3D>			m_transform{ };
	};
}
#endif // !SPHERE_MESH_DRAWER_H_