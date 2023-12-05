#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../scene/gm_scene_title.h"
#include "menu_ui_commander.h"


// コンストラクタ
MenuUICommander::MenuUICommander() {

	main_menu_ui_ = new MainMenuUI(menu_ui_pos_);
}

// デストラクタ
MenuUICommander::~MenuUICommander() {

	delete main_menu_ui_;
	main_menu_ui_ = nullptr;

	delete message_ui_;
	message_ui_ = nullptr;
}

// アップデート
void MenuUICommander::update(float delta_time) {

	sequence_.update(delta_time);
}

// 描画
void MenuUICommander::draw() {

	if (main_menu_ui_) main_menu_ui_->draw();
	if (message_ui_) message_ui_->draw();
}

//// 待機画面
//bool MenuUICommander::seqIdle(const float delta_time) {
//
//	if ( tnl::Input::IsKeyDownTrigger( eKeys::KB_ESCAPE ) || tnl::Input::IsPadDownTrigger(ePad::KEY_3)) {
//		sequence_.change(&MenuUICommander::seqSelMainMenu);
//		ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
//		scene_play->setSelectUIFlg(true);
//	}
//
//	return true;
//}

// メインメニュー選択画面
bool MenuUICommander::seqSelMainMenu(const float delta_time) {

	if (main_menu_ui_ == nullptr) return false;
		main_menu_ui_->update(delta_time);

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {
		
		switch (main_menu_ui_->getSelectCmd())
		{
			// ゲーム終了の選択画面移動
		case eMainMenuCmd::MC_GAMEOVER:
			sequence_.change(&MenuUICommander::seqSelGameOverMenu);
			break;
			// ウィンドウを閉じる
		case eMainMenuCmd::MC_CANCEL:
			delete main_menu_ui_;
			main_menu_ui_ = nullptr;
			is_select_menu_ = false;
			break;
		}
	}

	return true;
}

// ゲーム終了の選択画面
bool MenuUICommander::seqSelGameOverMenu(const float delta_time) {
	if (sequence_.isStart()) {
		message_ui_ = new MessageUI(mess_ui_pos_, mess_str_, false, true);
	}

	if (message_ui_) {
		message_ui_->update(delta_time);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

			ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());

			switch (message_ui_->getTwoChoiseUI()->getSelectCmd())
			{
			// ゲームを終了
			case TwoChoiseCmd::TCC_YES:
				delete main_menu_ui_;
				main_menu_ui_ = nullptr;
				delete message_ui_;
				message_ui_ = nullptr;
				is_end_game_sign_ = true;
				break;
			case TwoChoiseCmd::TCC_NO:
				sequence_.change(&MenuUICommander::seqSelMainMenu);
				delete message_ui_;
				message_ui_ = nullptr;
				break;
			}
		}
	}

	return true;
}