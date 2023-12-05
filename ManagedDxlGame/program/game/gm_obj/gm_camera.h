#pragma once
#include "../common/gm_manager.h"


// �J�����N���X
class Camera {
public:
	Camera(const tnl::Vector3& target_pos);
	~Camera();

	void update(const tnl::Vector3& target_pos);								// �A�b�v�f�[�g

	inline tnl::Vector3 getPos() { return pos_; }							// �J�����̈ʒu��n��

private:
	const float MAX_UP_POS = 8 * GameManager::GPC_DRAW_CHIP_SIZE;			// ��ʏ�̍ő�ʒu
	const float MAX_DOWN_POS = 22 * GameManager::GPC_DRAW_CHIP_SIZE;		// ��ʉ��̍ő�ʒu
	const float MAX_LEFT_POS = 12 * GameManager::GPC_DRAW_CHIP_SIZE;		// ��ʍ��̍ő�ʒu
	const float MAX_RIGHT_POS = 30 * GameManager::GPC_DRAW_CHIP_SIZE;		// ��ʉE�̍ő�ʒu

	tnl::Vector3 pos_;														// �J�����̈ʒu

};