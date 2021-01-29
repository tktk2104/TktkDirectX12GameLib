#ifndef SHT_2D_TITLE_SCENE_MENU_SCRIPT_H_
#define SHT_2D_TITLE_SCENE_MENU_SCRIPT_H_

#include <array>
#include <TktkDX12GameLib.h>

  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│自作のコンポーネントを作る際は「tktk::ComponentBase」を継承して下さい。
	│　シーンと同じように複数の関数がダックタイピング的に呼ばれます。
	│　どのような関数があるかは「ComponentBase.h」を参照して下さい。（「tktk::ComponentBase」をシングルクリック＆F12キーを入力）
	└────────────────────────────────────────────────────────────────────────────────────────*/

// タイトルメニュースクリプト
class Sht2D_TitleSceneMenuScript
	: public tktk::ComponentBase
{
public:

	Sht2D_TitleSceneMenuScript() = default;

public:

  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│下の２つの関数はフレームワーク側で自動で呼ばれる関数です。関数名を間違えると呼ばれないので注意しましょう。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	void start();
	void update();

private:

	void changeMenuState(int nextMenuState);

private:

	// メニューの項目の種類
	enum class MenuContantType
	{
		GameStart,
		GemeEnd,
	};

private:

	// メニュー項目の選択肢を変更する間隔（秒）
	constexpr static float ChangeMenuIntervalTimeSec{ 0.2f };

private:

	// メニュー項目の選択肢を変更する間隔のタイマー（秒）
	float m_changeMenuIntervalSecTimer	{ 0.0f };

	// 現在選択されているメニューの種類
	MenuContantType		m_curMenuState	{ MenuContantType::GameStart };

	// メニューの項目オブジェクトのポインタを管理する配列
	std::array<tktk::GameObjectPtr, 2U> m_menuContantObjectArray;
};
#endif // !SHT_2D_TITLE_SCENE_MENU_SCRIPT_H_