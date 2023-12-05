#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../ui/message_ui.h"


class MessageEvent {
public:
	virtual ~MessageEvent() {};

	virtual void update(float delta_time) = 0;			// �A�b�v�f�[�g
	virtual void draw() = 0;							// �`��

	virtual bool getEndFlg() = 0;						// ���b�Z�[�W�I���t���O��Ԃ��B

protected:
	int mess_count_;								// �\�����镶�����̃J�E���g

	bool end_flg_;									// ���b�Z�[�W�̕\���A�I���t���O

	std::string* mess_;								// ���b�Z�[�W
	MessageUI* mess_ui_;							// ���b�Z�[�WUI

};