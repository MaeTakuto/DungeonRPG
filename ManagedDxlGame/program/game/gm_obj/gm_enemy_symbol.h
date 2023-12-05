#pragma once
#include "../base/gm_chara_symbol_base.h"



// エネミーシンボルクラス
class EnemySymbol : public CharaSymbol {
public:
	EnemySymbol(tnl::Vector3 pos);
	~EnemySymbol();

	void update(float delta_time) override;
	void draw(const tnl::Vector3& camera_pos) override;

	inline tnl::Vector3& getPos() override { return pos_; }							// エネミーの現在の位置を返す。
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// エネミーの次の位置を返す。
	inline bool isAlive() override { return is_alive_; }							// 生存しているかを返す。
	inline void setIsCollision(bool is_collision) override { is_collision_ = is_collision; }			// 当たり判定フラグのセット
	inline eActState getActState() override { return act_state_; }					// エネミーの行動状態を返す

	// 行動を開始させる関数
	inline void beginAct() { 
		act_state_ = eActState::ACT;

		// 移動先のポジションセット
		switch (dir_) {
		case eDir::DOWN:
			next_pos_.y += 1;
			break;
		case eDir::UP:
			next_pos_.y -= 1;
			break;
		case eDir::LEFT:
			next_pos_.x -= 1;
			break;
		case eDir::RIGHT:
			next_pos_.x += 1;
			break;
		}

		sequence_.change(&EnemySymbol::seqAction);
	}

	// ダメージ処理
	inline int applyDamage(int damage) override {

		int sum_damage = damage;
		parameter_.hp_ -= sum_damage;

		// HPが 0になった時
		if (parameter_.hp_ <= 0) is_alive_ = false;

		return sum_damage;
	}

private:
	// エネミーの行動
	tnl::Sequence<EnemySymbol> sequence_ 
		= tnl::Sequence<EnemySymbol>(this, &EnemySymbol::seqIdle);

	bool seqIdle(const float delta_time);		// 待機状態
	bool seqAction(const float delta_time);		// 移動状態

	void move(const float delta_time);			// 移動処理
	void dirChange();							// 方向転換処理

};
