#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_animation_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_player_symbol.h"


// コンストラクタ
PlayerSymbol::PlayerSymbol() {

	// キャラの画像データのロード
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/player_gpc_pass.csv");
	
	// std::vectorの場合 
	chara_anim_hdls_.resize( static_cast<int>( eDir::MAX ) );

	for (int i = 0; i < static_cast<int>(eDir::MAX); ++i) {

		chara_anim_hdls_[i].resize( chara_anim_hdls_data_[1][i].getInt() );

		// アニメーションの取得
		chara_anim_hdls_[i] = AnimationManager::GetInstance()->loadAnimation(
			chara_anim_hdls_data_[0][i].getString(),
			chara_anim_hdls_data_[1][i].getInt(),
			chara_anim_hdls_data_[2][i].getInt(),
			chara_anim_hdls_data_[3][i].getInt(),
			GameManager::GPC_CHIP_SIZE,
			GameManager::GPC_CHIP_SIZE );
	}
	
	// 位置情報など初期化
	pos_ = { 20, 6, 0 };
	next_pos_ = pos_;
	is_collision_ = false;
	is_alive_ = true;
	anim_frame_ = ANIM_IDLE;
	anim_time_count_ = 0.0f;

	// パラメーターの初期化
	parameter_.hp_ = max_hp_;
	parameter_.atk_ = 10;

	dir_ = eDir::DOWN;
}

// デストラクタ
PlayerSymbol::~PlayerSymbol() {
	
}

// アップデート
void PlayerSymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// 描画
void PlayerSymbol::draw(const tnl::Vector3& camera_pos) {

	// 描画位置調整
	tnl::Vector3 draw_pos = tnl::Vector3( pos_.x * GameManager::GPC_DRAW_CHIP_SIZE, pos_.y * GameManager::GPC_DRAW_CHIP_SIZE, 0 ) 
		- camera_pos + tnl::Vector3( DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0 );

	DrawExtendGraph(draw_pos.x, draw_pos.y, draw_pos.x + GameManager::GPC_DRAW_CHIP_SIZE, draw_pos.y + GameManager::GPC_DRAW_CHIP_SIZE,
		chara_anim_hdls_[static_cast<int>(dir_)][anim_frame_], true);
	// DrawRotaGraph( draw_pos.x, draw_pos.y, 2.0f, 0, chara_anim_hdls_[ static_cast<int>( dir_ ) ][ ANIM_IDLE ], true );

	/*
	SetFontSize(DEFAULT_FONT_SIZE);
	DrawStringEx(10, 10, -1, "pos_x = %.2f, pos_y = %.2f", pos_.x, pos_.y);
	*/
}

// 待機状態
bool PlayerSymbol::seqIdle(const float delta_time) {

	anim_time_count_ += delta_time;

	// アニメーションフレーム更新
	if (anim_time_count_ > IDLE_FRAME_TIME) {
		anim_frame_++;
		anim_frame_ %= chara_anim_hdls_data_[1][static_cast<int>(dir_)].getInt();
		anim_time_count_ = 0.0f;
	}

	if (act_state_ != eActState::IDLE) return true;

	// シフトキーを押したとき
	if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

		// 方向転換
		if (tnl::Input::IsKeyDown(eKeys::KB_A)) dir_ = eDir::LEFT;
		if (tnl::Input::IsKeyDown(eKeys::KB_D)) dir_ = eDir::RIGHT;
		if (tnl::Input::IsKeyDown(eKeys::KB_W)) dir_ = eDir::UP;
		if (tnl::Input::IsKeyDown(eKeys::KB_S)) dir_ = eDir::DOWN;
	}
	else {
		// Aキー（左移動）
		if (tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {
			next_pos_.x -= 1;
			dir_ = eDir::LEFT;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}

		// Dキー（右移動）
		if (tnl::Input::IsKeyDown(eKeys::KB_D) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) {
			next_pos_.x += 1;
			dir_ = eDir::RIGHT;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}

		// Wキー（上移動）
		if (tnl::Input::IsKeyDown(eKeys::KB_W) /* || tnl::Input::IsPadDown(ePad::KEY_UP) */) {
			next_pos_.y -= 1;
			dir_ = eDir::UP;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}

		// Sキー（下移動）
		if (tnl::Input::IsKeyDown(eKeys::KB_S) || tnl::Input::IsPadDown(ePad::KEY_DOWN)) {
			next_pos_.y += 1;
			dir_ = eDir::DOWN;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}
	}

	// 攻撃（スペースボタン）
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		act_state_ = eActState::ATTACK;
		sequence_.change(&PlayerSymbol::seqAttack);
		anim_frame_ = ANIM_IDLE;
	}

	// 待機（zキー、□ボタン）
	if (tnl::Input::IsKeyDown(eKeys::KB_Z) || tnl::Input::IsPadDown(ePad::KEY_2)) {
		sequence_.change(&PlayerSymbol::seqCheckWall);
		act_state_ = eActState::ACT;
		return true;
	}
	
	return true;
}

// 当たり判定の確認
bool PlayerSymbol::seqCheckWall(const float delta_time) {

	if (is_collision_) {
		sequence_.change(&PlayerSymbol::seqIdle);
		next_pos_ = pos_;
		act_state_ = eActState::IDLE;
		is_collision_ = false;
	}
	else {
		sequence_.change(&PlayerSymbol::seqMove);
	}

	return true;
}

// 攻撃先のマップ情報の確認
bool PlayerSymbol::seqAttack(const float delta_time) {

	tnl::Vector3 attack_pos = pos_;

	if (dir_ == eDir::UP) attack_pos.y -= 1;
	if (dir_ == eDir::DOWN) attack_pos.y += 1;
	if (dir_ == eDir::LEFT) attack_pos.x -= 1;
	if (dir_ == eDir::RIGHT) attack_pos.x += 1;

	auto scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());

	auto target = scene_play->getTargetEnemy(attack_pos);

	// 敵がいなければ
	if (!target)
	{
		act_state_ = eActState::END;
		sequence_.change(&PlayerSymbol::seqIdle);
		return true;
	}
	// 攻撃
	scene_play->applyDamage(target, parameter_.atk_);

	act_state_ = eActState::END;
	sequence_.change(&PlayerSymbol::seqIdle);

	return true;
}

// 移動状態
bool PlayerSymbol::seqMove(const float delta_time) {

	anim_time_count_ += delta_time;

	// アニメーションフレーム更新
	if (anim_time_count_ > MOVE_FRAME_TIME) {
		anim_frame_++;
		anim_frame_ %= chara_anim_hdls_data_[1][static_cast<int>(dir_)].getInt();
		anim_time_count_ = 0.0f;
	}

	if ( abs(next_pos_.x - pos_.x) > 0.1f || abs(next_pos_.y - pos_.y) > 0.1f ) {
		//tnl::DebugTrace("pos_ = %.2f\n", pos_.length());
		//tnl::DebugTrace("next_pos_ - pos_ = %.2f\n", next_pos_.length() - pos_.length());
		pos_ += (next_pos_ - pos_) * MOVE_SPEED;
	}
	else {
		act_state_ = eActState::END;
		pos_ = next_pos_;
		sequence_.change(&PlayerSymbol::seqIdle);
	}
	
	return true;
}

// 待機行動状態
bool PlayerSymbol::seqStandby(const float delta_time) {
	
	act_state_ = eActState::END;
	sequence_.change(&PlayerSymbol::seqIdle);

	return true;
}
