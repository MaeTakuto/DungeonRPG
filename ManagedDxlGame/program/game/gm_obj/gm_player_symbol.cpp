#include "../../dxlib_ext/dxlib_ext.h"
#include "../common/gm_manager.h"
#include "../common/gm_animation_manager.h"
#include "../scene/gm_scene_play.h"
#include "gm_player_symbol.h"


// �R���X�g���N�^
PlayerSymbol::PlayerSymbol() {

	// �L�����̉摜�f�[�^�̃��[�h
	chara_anim_hdls_data_ = tnl::LoadCsv("csv/player_gpc_pass.csv");
	
	// std::vector�̏ꍇ 
	chara_anim_hdls_.resize( static_cast<int>( eDir::MAX ) );

	for (int i = 0; i < static_cast<int>(eDir::MAX); ++i) {

		chara_anim_hdls_[i].resize( chara_anim_hdls_data_[1][i].getInt() );

		// �A�j���[�V�����̎擾
		chara_anim_hdls_[i] = AnimationManager::GetInstance()->loadAnimation(
			chara_anim_hdls_data_[0][i].getString(),
			chara_anim_hdls_data_[1][i].getInt(),
			chara_anim_hdls_data_[2][i].getInt(),
			chara_anim_hdls_data_[3][i].getInt(),
			GameManager::GPC_CHIP_SIZE,
			GameManager::GPC_CHIP_SIZE );
	}
	
	// �ʒu���ȂǏ�����
	pos_ = { 20, 6, 0 };
	next_pos_ = pos_;
	is_collision_ = false;
	is_alive_ = true;
	anim_frame_ = ANIM_IDLE;
	anim_time_count_ = 0.0f;

	// �p�����[�^�[�̏�����
	parameter_.hp_ = max_hp_;
	parameter_.atk_ = 10;

	dir_ = eDir::DOWN;
}

// �f�X�g���N�^
PlayerSymbol::~PlayerSymbol() {
	
}

// �A�b�v�f�[�g
void PlayerSymbol::update(float delta_time) {

	sequence_.update(delta_time);
}

// �`��
void PlayerSymbol::draw(const tnl::Vector3& camera_pos) {

	// �`��ʒu����
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

// �ҋ@���
bool PlayerSymbol::seqIdle(const float delta_time) {

	anim_time_count_ += delta_time;

	// �A�j���[�V�����t���[���X�V
	if (anim_time_count_ > IDLE_FRAME_TIME) {
		anim_frame_++;
		anim_frame_ %= chara_anim_hdls_data_[1][static_cast<int>(dir_)].getInt();
		anim_time_count_ = 0.0f;
	}

	if (act_state_ != eActState::IDLE) return true;

	// �V�t�g�L�[���������Ƃ�
	if (tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)) {

		// �����]��
		if (tnl::Input::IsKeyDown(eKeys::KB_A)) dir_ = eDir::LEFT;
		if (tnl::Input::IsKeyDown(eKeys::KB_D)) dir_ = eDir::RIGHT;
		if (tnl::Input::IsKeyDown(eKeys::KB_W)) dir_ = eDir::UP;
		if (tnl::Input::IsKeyDown(eKeys::KB_S)) dir_ = eDir::DOWN;
	}
	else {
		// A�L�[�i���ړ��j
		if (tnl::Input::IsKeyDown(eKeys::KB_A) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {
			next_pos_.x -= 1;
			dir_ = eDir::LEFT;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}

		// D�L�[�i�E�ړ��j
		if (tnl::Input::IsKeyDown(eKeys::KB_D) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) {
			next_pos_.x += 1;
			dir_ = eDir::RIGHT;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}

		// W�L�[�i��ړ��j
		if (tnl::Input::IsKeyDown(eKeys::KB_W) /* || tnl::Input::IsPadDown(ePad::KEY_UP) */) {
			next_pos_.y -= 1;
			dir_ = eDir::UP;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}

		// S�L�[�i���ړ��j
		if (tnl::Input::IsKeyDown(eKeys::KB_S) || tnl::Input::IsPadDown(ePad::KEY_DOWN)) {
			next_pos_.y += 1;
			dir_ = eDir::DOWN;
			sequence_.change(&PlayerSymbol::seqCheckWall);
			act_state_ = eActState::ACT;
			return true;
		}
	}

	// �U���i�X�y�[�X�{�^���j
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		act_state_ = eActState::ATTACK;
		sequence_.change(&PlayerSymbol::seqAttack);
		anim_frame_ = ANIM_IDLE;
	}

	// �ҋ@�iz�L�[�A���{�^���j
	if (tnl::Input::IsKeyDown(eKeys::KB_Z) || tnl::Input::IsPadDown(ePad::KEY_2)) {
		sequence_.change(&PlayerSymbol::seqCheckWall);
		act_state_ = eActState::ACT;
		return true;
	}
	
	return true;
}

// �����蔻��̊m�F
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

// �U����̃}�b�v���̊m�F
bool PlayerSymbol::seqAttack(const float delta_time) {

	tnl::Vector3 attack_pos = pos_;

	if (dir_ == eDir::UP) attack_pos.y -= 1;
	if (dir_ == eDir::DOWN) attack_pos.y += 1;
	if (dir_ == eDir::LEFT) attack_pos.x -= 1;
	if (dir_ == eDir::RIGHT) attack_pos.x += 1;

	auto scene_play = static_cast<ScenePlay*>(GameManager::GetInstance()->getSceneInstance());

	auto target = scene_play->getTargetEnemy(attack_pos);

	// �G�����Ȃ����
	if (!target)
	{
		act_state_ = eActState::END;
		sequence_.change(&PlayerSymbol::seqIdle);
		return true;
	}
	// �U��
	scene_play->applyDamage(target, parameter_.atk_);

	act_state_ = eActState::END;
	sequence_.change(&PlayerSymbol::seqIdle);

	return true;
}

// �ړ����
bool PlayerSymbol::seqMove(const float delta_time) {

	anim_time_count_ += delta_time;

	// �A�j���[�V�����t���[���X�V
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

// �ҋ@�s�����
bool PlayerSymbol::seqStandby(const float delta_time) {
	
	act_state_ = eActState::END;
	sequence_.change(&PlayerSymbol::seqIdle);

	return true;
}
