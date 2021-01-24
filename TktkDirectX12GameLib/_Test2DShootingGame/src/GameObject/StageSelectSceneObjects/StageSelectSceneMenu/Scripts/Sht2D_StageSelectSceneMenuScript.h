#ifndef SHT_2D_STAGE_SELECT_SCENE_MENU_SCRIPT_H_
#define SHT_2D_STAGE_SELECT_SCENE_MENU_SCRIPT_H_

#include <array>
#include <TktkDX12GameLib.h>

// ステージセレクトメニュースクリプト
class Sht2D_StageSelectSceneMenuScript
	: public tktk::ComponentBase
{
public:

	Sht2D_StageSelectSceneMenuScript() = default;

public:

	void start();
	void update();

private:

	void changeMenuState(int nextMenuState);

private:

	// メニューの項目の種類
	enum class MenuContantType
	{
		Stage1,
		Stage2,
		Stage3,
		Back,
	};

private:

	// メニュー項目の選択肢を変更する間隔（秒）
	constexpr static float ChangeMenuIntervalTimeSec{ 0.2f };

private:

	// メニュー項目の選択肢を変更する間隔のタイマー（秒）
	float m_changeMenuIntervalSecTimer{ 0.0f };

	// 現在選択されているメニューの種類
	MenuContantType		m_curMenuState{ MenuContantType::Stage1 };

	// メニューの項目オブジェクトのポインタを管理する配列
	std::array<tktk::GameObjectPtr, 4U> m_menuContantObjectArray;
};
#endif // !SHT_2D_STAGE_SELECT_SCENE_MENU_SCRIPT_H_