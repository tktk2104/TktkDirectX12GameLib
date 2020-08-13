#include "ElementSphereManagerScript.h"

#include <limits>
#include <TktkMath/Random.h>
#include <TktkMath/MathHelper.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawer.h>

#include <TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h>

#include "../../ElementSphere/ElementSphere.h"
#include "../../ElementShapeGuide/ElementShapeGuide.h"
#include "../../../../Enum/_ResourceIds/ResourceIds.h"

#include "../../ElementShape/ElementShape.h"

// 画面に表示する球体の上限数
constexpr unsigned int ElementSphereManagerScript::m_sphereMaxNum;

void ElementSphereManagerScript::start()
{
	// 画面に表示する球体の数だけループする
	for (unsigned int i = 0; i < m_sphereMaxNum; i++)
	{
		// 何色の球体を出現させるかは乱数を使う
		tktkMath::Color sphereColor;

		switch (tktkMath::Random::getRandI(1, 3))
		{
		case 1: sphereColor = tktkMath::Color_v::red;	break;
		case 2: sphereColor = tktkMath::Color_v::green; break;
		case 3: sphereColor = tktkMath::Color_v::blue;	break;
		}

		// 出現座標も乱数を使う
		tktkMath::Vector3 pos = {
			tktkMath::Random::getRandF(-3.0f, 3.0f),
			tktkMath::Random::getRandF(-3.0f, 3.0f),
			tktkMath::Random::getRandF(-3.0f, 3.0f)
		};

		// 球体を出現させて管理リストに追加する
		m_sphereObjectList.push_front(ElementSphere::create(pos, sphereColor));
	}

	m_elementShapeGuide = ElementShapeGuide::create();
}

void ElementSphereManagerScript::update()
{
	// 死亡している球体オブジェクトをリストから削除する
	m_sphereObjectList.remove_if([](tktk::GameObjectPtr& node) { return node.expired(); });

	// スクリーン空間上の点と対応する色情報の配列
	std::vector<ElementShapeVertexData> elementSpherePointArray;

	// X座標が最大、最小の座標のインデックス
	unsigned int maxXPosIndex = 0U;
	unsigned int minXPosIndex = 0U;

	// Y座標が最大、最小の座標のインデックス
	unsigned int maxYPosIndex = 0U;
	unsigned int minYPosIndex = 0U;

	// 現在のインデックス
	unsigned int curIndex = 0U;

	// 画面上の球体描画オブジェクトを巡回
	for (const auto& sphereObject : m_sphereObjectList)
	{
		// 座標管理コンポーネント
		auto transform = sphereObject->getComponent<tktk::Transform3D>();

		// 画面サイズ
		const auto& screenSize = tktk::DX12GameManager::getWindowSize();

		// メインカメラのビュー行列
		const auto& viewMatrix = tktk::DX12GameManager::getViewMatrix(toInt(CameraId::Basic));

		// メインカメラのプロジェクション行列
		const auto& projectionMatrix = tktk::DX12GameManager::getProjectionMatrix(toInt(CameraId::Basic));

		// ビュー行列とプロジェクション行列で球体の中心座標を座標変換する
		auto calculatedScreenPos = transform->getLocalPosition() * viewMatrix * projectionMatrix;

		// ｚの値で各成分を割る
		calculatedScreenPos /= calculatedScreenPos.z;

		// スクリーン座標を求める
		calculatedScreenPos = calculatedScreenPos * tktkMath::Matrix4::createScreen(0.0f, 0.0f, screenSize.x, screenSize.y);

		// もしも頂点が画面外に出ていた場合、何もしない
		if (calculatedScreenPos.x < 0.0f || calculatedScreenPos.x > screenSize.x || calculatedScreenPos.y < 0.0f || calculatedScreenPos.y > screenSize.y) continue;

		// スクリーン空間上の点の配列を追加する
		ElementShapeVertexData tempData;
		tempData.position = tktkMath::Vector2(calculatedScreenPos.x, calculatedScreenPos.y);
		tempData.vertexColor = sphereObject->getComponent<tktk::SphereMeshDrawer>()->getAlbedoColor();
		elementSpherePointArray.push_back(tempData);

		// 座標それぞれの成分の最大、最小の座標のインデックスを更新する
		if (elementSpherePointArray.at(maxXPosIndex).position.x < calculatedScreenPos.x) maxXPosIndex = curIndex;
		if (elementSpherePointArray.at(minXPosIndex).position.x > calculatedScreenPos.x) minXPosIndex = curIndex;
		if (elementSpherePointArray.at(maxYPosIndex).position.y < calculatedScreenPos.y) maxYPosIndex = curIndex;
		if (elementSpherePointArray.at(minYPosIndex).position.y > calculatedScreenPos.y) minYPosIndex = curIndex;

		curIndex++;
	}

	// 頂点が１つも無かったら何もしない
	if (elementSpherePointArray.size() == 0U) return;

	// 球体の頂点をゲームカメラから見た時の２次元座標で作れる最も大きな多角形を計算する
	calculateElementShape(elementSpherePointArray, maxXPosIndex, minXPosIndex, maxYPosIndex, minYPosIndex);
}

