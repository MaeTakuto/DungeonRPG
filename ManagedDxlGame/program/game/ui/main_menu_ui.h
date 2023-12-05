#pragma once
#include "../base/ui_select_cmd_base.h"

// メインメニューのコマンド
enum class eMainMenuCmd {
	MC_BEGIN = -1,
	MC_GAMEOVER,
	MC_CANCEL,
	MC_END
};


// メニューの選択をするクラス
class MainMenuUI : public SelectUIBase {
public:
	MainMenuUI(const tnl::Vector3& pos);
	~MainMenuUI();

	void update(float delta_time) override;
	void draw() override;

	inline const eMainMenuCmd getSelectCmd() { return select_cmd_; }	// 選択中のコマンドを返す。

private:
	eMainMenuCmd select_cmd_;						// 選択中のコマンド 

	std::string cmd_str_[static_cast<int>(eMainMenuCmd::MC_END)];	// コマンドのテキスト

	tnl::Vector3 cmd_pos_;							// コマンドテキストの表示位置

};