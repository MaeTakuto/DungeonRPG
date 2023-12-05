#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_graphic_manager.h"
#include "gm_scene_title.h"
#include "gm_scene_result.h"



// コンストラクタ
SceneResult::SceneResult() {

	background_ = GraphicManager::GetInstance()->loadGraph("graphics/GameClear.JPG");
	is_transition_process_ = false;
}

// デストラクタ
SceneResult::~SceneResult() {

}

// アップデート
void SceneResult::update(float delta_time) {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1) ) {
		GameManager::GetInstance()->changeScene( new SceneTitle() );
		is_transition_process_ = true;
	}
}

// 描画
void SceneResult::draw() {


	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, background_, false);
	/*
	SetFontSize(GameManager::TITLE_FONT_SIZE);
	DrawStringEx(350, 100, -1, "ゲームクリア");
	*/
}