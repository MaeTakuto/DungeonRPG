#include <time.h>
#include <string>
#include <vector>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "common/gm_manager.h"
#include "scene/gm_scene_title.h"



//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));

	// インスタンス生成、最初のシーンをセット
	GameManager::GetInstance( new SceneTitle() );

}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	// ゲームマネージャーのアップデート
	GameManager::GetInstance()->update(delta_time);

}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
