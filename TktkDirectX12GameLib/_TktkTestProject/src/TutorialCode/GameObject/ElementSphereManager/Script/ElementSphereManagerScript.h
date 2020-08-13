#pragma once

#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../../ElementShape/VertexColor2DPolygonVertexData.h"

class ElementSphereManagerScript
	: public tktk::ComponentBase
{
public:

	ElementSphereManagerScript() = default;

public:

	void start();

	void update();

private:

	// 球体の頂点をゲームカメラから見た時の２次元座標で作れる最も大きな多角形を計算する
	void calculateElementShape(
		const std::vector<ElementShapeVertexData>& elementSpherePointArray,
		unsigned int maxXPosIndex,
		unsigned int minXPosIndex,
		unsigned int maxYPosIndex,
		unsigned int minYPosIndex
	);

	// 引数の２頂点を結ぶ線分を分割する時の頂点のインデックスを取得する
	std::forward_list<unsigned int> getSplitLineVertexIndexArray(
		const std::vector<ElementShapeVertexData>& elementSpherePointArray,
		std::forward_list<unsigned int>& notUseIndexList,
		const tktkMath::Vector2& previousPos,
		const tktkMath::Vector2& nextPos
	);

private:

	// 画面に表示する球体の上限数
	static constexpr unsigned int m_sphereMaxNum{ 8U };

private:

	// 球体を描画するオブジェクトのリスト
	std::forward_list<tktk::GameObjectPtr> m_sphereObjectList;

	// 作られる多角形の大まかな形を示すガイド
	tktk::GameObjectPtr m_elementShapeGuide;
};