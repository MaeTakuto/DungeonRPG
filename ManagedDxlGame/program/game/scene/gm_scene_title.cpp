#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_graphic_manager.h"
#include "../common/gm_sound_manager.h"
#include "gm_scene_play.h"
#include "gm_scene_title.h"


SceneTitle::SceneTitle() {

	// 背景ロード
	background = GraphicManager::GetInstance()->loadGraph(background_path_);

	// タイトルBGMロード
	title_snd_ = SoundManager::GetInstance()->loadSound(title_snd_path_);

	is_transition_process_ = false;

}

SceneTitle::~SceneTitle() {

	StopSoundMem(title_snd_);

	GraphicManager::GetInstance()->deleteGraph(background_path_);

	SoundManager::GetInstance()->deleteSound(title_snd_path_);
}

void SceneTitle::update(float delta_time) {

	sequence_.update(delta_time);
}

void SceneTitle::draw() {

	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, background, false);

	SetFontSize(GameManager::TITLE_FONT_SIZE);
	DrawStringEx( TITLE_LOGO_POS.x, TITLE_LOGO_POS.y, -1, TITLE_LOGO.c_str() );
}

bool SceneTitle::seqCheckTrans(const float delta_time) {

	if (!CheckSoundMem(title_snd_)) PlaySoundMem(title_snd_, DX_PLAYTYPE_LOOP, true);

	if (!GameManager::GetInstance()->isTransition()) {

		is_transition_process_ = true;
		sequence_.change(&SceneTitle::seqSelectMenu);
	}

	return true;
}

bool SceneTitle::seqSelectMenu(const float delta_time) {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDown(ePad::KEY_1)) {
		GameManager::GetInstance()->changeScene(new ScenePlay(), eFadeColor::BLACK);
		sequence_.change(&SceneTitle::seqCheckTrans);
	}

	return true;
}