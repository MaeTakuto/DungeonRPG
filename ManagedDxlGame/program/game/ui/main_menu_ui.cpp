#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_graphic_manager.h"
#include "main_menu_ui.h"


// コンストラクタ
MainMenuUI::MainMenuUI(const tnl::Vector3& gpc_pos) {

	// 選択中のコマンドの初期化
	select_cmd_ = static_cast<eMainMenuCmd>(static_cast<int>(eMainMenuCmd::MC_BEGIN) + 1);

	std::string window_gpc_hdl_path = "graphics/SelectWindow.png";
	std::string select_cursor_gpc_hdl_path = "graphics/select_cursor01.png";

	// 画像のロード
	window_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(window_gpc_hdl_path);
	select_cursor_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(select_cursor_gpc_hdl_path);

	// コマンドウィンドウの幅、高さ取得
	GetGraphSize(window_gpc_hdl_, &window_gpc_hdl_width_, &window_gpc_hdl_height_);

	// コマンド文字の初期化
	cmd_str_[static_cast<int>(eMainMenuCmd::MC_GAMEOVER)] = "ゲーム終了";
	cmd_str_[static_cast<int>(eMainMenuCmd::MC_CANCEL)] = "もどる";

	// 表示位置の初期化
	window_pos_ = gpc_pos;
	cmd_pos_ = { window_pos_.x + STR_WIDTH_SPACE, window_pos_.y + STR_TOP_HEIGHT_SPACE, 0 };

	// 選択カーソル初期化
	select_cursor_pos_ = new tnl::Vector3[static_cast<int>(eMainMenuCmd::MC_END)];

	for (int i = 0; i < static_cast<int>(eMainMenuCmd::MC_END); ++i) {
		select_cursor_pos_[i] = { cmd_pos_.x - 20, cmd_pos_.y + (STR_TOP_HEIGHT_SPACE / 2) + (i * STR_HEIGHT_SPACE), 0 };
	}

}

// デストラクタ
MainMenuUI::~MainMenuUI() {

	delete[] select_cursor_pos_;
	select_cursor_pos_ = nullptr;
}

// アップデート関数
void MainMenuUI::update(float delta_time) {

	// 上下キーを押したとき
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP, eKeys::KB_W) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP)) {
		if (select_cmd_ == static_cast<eMainMenuCmd>(static_cast<int>(eMainMenuCmd::MC_BEGIN) + 1)) select_cmd_ = static_cast<eMainMenuCmd>(static_cast<int>(eMainMenuCmd::MC_END) - 1);
		else select_cmd_ = static_cast<eMainMenuCmd>(static_cast<int>(select_cmd_) - 1);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN, eKeys::KB_S) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN)) {
		if (select_cmd_ == static_cast<eMainMenuCmd>(static_cast<int>(eMainMenuCmd::MC_END) - 1)) select_cmd_ = static_cast<eMainMenuCmd>(static_cast<int>(eMainMenuCmd::MC_BEGIN) + 1);
		else select_cmd_ = static_cast<eMainMenuCmd>(static_cast<int>(select_cmd_) + 1);

	}

}

// 描画関数
void MainMenuUI::draw() {

	DrawGraph(window_pos_.x, window_pos_.y, window_gpc_hdl_, false);
	DrawRotaGraph(select_cursor_pos_[static_cast<int>(select_cmd_)].x, select_cursor_pos_[static_cast<int>(select_cmd_)].y, 0.85f, 0, select_cursor_gpc_hdl_, false);

	SetFontSize(STR_FONT_SIZE);
	for (int i = 0; i < static_cast<int>(eMainMenuCmd::MC_END); ++i) {
		DrawStringEx(cmd_pos_.x, cmd_pos_.y + (STR_HEIGHT_SPACE * i), -1, cmd_str_[i].c_str());
	}
}