// 球体の頂点をゲームカメラから見た時の２次元座標で作れる最も大きな多角形を計算する
void ElementSphereManagerScript::calculateElementShape(
	const std::vector<ElementShapeVertexData>& elementSpherePointArray,
	unsigned int maxXPosIndex,
	unsigned int minXPosIndex,
	unsigned int maxYPosIndex,
	unsigned int minYPosIndex
)
{
	// 多角形で使用していないインデックスのリスト
	std::forward_list<unsigned int> notUseIndexList;

	// スクリーン空間上の点の配列の要素分だけループする
	for (unsigned int i = 0; i < elementSpherePointArray.size(); i++)
	{
		// 現在の頂点がいずれの成分の最大、最小値で無ければ「最大、最小ではない頂点のインデックスのリスト」に追加する
		if (maxXPosIndex != i && minXPosIndex != i && maxYPosIndex != i && minYPosIndex != i)
		{
			notUseIndexList.push_front(i);
		}
	}

	// 作成する図形の頂点カラー込みの頂点情報の配列
	std::vector<ElementShapeVertexData> elementShapeVertexArray;

	// 直前に追加した頂点を持つ変数
	tktkMath::Vector2 previousAddPos = elementSpherePointArray.at(minXPosIndex).position;

	// 「ｘ座標が最小の座標」を最初の頂点として配列に追加する
	elementShapeVertexArray.push_back(elementSpherePointArray.at(minXPosIndex));

	// 「ｙ座標が最小の座標」が「ｘ座標が最小の座標」と同じでなければ
	if (minYPosIndex != minXPosIndex)
	{
		// 「ｘ座標が最小の座標」と「ｙ座標が最小の座標」を結ぶ線分を分割した時の頂点インデックスを取得する
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(minYPosIndex).position
		);

		// 取得した頂点インデックスに対応した頂点情報を作成する図形の頂点情報配列に追加する
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		// 「ｙ座標が最小の座標」を図形の頂点情報配列に追加する
		elementShapeVertexArray.push_back(elementSpherePointArray.at(minYPosIndex));

		// 「ｙ座標が最小の座標」を直前に追加した頂点にする
		previousAddPos = elementSpherePointArray.at(minYPosIndex).position;
	}

	// 「ｙ座標が最小の座標」、「ｘ座標が最小の座標」、「ｘ座標が最大の座標」が同じでなければ
	if (maxXPosIndex != minXPosIndex && maxXPosIndex != minYPosIndex)
	{
		// 「直前に判定した座標」と「ｘ座標が最大の座標」を結ぶ線分を分割した時の頂点インデックスを取得する
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(maxXPosIndex).position
		);

		// 取得した頂点インデックスに対応した頂点情報を作成する図形の頂点情報配列に追加する
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		// 「ｘ座標が最大の座標」を図形の頂点情報配列に追加する
		elementShapeVertexArray.push_back(elementSpherePointArray.at(maxXPosIndex));

		// 「ｘ座標が最大の座標」を直前に追加した頂点にする
		previousAddPos = elementSpherePointArray.at(maxXPosIndex).position;
	}

	// 「ｙ座標が最小の座標」、「ｘ座標が最小の座標」、「ｘ座標が最大の座標」、「ｙ座標が最大の座標」が同じでなければ
	if (maxYPosIndex != minXPosIndex && maxYPosIndex != minYPosIndex && maxYPosIndex != maxXPosIndex)
	{
		// 「直前に判定した座標」と「ｙ座標が最大の座標」を結ぶ線分を分割した時の頂点インデックスを取得する
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(maxYPosIndex).position
		);

		// 取得した頂点インデックスに対応した頂点情報を作成する図形の頂点情報配列に追加する
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		// 「ｘ座標が最大の座標」を図形の頂点情報配列に追加する
		elementShapeVertexArray.push_back(elementSpherePointArray.at(maxYPosIndex));

		// 「ｘ座標が最大の座標」を直前に追加した頂点にする
		previousAddPos = elementSpherePointArray.at(maxYPosIndex).position;
	}

	// 最後の１辺は条件不問で実行
	{
		// 「直前に判定した座標」と「ｘ座標が最小の座標」を結ぶ線分を分割した時の頂点インデックスを取得する
		auto result = getSplitLineVertexIndexArray(
			elementSpherePointArray,
			notUseIndexList,
			previousAddPos,
			elementSpherePointArray.at(minXPosIndex).position
		);

		// 取得した頂点インデックスに対応した頂点情報を作成する図形の頂点情報配列に追加する
		for (unsigned int index : result)
		{
			elementShapeVertexArray.push_back(elementSpherePointArray.at(index));
		}

		//// 「ｘ座標が最小の座標」を図形の頂点情報配列に追加する
		//elementShapeVertexArray.push_back(elementSpherePointArray.at(minXPosIndex));
	}

	// 線描画コンポーネント用の頂点を作る
	std::vector<tktkMath::Vector2> shapeGuideVertexArray;
	shapeGuideVertexArray.reserve(elementShapeVertexArray.size() + 1U);
	for (const auto& node : elementShapeVertexArray)
	{
		shapeGuideVertexArray.push_back(node.position);
	}
	//+
	shapeGuideVertexArray.push_back(elementShapeVertexArray.at(0).position);

	// 線描画コンポーネントの頂点を更新
	m_elementShapeGuide->getComponent<tktk::Line2DDrawer>()->setLineVertexArray(shapeGuideVertexArray);

	if (tktk::DX12GameManager::isTrigger(tktk::KeybordKeyType::key_Space) && elementShapeVertexArray.size() >= 3U)
	{
		ElementShape::create(elementShapeVertexArray);
	}
}

