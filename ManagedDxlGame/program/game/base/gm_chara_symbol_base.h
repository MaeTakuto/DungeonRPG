#pragma once
#include "../../dxlib_ext/dxlib_ext.h"


// �L�����̃p�����[�^�[
struct Parameter {
	int hp_;
	int atk_;
};

// �L�����̕���
enum class eDir {
	UP,			// ��
	DOWN,		// ��
	LEFT,		// ��
	RIGHT,		// �E
	MAX			// �ő�l
};

// �L�����̍s�����
enum class eActState {
	IDLE,
	ACT,
	END
};

// �L�����N�^�[�V���{���̊��N���X
class CharaSymbol {
public:
	virtual ~CharaSymbol() {};

	virtual void update(float delta_time) = 0;
	virtual void draw(const tnl::Vector3& camera_pos) = 0;

	virtual tnl::Vector3& getPos() = 0;						// �L�����̌��݂̈ʒu��Ԃ��B
	virtual tnl::Vector3& getNextPos() = 0;					// �L�����̎��̈ʒu��Ԃ��B
	virtual bool isAlive() = 0;								// �L�����̐������Ă��邩�Ԃ��B
	virtual void setIsCollision(bool is_collision) = 0;		// �L�����ɓ����蔻��Z�b�g
	virtual int applyDamage(int damage) = 0;				// �_���[�W��^����B
	virtual eActState getActState() = 0;					// �L�����̍s����Ԃ�Ԃ��B

protected:
	const int ANIM_IDLE = 1;					// �ҋ@���
	const float MOVE_SPEED = 0.25f;				// �ړ����x
	const float IDLE_FRAME_TIME = 0.25f;		// �ҋ@���̃t���[�����x
	const float MOVE_FRAME_TIME = 0.05f;		// �ړ����̃t���[�����x

	Parameter parameter_;
	eDir dir_;						// �L�����̕���

	tnl::Vector3 pos_;							// �ʒu���
	tnl::Vector3 next_pos_;						// �ړ���̈ʒu

	std::vector< std::vector< int > >
		chara_anim_hdls_;						// �L�����̃A�j���[�V����

	int anim_frame_;							// �A�j���[�V�����t���[��
	float anim_time_count_;						// �A�j���[�V�����̎���

	bool is_alive_;								// ��������
	bool is_collision_;							// �Փ˔���

	eActState act_state_ = eActState::IDLE;

	std::vector< std::vector< tnl::CsvCell > > 
		chara_anim_hdls_data_;			// �L�����N�^�[�̃A�j���[�V�����f�[�^

};