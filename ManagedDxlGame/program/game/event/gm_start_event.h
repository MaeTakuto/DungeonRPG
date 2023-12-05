#pragma once
#include "../base/gm_message_event_base.h"


class StartEvent : public MessageEvent {
public:
	StartEvent();
	~StartEvent();

	void update(float delta_time) override;
	void draw() override;

	inline bool getEndFlg() { return end_flg_; }		// �C�x���g�I���̔���t���O��Ԃ��B

private:
	const int MESS_MAX = 2;								// ���b�Z�[�W�̍s

};