// 引数の２頂点を結ぶ線分を分割する時の頂点を取得する
std::forward_list<unsigned int> ElementSphereManagerScript::getSplitLineVertexIndexArray(
	const std::vector<ElementShapeVertexData>& elementSpherePointArray,
	std::forward_list<unsigned int>& notUseIndexList,
	const tktkMath::Vector2& previousPos,
	const tktkMath::Vector2& nextPos
)
{
	// 「previousPos->nextPos」のベクトル
	tktkMath::Vector2 line = nextPos - previousPos;

	// 指定した２頂点間に入る資格のある頂点のインデックスのリスト
	std::forward_list<unsigned int> insertVertexIndexList;

	// 作成する図形の頂点になっていない頂点のインデックスを巡回
	for (unsigned int index : notUseIndexList)
	{
		// 「previousPos->巡回中の頂点」のベクトル
		tktkMath::Vector2 firstToPoint = elementSpherePointArray.at(index).position - previousPos;

		// 指定した２頂点間に入る資格のある頂点をリストに追加する
		if (tktkMath::Vector2::cross(firstToPoint, line) > 0.0f) insertVertexIndexList.push_front(index);
	}

	// 指定した２頂点間に入る資格のある頂点が存在しなかったら空のリストを返す
	if (std::begin(insertVertexIndexList) == std::end(insertVertexIndexList)) return std::forward_list<unsigned int>();

	// 最も「previousPos->nextPos」の線分から遠い頂点のインデックス
	unsigned int mostFarVertexIndex = 0U;

	// 最も遠い「firstPos->nextPos」から「mostFarVertexIndex」の頂点の距離
	float mostFarDist = std::numeric_limits<float>::min();

	// 指定した２頂点間に入る資格のある頂点を巡回
	for (unsigned int index : insertVertexIndexList)
	{
		// 判定する頂点座標
		tktkMath::Vector2 chackVertex = elementSpherePointArray.at(index).position;

		// 指定した２頂点を結ぶ線分と判定する頂点座標がどれだけ離れているかを判定する処理
		{
			float a = nextPos.x - previousPos.x;
			float b = nextPos.y - previousPos.y;

			float a2 = a * a;
			float b2 = b * b;

			float r2 = a2 + b2;

			float tt = -(a * (previousPos.x - chackVertex.x) + b * (previousPos.y - chackVertex.y));

			float tempDist = 0.0f;

			if (tt < 0)
			{
				tempDist = std::sqrtf((previousPos.x - chackVertex.x) * (previousPos.x - chackVertex.x) + (previousPos.y - chackVertex.y) * (previousPos.y - chackVertex.y));
			}
			else if (tt > r2)
			{
				tempDist = std::sqrtf((nextPos.x - chackVertex.x) * (nextPos.x - chackVertex.x) + (nextPos.y - chackVertex.y) * (nextPos.y - chackVertex.y));
			}
			else
			{
				float f1 = a * (previousPos.y - chackVertex.y) - b * (previousPos.x - chackVertex.x);
				tempDist = std::sqrtf((f1 * f1) / r2);
			}

			if (mostFarDist < tempDist)
			{
				mostFarVertexIndex = index;
				mostFarDist = tempDist;
			}
		}
	}

	// 使用される頂点のインデックスのリスト
	std::forward_list<unsigned int> result;

	// 指定した２頂点間に入る資格があり、２頂点を結ぶ線分から最も遠い頂点を追加する
	result.push_front(mostFarVertexIndex);

	// 使用される頂点のインデックスを「多角形で使用していないインデックスのリスト」から削除する
	notUseIndexList.remove(mostFarVertexIndex);

	// 使用される頂点のインデックスを１つ目の頂点として再起し、結果を取得する
	auto childResult = getSplitLineVertexIndexArray(
					elementSpherePointArray,
					notUseIndexList,
					elementSpherePointArray.at(mostFarVertexIndex).position,
					nextPos
				);

	// 使用される頂点のインデックスのリストに再起処理の結果を足す
	result.splice_after(std::begin(result), std::move(childResult));

	return result;
	
}
