#pragma once
#include "../base/gm_chara_symbol_base.h"



// �G�l�~�[�V���{���N���X
class EnemySymbol : public CharaSymbol {
public:
	EnemySymbol(tnl::Vector3 pos);
	~EnemySymbol();

	void update(float delta_time) override;
	void draw(const tnl::Vector3& camera_pos) override;

	inline tnl::Vector3& getPos() override { return pos_; }							// �G�l�~�[�̌��݂̈ʒu��Ԃ��B
	inline tnl::Vector3& getNextPos() override { return next_pos_; }				// �G�l�~�[�̎��̈ʒu��Ԃ��B
	inline bool isAlive() override { return is_alive_; }							// �������Ă��邩��Ԃ��B
	inline void setIsCollision(bool is_collision) override { is_collision_ = is_collision; }			// �����蔻��t���O�̃Z�b�g
	inline eActState getActState() override { return act_state_; }					// �G�l�~�[�̍s����Ԃ�Ԃ�

	// �s�����J�n������֐�
	inline void beginAct() { 
		act_state_ = eActState::ACT;

		// �ړ���̃|�W�V�����Z�b�g
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

	// �_���[�W����
	inline int applyDamage(int damage) override {

		int sum_damage = damage;
		parameter_.hp_ -= sum_damage;

		// HP�� 0�ɂȂ�����
		if (parameter_.hp_ <= 0) is_alive_ = false;

		return sum_damage;
	}

private:
	// �G�l�~�[�̍s��
	tnl::Sequence<EnemySymbol> sequence_ 
		= tnl::Sequence<EnemySymbol>(this, &EnemySymbol::seqIdle);

	bool seqIdle(const float delta_time);		// �ҋ@���
	bool seqAction(const float delta_time);		// �ړ����

	void move(const float delta_time);			// �ړ�����
	void dirChange();							// �����]������

};
