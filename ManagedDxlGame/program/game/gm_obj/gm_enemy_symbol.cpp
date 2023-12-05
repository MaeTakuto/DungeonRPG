#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_animation_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_enemy_symbol.h"


// �R���X�g���N�^
EnemySymbol::EnemySymbol(tnl::Vector3 pos) {
	// �L�����̉摜�f�[�^���[�h
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/enemy_gpc_pass.csv");

	// �A�j���[�V�����̎擾
	chara_anim_hdls_.resize(static_cast<int>(eDir::MAX));

	for (int i = 0; i < static_cast<int>(eDir::MAX); ++i) {

		chara_anim_hdls_[i].resize(chara_anim_hdls_data_[1][i].getInt());

		chara_anim_hdls_[i] = AnimationManager::GetInstance()->loadAnimation(
			chara_anim_hdls_data_[0][i].getString(),
			chara_anim_hdls_data_[1][i].getInt(),
			chara_anim_hdls_data_[2][i].getInt(),
			chara_anim_hdls_data_[3][i].getInt(),
			GameManager::GPC_CHIP_SIZE,
			GameManager::GPC_CHIP_SIZE);
	}

	tnl::DebugTrace("pass = %x\n", chara_anim_hdls_[1][1]);

	// �ʒu�Ȃǂ̏�����
	pos_ = pos;
	next_pos_ = pos_;
	is_alive_ = true;
	is_collision_ = false;
	anim_frame_ = ANIM_IDLE;
	anim_time_count_ = 0.0f;

	// �p�����[�^�[�̏�����
	parameter_.hp_ = 30;
	parameter_.atk_ = 10;

	dir_ = eDir::DOWN;

}

// �f�X�g���N�^
EnemySymbol::~EnemySymbol() {

}

// �A�b�v�f�[�g
void EnemySymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// �`��
void EnemySymbol::draw(const tnl::Vector3& camera_pos) {

	tnl::Vector3 draw_pos = tnl::Vector3( pos_.x * GameManager::GPC_DRAW_CHIP_SIZE, pos_.y * GameManager::GPC_DRAW_CHIP_SIZE, 0 )
		- camera_pos + tnl::Vector3( DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0 );

	DrawExtendGraph(draw_pos.x, draw_pos.y, draw_pos.x + GameManager::GPC_DRAW_CHIP_SIZE, draw_pos.y + GameManager::GPC_DRAW_CHIP_SIZE,
		chara_anim_hdls_[static_cast<int>(dir_)][anim_frame_], true);
	// DrawRotaGraph(draw_pos.x, draw_pos.y, 2.0f, 0, chara_anim_hdls_[static_cast<int>(dir_)][ANIM_IDLE], true);
}

// �ҋ@���
bool EnemySymbol::seqIdle(const float delta_time) {

	anim_time_count_ += delta_time;

	// �A�j���[�V�����t���[���X�V
	if (anim_time_count_ > IDLE_FRAME_TIME) {
		anim_frame_++;
		anim_frame_ %= chara_anim_hdls_data_[1][static_cast<int>(dir_)].getInt();
		anim_time_count_ = 0.0f;
	}

	return true;
}

// �s�����
bool EnemySymbol::seqAction(const float delta_time) {

	// �������Ă��邩�ǂ���
	if (is_collision_) {
		dirChange();
		is_collision_ = false;
		next_pos_ = pos_;
	}
	else {
		move(delta_time);
	}

	return true;
}

// �ړ�
void EnemySymbol::move(const float delta_time) {

	anim_time_count_ += delta_time;

	// �A�j���[�V�����t���[���X�V
	if (anim_time_count_ > MOVE_FRAME_TIME) {
		anim_frame_++;
		anim_frame_ %= chara_anim_hdls_data_[1][static_cast<int>(dir_)].getInt();
		anim_time_count_ = 0.0f;
	}

	if (abs(next_pos_.x - pos_.x) > 0.1f || abs(next_pos_.y - pos_.y) > 0.1f) {
		pos_ += (next_pos_ - pos_) * MOVE_SPEED;
	}
	else {
		pos_ = next_pos_;
		act_state_ = eActState::END;
		sequence_.change(&EnemySymbol::seqIdle);
	}
}

// �����]������
void EnemySymbol::dirChange() {

	tnl::Vector3 d_pos[ static_cast<int>( eDir::MAX ) ];

	d_pos[0] = { 0, -1, 0 };
	d_pos[1] = { 0, 1, 0 };
	d_pos[2] = { -1, 0, 0 };
	d_pos[3] = { 1, 0, 0 };

	ScenePlay* scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());
	std::vector<eDir> dir;

	// ��������
	for (int i = 0; i < static_cast<int>(eDir::MAX); ++i) {
		tnl::Vector3 temp_pos = pos_ + d_pos[i];
		if (scene_play->getMapNum(temp_pos) == 0) {
			dir.emplace_back(static_cast<eDir>(i));
		}
	} 

	// �ړ��ł���������Ȃ��ꍇ
	if (dir.size() == 0) {
		act_state_ = eActState::END;
		sequence_.change(&EnemySymbol::seqIdle);
	}
	int r = GetRand(static_cast<int>(dir.size() - 1));
	tnl::DebugTrace("r = %d\n", r);

	dir_ = dir[r];

	act_state_ = eActState::END;

	sequence_.change(&EnemySymbol::seqIdle);

}