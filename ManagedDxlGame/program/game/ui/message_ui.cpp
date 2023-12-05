#include "message_ui.h"
#include "../common/gm_graphic_manager.h"



// コンストラクタ
MessageUI::MessageUI(tnl::Vector3 pos, std::string& mess_str, bool anim_flg, bool sel_ui_flg) {

	std::string window_gpc_hdl_path = "graphics/MessageWindow.png";

	// 画像、文字などセット
	window_gpc_hdl_ = GraphicManager::GetInstance()->loadGraph(window_gpc_hdl_path);
	message_str_ = mess_str;

	// コマンドウィンドウの幅、高さ取得
	GetGraphSize(window_gpc_hdl_, &window_gpc_hdl_width_, &window_gpc_hdl_height_);

	// 表示位置の初期化
	window_pos_ = pos;
	mess_pos_ = { window_pos_.x + STR_WIDTH_SPACE, window_pos_.y + STR_TOP_HEIGHT_SPACE, 0 };
	two_choise_ui_pos_ = { window_pos_.x + window_gpc_hdl_width_ + 20, window_pos_.y, 0 };

	// 二択コマンドを表示
	if (sel_ui_flg) two_choise_ui_ = new TwoChoiseUI(two_choise_ui_pos_);

	anim_flg_ = anim_flg;
}

// デストラクタ
MessageUI::~MessageUI() {

	delete two_choise_ui_;
	two_choise_ui_ = nullptr;
}

// アップデート
void MessageUI::update(float delta_time) {

	sequence_.update(delta_time);
}

// 描画
void MessageUI::draw() {

	DrawGraph(window_pos_.x, window_pos_.y, window_gpc_hdl_, false);

	SetFontSize(STR_FONT_SIZE);
	DrawStringEx(mess_pos_.x, mess_pos_.y, -1, text_.c_str());

	if(two_choise_ui_) two_choise_ui_->draw();
}

// 表示タイプ選択
bool MessageUI::seqSelDrawType(const float delta_time) {

	if (anim_flg_) sequence_.change(&MessageUI::seqAnimMess);
	else sequence_.change(&MessageUI::seqDefault);

	return true;
}

// そのまま表示
bool MessageUI::seqDefault(const float delta_time) {

	text_ = message_str_;
	sequence_.change(&MessageUI::seqRun);

	return true;
}

// アニメーション表示
bool MessageUI::seqAnimMess(const float delta_time) {

	timer_ += delta_time;

	if (timer_ > STR_DRAW_INTERVEL) {
		text_ = message_str_.substr(0, count_);

		if (message_str_.length() > count_) {
			count_ += 2;
		}
		else {
			sequence_.change(&MessageUI::seqRun);
			mess_end_flg_ = true;
		}
		timer_ = 0.0f;
	}

	return true;
}

//
bool MessageUI::seqRun(const float delta_time) {

	if (two_choise_ui_) two_choise_ui_->update(delta_time);
	return true;
}