#pragma once
#include "../base/gm_scene_base.h"
#include "../gm_obj/gm_player_symbol.h"
#include "../gm_obj/gm_enemy_symbol.h"
#include "../gm_obj/gm_camera.h"
#include "../ui/menu_ui_commander.h"
#include "../base/gm_message_event_base.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	// マップデータの状態
	enum class eMapData {
		GROUND = 0,					// 床
		WALL,						// 壁
		GOAL,						// 出口
		PLAYER,						// プレイヤー
		ENEMY						// エネミー
	};

	static const int ENEMY_MAX_NUM = 8;								// エネミーの最大生成数

	void update(float delta_time) override;							// シーンプレイのアップデート
	void draw() override;											// シーンプレイ描画

	inline bool isTransitionProcess() { return is_transition_process_; }

private:
	PlayerSymbol* player_symbol_ = nullptr;						// プレイヤーシンボル
	std::list<EnemySymbol*> enemy_symbols_;						// エネミー

	Camera* camera_ = nullptr;									// カメラ
	MenuUICommander* menu_ui_ = nullptr;						// メニューUI
	MessageEvent* mess_event_ = nullptr;						// イベント

	tnl::Sequence<ScenePlay> sequence_ 
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::seqStartEvent);	// プレイシーンのシーケンス
	bool is_scene_change_ = false;								// 

	std::string scene_play_snd_path_ 
		= "sound/MusMUs/play_scene_bgm02.mp3";					// プレイシーンBGMパス
	
	std::string enter_se_path_ = "sound/button_se.mp3";			// 決定ボタンSEパス
	std::string select_se_path_ = "select_se.mp3";				// 選択時SEパス
	std::string clear_trans_se_path_ = "sound/transition_se.mp3";		// クリア時遷移SEパス

	int scene_play_snd_;										// プレイシーンBGM
	int enter_se_;												// 決定ボタンSE
	int select_se_;												// 選択時SE
	int clear_trans_se_;										// クリア時遷移SE

	std::string gpc_map_chip_hdls_pass_;						// 画像パス
	int map_chip_width_;										// マップチップの幅
	int map_chip_height_;										// マップチップの高さ
	int map_chip_all_size_;										// マップチップの総フレーム数
	int map_chip_x_size_;										// マップチップの横フレーム数
	int map_chip_y_size_;										// マップチップの縦フレーム数
	int* gpc_map_chip_hdls_;									// 画像データ格納

	std::string map_data_csv_pass_;								// マップCSVデータのパス
	std::vector< std::vector< int > > mapchip_data_;			// マップチップのデータ
	std::vector< std::vector< int > > map_data_;				// マップデータ ( 敵やプレイヤーなどの位置を含む )

	bool seqStartEvent(const float delta_time);					// スタートイベントを再生するシーケンス
	bool seqPlayerAct(const float delta_time);					// プレイヤー行動シーケンス
	bool seqEnemyAct(const float delta_time);					// 敵の行動シーケンス
	bool seqCheckActEnd(const float delta_time);				// プレイヤー、敵の行動終了を確認するシーケンス
	bool seqMenuSelect(const float delta_time);					// メニュー画面選択シーケンス
	bool seqChangeResultScene(const float delta_time);			// リザルトシーンに切り替え
	bool seqChangeTitleScene(const float delta_time);			// 
	bool seqEndEvent(const float delta_time);					// 終了イベント再生シーケンス

	void charaUpdate(float delta_time);							// キャラクターアップデート

public:

	// ======================================
	//      マップの番号を返す
	// ======================================
	inline int getMapNum(const tnl::Vector3& pos) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		return map_data_[y][x];
	}

	// ======================================
	//         マップ上のデータの更新
	// ======================================
	inline void setMapData(const tnl::Vector3& pos, int num) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		map_data_[y][x] = num;
	}

	// ======================================
	//      マップチップの番号を返す
	// ======================================
	inline int getMapChipData(const tnl::Vector3& pos) {
		int x = pos.x;
		int y = pos.y;

		return mapchip_data_[y][x];
	}

	// ======================================
	//     特定のエネミーのアドレスを渡す
	// ======================================
	inline EnemySymbol* getTargetEnemy(const tnl::Vector3& pos) {

		for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
			if ((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y) {
				return *it;
			}
		}
		return nullptr;
	}

	// ===============================================
	//     指定されたキャラにダメージを与える
	// ===============================================
	inline void applyDamage(EnemySymbol* target, int damage) {

		tnl::DebugTrace("敵は%dダメージ受けた\n", target->applyDamage(damage));

		if (target->isAlive() == false)
			for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end();) {
				if ((*it) == target) {
					tnl::DebugTrace("敵を倒した。\n");
					setMapData( (*it)->getPos(), getMapChipData( (*it)->getPos() ) );
					delete* it;
					it = enemy_symbols_.erase(it);
					break;
				}
				it++;
			}
	}

	inline void applyDamage(PlayerSymbol* target, int damage) {

		tnl::DebugTrace("敵は%dダメージ受けた\n", target->applyDamage(damage));

		if (target->isAlive() == false) {

		}
	}

};
