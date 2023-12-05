#include "../common/gm_graphic_manager.h"
#include "two_choise_ui.h"



TwoChoiseUI::TwoChoiseUI(const tnl::Vector3& pos) {

	// コマンド文字の初期化
	cmd_str_[static_cast<int>(TwoChoiseCmd::TCC_YES)] = "はい";
	cmd_str_[static_cast<int>(TwoChoiseCmd::TCC_NO)] = "いいえ";

	std::string window_gpc_hdl_path = "graphics/SelectWindow.png";
	std::string select_cursor_gpc_hdl_path = "graphics/select_cursor01.png";

	// 画像のロード
	window_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(window_gpc_hdl_path);
	select_cursor_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(select_cursor_gpc_hdl_path);

	// コマンドウィンドウの幅、高さ取得
	// GetGraphSize(window_gpc_hdl_, &window_gpc_hdl_width_, &window_gpc_hdl_height_);

	// 表示位置の初期化
	window_pos_ = pos;
	cmd_pos_ = { window_pos_.x + STR_WIDTH_SPACE, window_pos_.y + STR_TOP_HEIGHT_SPACE, 0 };

	select_cursor_pos_ = new tnl::Vector3[static_cast<int>(TwoChoiseCmd::TCC_END)];

	for (int i = 0; i < static_cast<int>(TwoChoiseCmd::TCC_END); ++i) {
		select_cursor_pos_[i] = { cmd_pos_.x - 20, cmd_pos_.y + (STR_TOP_HEIGHT_SPACE / 2) + (i * STR_HEIGHT_SPACE), 0 };
	}
}

TwoChoiseUI::~TwoChoiseUI() {

	delete[] select_cursor_pos_;
	select_cursor_pos_ = nullptr;
}

void TwoChoiseUI::update(float delta_time) {

	// 上下キーを押したとき
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP, eKeys::KB_W) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP)) {
		if (select_cmd_ == static_cast<TwoChoiseCmd>(static_cast<int>(TwoChoiseCmd::TCC_BEGIN) + 1)) select_cmd_ = static_cast<TwoChoiseCmd>(static_cast<int>(TwoChoiseCmd::TCC_END) - 1);
		else select_cmd_ = static_cast<TwoChoiseCmd>(static_cast<int>(select_cmd_) - 1);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN, eKeys::KB_S) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN)) {
		if (select_cmd_ == static_cast<TwoChoiseCmd>(static_cast<int>(TwoChoiseCmd::TCC_END) - 1)) select_cmd_ = static_cast<TwoChoiseCmd>(static_cast<int>(TwoChoiseCmd::TCC_BEGIN) + 1);
		else select_cmd_ = static_cast<TwoChoiseCmd>(static_cast<int>(select_cmd_) + 1);
	}
}

void TwoChoiseUI::draw() {

	DrawGraph(window_pos_.x, window_pos_.y, window_gpc_hdl_, false);
	DrawRotaGraph(select_cursor_pos_[static_cast<int>(select_cmd_)].x, select_cursor_pos_[static_cast<int>(select_cmd_)].y, 0.85f, 0, select_cursor_gpc_hdl_, false);

	SetFontSize(STR_FONT_SIZE);
	for (int i = 0; i < static_cast<int>(TwoChoiseCmd::TCC_END); ++i) {
		DrawStringEx(cmd_pos_.x, cmd_pos_.y + (STR_HEIGHT_SPACE * i), -1, cmd_str_[i].c_str());
	}
}