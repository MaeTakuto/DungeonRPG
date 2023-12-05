#pragma once
#include "../common/gm_manager.h"


// カメラクラス
class Camera {
public:
	Camera(const tnl::Vector3& target_pos);
	~Camera();

	void update(const tnl::Vector3& target_pos);								// アップデート

	inline tnl::Vector3 getPos() { return pos_; }							// カメラの位置を渡す

private:
	const float MAX_UP_POS = 8 * GameManager::GPC_DRAW_CHIP_SIZE;			// 画面上の最大位置
	const float MAX_DOWN_POS = 22 * GameManager::GPC_DRAW_CHIP_SIZE;		// 画面下の最大位置
	const float MAX_LEFT_POS = 12 * GameManager::GPC_DRAW_CHIP_SIZE;		// 画面左の最大位置
	const float MAX_RIGHT_POS = 30 * GameManager::GPC_DRAW_CHIP_SIZE;		// 画面右の最大位置

	tnl::Vector3 pos_;														// カメラの位置

};