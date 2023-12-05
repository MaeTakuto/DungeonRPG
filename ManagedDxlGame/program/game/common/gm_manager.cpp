#include "../../dxlib_ext/dxlib_ext.h"
#include "../gm_main.h"
#include "gm_manager.h"
#include "gm_graphic_manager.h"
#include "../base/gm_scene_base.h"


// コンストラクタ
GameManager::GameManager(SceneBase* start_scene) {
	now_scene_ = start_scene;
	transition_gpc_hdl_path_[static_cast<int>(eFadeColor::BLACK)] = "graphics/black.bmp";
	transition_gpc_hdl_path_[static_cast<int>(eFadeColor::WHITE)] = "graphics/white.bmp";

	for (int i = static_cast<int>(eFadeColor::BLACK); i < static_cast<int>(eFadeColor::MAX); ++i) {
		transition_gpc_hdl_[i] = GraphicManager::GetInstance()->loadGraph(transition_gpc_hdl_path_[i]);
	}
}

// ゲームマネージャーのアドレスを返す
GameManager* GameManager::GetInstance(SceneBase* start_scene) {

	static GameManager* instance = nullptr;

	if (!instance) {
		instance = new GameManager(start_scene);
	}
	return instance;
}

// アップデート
void GameManager::update(float delta_time) {

	if (now_scene_) now_scene_->update(delta_time);
	if (now_scene_) now_scene_->draw();

	sequence_.update(delta_time);
}

// シーンの切り替えをセット
void GameManager::changeScene( SceneBase* next_scene, eFadeColor fade_color, float fade_time ) {
	next_scene_ = next_scene;
	fade_color_ = fade_color;
	fade_time_ = fade_time;
	sequence_.change(&GameManager::seqTransOut);
	is_transition_ = true;
}

// 何もしない
bool GameManager::seqRun(const float delta_time) {

	return true;
}

// 
bool GameManager::seqTransOut(const float delta_time) {
	int alpha = (sequence_.getProgressTime() / fade_time_ * 255.0f);
	if (alpha >= 255) {
		sequence_.change(&GameManager::seqWait);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, transition_gpc_hdl_[static_cast<int>(fade_color_)], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	return true;
}

// 
bool GameManager::seqWait(const float delta_time) {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, transition_gpc_hdl_[static_cast<int>(fade_color_)], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (sequence_.getProgressTime() <= fade_time_wait_) return true;

	if (now_scene_->isTransitionProcess() == false) return true;

	delete now_scene_;
	now_scene_ = nullptr;
	now_scene_ = next_scene_;

	sequence_.change(&GameManager::seqTransIn);

	return true;
}

// シーンを切り替える
bool GameManager::seqTransIn(const float delta_time) {
	int alpha = 255 - (sequence_.getProgressTime() / fade_time_ * 255.0f);
	if (alpha <= 0) {
		sequence_.change(&GameManager::seqRun);
		is_transition_ = false;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, transition_gpc_hdl_[static_cast<int>(fade_color_)], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	return true;
}