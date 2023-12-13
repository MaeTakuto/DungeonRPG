#pragma once
#include "../base/gm_chara_symbol_base.h"
#include "gm_camera.h"



// プレイヤーシンボルクラス
class PlayerSymbol : public CharaSymbol {
public:
	PlayerSymbol();						// コンストラクタ
	~PlayerSymbol();					// デストラクタ

	void update(float delta_time) override;							// プレイヤーのアップデート
	void draw(const tnl::Vector3& camera_pos) override;				// プレイヤーの描画

	inline void setNextPos(tnl::Vector3& next_pos) { next_pos_ = next_pos; }		// プレイヤーの次の位置をセット。
	inline tnl::Vector3& getPos() override { return pos_; }							// プレイヤーの現在の位置を返す。
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// プレイヤーの次の位置を返す。
	inline int getHP() { return parameter_.hp_; }									// プレイヤーのHPを返す。
	inline bool isAlive() override { return is_alive_; }							// 生存しているかを返す。
	inline void setIsCollision(bool col_flg) override { is_collision_ = col_flg; }	// 当たり判定のフラグをセット。
	inline eActState getActState() override { return act_state_; }					// プレイヤーの行動状態を返す
	
	inline void beginAct() { act_state_ = eActState::IDLE; }						// 行動を開始させる。

	// ===================================
	//            ダメージ処理
	// ===================================
	inline int applyDamage(int damage) override {

		int sum_damage = damage;
		parameter_.hp_ -= sum_damage;

		// HPが 0になった時
		if (parameter_.hp_ <= 0) is_alive_ = false;

		return sum_damage;
	}

private:
	tnl::Sequence<PlayerSymbol> sequence_ 
		= tnl::Sequence<PlayerSymbol>(this, &PlayerSymbol::seqIdle);				// プレイヤーの行動状態

	int max_hp_ = 50;																// 最大HP

	bool seqIdle(const float delta_time);											// 待機状態
	bool seqCheckWall(const float delta_time);										// 当たり判定の確認
	bool seqAttack(const float delta_time);											// 攻撃
	bool seqMove(const float delta_time);											// 移動状態
	bool seqStandby(const float delta_time);										// 待機行動状態

};
