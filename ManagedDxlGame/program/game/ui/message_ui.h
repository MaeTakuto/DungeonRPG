#pragma once
#include "../base/ui_window_base.h"
#include "two_choise_ui.h"


// ���b�Z�[�W��\������E�B���h�E�N���X
class MessageUI : public WindowUIBase {
public:
	MessageUI(tnl::Vector3 pos, std::string& mess_str, bool anim_flg = false, bool sel_ui_flg = false);
	~MessageUI();

	void update(float delta_time) override;
	void draw() override;

	// ����R�}���h�̃A�h���X��Ԃ��B
	inline TwoChoiseUI* getTwoChoiseUI() { return two_choise_ui_; }

	// ���b�Z�[�W���I����Ă��邩�ǂ���
	inline bool getMessEndFlg() { return mess_end_flg_; }

	// ���b�Z�[�W���Z�b�g
	inline void setMessage(std::string& mess) {
		count_ = 0;
		text_ = "";
		message_str_ = mess;
		sequence_.change(&MessageUI::seqAnimMess);
	}

private:
	const float STR_DRAW_INTERVEL = 0.02f;			// �����A�j���[�V������\������Ԋu

	TwoChoiseUI* two_choise_ui_ = nullptr;			// ����R�}���h

	tnl::Sequence<MessageUI> sequence_
		= tnl::Sequence<MessageUI>(this, &MessageUI::seqSelDrawType);

	std::string message_str_;						// �\�����郁�b�Z�[�W
	std::string text_;								// �`�悷�镶���A�j���[�V����

	int count_ = 0;									// �\�����镶���̃J�E���g

	float timer_ = 0.0f;							// �����̃A�j���[�V�����p�^�C�}�[

	bool anim_flg_ = false;							// �����A�j���[�V�����ɂ��邩�̔���
	bool sel_ui_flg_ = false;						// ����R�}���h��\�����邩�̔���
	bool mess_end_flg_ = false;						// �����A�j���[�V�������I�����Ă邩�̔���

	tnl::Vector3 two_choise_ui_pos_;				// ����R�}���hUI
	tnl::Vector3 mess_pos_;							// ���b�Z�[�W��\������|�W�V����

	bool seqSelDrawType(const float delta_time);	// �\���^�C�v�̑I���V�[�P���X
	bool seqDefault(const float delta_time);		// ���̂܂ܕ\������V�[�P���X
	bool seqAnimMess(const float delta_time);		// �����A�j���[�V���������V�[�P���X
	bool seqRun(const float delta_time);			// ����R�}���h�\���A�܂��͉������Ȃ�

};