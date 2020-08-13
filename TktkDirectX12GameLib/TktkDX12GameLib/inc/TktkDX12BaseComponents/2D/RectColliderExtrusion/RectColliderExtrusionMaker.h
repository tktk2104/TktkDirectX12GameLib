#ifndef RECT_COLLIDER_EXTRUSION_MAKER_H_
#define RECT_COLLIDER_EXTRUSION_MAKER_H_

#include "RectColliderExtrusion.h"

namespace tktk
{
	class RectColliderExtrusionMaker
	{
	private: /* プライベートコンストラクタ達 */

		RectColliderExtrusionMaker() = default;
		RectColliderExtrusionMaker(const RectColliderExtrusionMaker& other) = default;
		RectColliderExtrusionMaker& operator = (const RectColliderExtrusionMaker& other) = default;

	public:

		// インスタンス作成開始
		static RectColliderExtrusionMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<RectColliderExtrusion> create();

	private:

		// 自身のポインタ
		static RectColliderExtrusionMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_MAKER_H_