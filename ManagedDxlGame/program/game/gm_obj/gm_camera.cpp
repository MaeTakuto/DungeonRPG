#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_player_symbol.h"
#include "gm_camera.h"



// コンストラクタ
Camera::Camera(const tnl::Vector3& target_pos) {

	pos_ = tnl::Vector3(target_pos.x * GameManager::GPC_DRAW_CHIP_SIZE, target_pos.y * GameManager::GPC_DRAW_CHIP_SIZE, 0);

	if (pos_.y < MAX_UP_POS) pos_.y = MAX_UP_POS;
	if (pos_.y > MAX_DOWN_POS) pos_.y = MAX_DOWN_POS;
	if (pos_.x < MAX_LEFT_POS) pos_.x = MAX_LEFT_POS;
	if (pos_.x > MAX_RIGHT_POS) pos_.x = MAX_RIGHT_POS;
}

// デストラクタ
Camera::~Camera() {

}

// アップデート
void Camera::update(const tnl::Vector3& target_pos) {

	pos_ = tnl::Vector3(target_pos.x * GameManager::GPC_DRAW_CHIP_SIZE, target_pos.y * GameManager::GPC_DRAW_CHIP_SIZE, 0);

	if (pos_.y < MAX_UP_POS) pos_.y = MAX_UP_POS;
	if (pos_.y > MAX_DOWN_POS) pos_.y = MAX_DOWN_POS;
	if (pos_.x < MAX_LEFT_POS) pos_.x = MAX_LEFT_POS;
	if (pos_.x > MAX_RIGHT_POS) pos_.x = MAX_RIGHT_POS;

}