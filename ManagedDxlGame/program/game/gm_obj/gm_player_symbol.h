#pragma once
#include "../base/gm_chara_symbol_base.h"
#include "gm_camera.h"



// �v���C���[�V���{���N���X
class PlayerSymbol : public CharaSymbol {
public:
	PlayerSymbol();						// �R���X�g���N�^
	~PlayerSymbol();					// �f�X�g���N�^

	void update(float delta_time) override;							// �v���C���[�̃A�b�v�f�[�g
	void draw(const tnl::Vector3& camera_pos) override;				// �v���C���[�̕`��

	inline void setNextPos(tnl::Vector3& next_pos) { next_pos_ = next_pos; }		// �v���C���[�̎��̈ʒu���Z�b�g�B
	inline tnl::Vector3& getPos() override { return pos_; }							// �v���C���[�̌��݂̈ʒu��Ԃ��B
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// �v���C���[�̎��̈ʒu��Ԃ��B
	inline int getHP() { return parameter_.hp_; }									// �v���C���[��HP��Ԃ��B
	inline bool isAlive() override { return is_alive_; }							// �������Ă��邩��Ԃ��B
	inline void setIsCollision(bool col_flg) override { is_collision_ = col_flg; }	// �����蔻��̃t���O���Z�b�g�B
	inline eActState getActState() override { return act_state_; }					// �v���C���[�̍s����Ԃ�Ԃ�
	
	inline void beginAct() { act_state_ = eActState::IDLE; }						// �s�����J�n������B

	// ===================================
	//            �_���[�W����
	// ===================================
	inline int applyDamage(int damage) override {

		int sum_damage = damage;
		parameter_.hp_ -= sum_damage;

		// HP�� 0�ɂȂ�����
		if (parameter_.hp_ <= 0) is_alive_ = false;

		return sum_damage;
	}

private:
	tnl::Sequence<PlayerSymbol> sequence_ 
		= tnl::Sequence<PlayerSymbol>(this, &PlayerSymbol::seqIdle);				// �v���C���[�̍s�����

	int max_hp_ = 50;																// �ő�HP

	bool seqIdle(const float delta_time);											// �ҋ@���
	bool seqCheckWall(const float delta_time);										// �����蔻��̊m�F
	bool seqAttack(const float delta_time);											// �U��
	bool seqMove(const float delta_time);											// �ړ����
	bool seqStandby(const float delta_time);										// �ҋ@�s�����

};
