#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// キャラのパラメーター
struct Parameter {
	int hp_;
	int atk_;
};

// キャラの方向
enum class eDir {
	UP,			// 上
	DOWN,		// 下
	LEFT,		// 左
	RIGHT,		// 右
	MAX			// 最大値
};

// キャラの行動状態
enum class eActState {
	IDLE,
	ACT,
	END
};

// キャラクターシンボルの基底クラス
class CharaSymbol {
public:
	virtual ~CharaSymbol() {};

	virtual void update(float delta_time) = 0;
	virtual void draw(const tnl::Vector3& camera_pos) = 0;

	virtual tnl::Vector3& getPos() = 0;						// キャラの現在の位置を返す。
	virtual tnl::Vector3& getNextPos() = 0;					// キャラの次の位置を返す。
	virtual bool isAlive() = 0;								// キャラの生存しているか返す。
	virtual void setIsCollision(bool is_collision) = 0;		// キャラに当たり判定セット
	virtual int applyDamage(int damage) = 0;				// ダメージを与える。
	virtual eActState getActState() = 0;					// キャラの行動状態を返す。

protected:
	const int ANIM_IDLE = 1;					// 待機状態
	const float MOVE_SPEED = 0.25f;				// 移動速度
	const float IDLE_FRAME_TIME = 0.25f;		// 待機時のフレーム速度
	const float MOVE_FRAME_TIME = 0.05f;		// 移動時のフレーム速度

	Parameter parameter_;
	eDir dir_;						// キャラの方向

	tnl::Vector3 pos_;							// 位置情報
	tnl::Vector3 next_pos_;						// 移動先の位置

	std::vector< std::vector< int > >
		chara_anim_hdls_;						// キャラのアニメーション

	int anim_frame_;							// アニメーションフレーム
	float anim_time_count_;						// アニメーションの時間

	bool is_alive_;								// 生存判定
	bool is_collision_;							// 衝突判定

	eActState act_state_ = eActState::IDLE;

	std::vector< std::vector< tnl::CsvCell > > 
		chara_anim_hdls_data_;			// キャラクターのアニメーションデータ

};