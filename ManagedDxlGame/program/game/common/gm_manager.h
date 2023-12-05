#pragma once


class SceneBase;

// フェードイン、アウトのカラー
enum class eFadeColor {
	BLACK,
	WHITE,
	MAX
};

class GameManager {
public:
	static constexpr int TITLE_FONT_SIZE = 100;								// タイトルのフォントサイズ
	static constexpr int NORMAL_FONT_SIZE = 30;								// ノーマルのフォントサイズ

	static constexpr int GPC_CHIP_SIZE = 32;								// 画像のチップサイズ
	static constexpr int GPC_DRAW_CHIP_SIZE = GPC_CHIP_SIZE * 2;			// 画面に表示するサイズ


	static GameManager* GetInstance(SceneBase* start_scene = nullptr);		// ゲームマネージャーのアドレスを返す
	inline static void Destroy() { delete GetInstance(); }					// アドレスの削除

	void update(float delta_time);											// ゲームマネージャーの更新
	void changeScene( SceneBase* next_scene, 
		eFadeColor fade_color = eFadeColor::BLACK, float fade_time = 2.0f);	// シーンの切り替えを行う
	inline SceneBase* getSceneInstance() { return now_scene_; }				// シーンのインスタンスを返す。
	inline bool isTransition() { return is_transition_; }				// フェード演出フラグを返す。

private:
	GameManager(SceneBase* start_scene);									// コンストラクタ

	SceneBase* now_scene_ = nullptr;										// 現在のシーン
	SceneBase* next_scene_ = nullptr;										// 次のシーン

	eFadeColor fade_color_ = eFadeColor::BLACK;								// フェードカラー

	std::string transition_gpc_hdl_path_[static_cast<int>(eFadeColor::MAX)];	// フェード演出画像パス

	int transition_gpc_hdl_[static_cast<int>(eFadeColor::MAX)];				// フェード演出画像
	float fade_time_ = 0.0f;												// フェード演出時間
	float fade_time_wait_ = 0.25f;											// フェード演出待機時間
	bool is_transition_ = false;											// フェード演出フラグ

	tnl::Sequence<GameManager> sequence_
		= tnl::Sequence<GameManager>(this, &GameManager::seqRun);			// ゲームマネージャーの状態

	bool seqRun(const float delta_time);									// 何もしない
	bool seqTransOut(const float delta_time);								// フェードアウト
	bool seqWait(const float delta_time);									// フェード演出待機
	bool seqTransIn(const float delta_time);								// フェードイン

};