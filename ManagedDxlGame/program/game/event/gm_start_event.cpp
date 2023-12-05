#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_start_event.h"



// コンストラクタ
StartEvent::StartEvent() {

	mess_ = new std::string[MESS_MAX];

	mess_[0] = "道に迷ってしまったようだ";
	mess_[1] = "出口を見つけなければ";

	mess_ui_ = new MessageUI(tnl::Vector3(300, 400, 0), mess_[mess_count_], true, false);

	mess_count_ = 0;
	end_flg_ = false;
}

// デストラクタ
StartEvent::~StartEvent() {

	delete[] mess_;
	mess_ = nullptr;

	delete mess_ui_;
	mess_ui_ = nullptr;
}

// アップデート
void StartEvent::update(float delta_time) {

	if (mess_ui_) mess_ui_->update(delta_time);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDown(ePad::KEY_1)) {

		mess_count_++;

		if (mess_count_ < MESS_MAX) {
			// 次のメッセージをセット
			if (mess_ui_) mess_ui_->setMessage(mess_[mess_count_]);
		}
		else {
			end_flg_ = true;
		}
	}
}

// 描画
void StartEvent::draw() {

	if (mess_ui_) mess_ui_->draw();
}