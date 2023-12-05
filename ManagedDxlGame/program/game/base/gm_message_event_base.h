#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../ui/message_ui.h"


class MessageEvent {
public:
	virtual ~MessageEvent() {};

	virtual void update(float delta_time) = 0;			// アップデート
	virtual void draw() = 0;							// 描画

	virtual bool getEndFlg() = 0;						// メッセージ終了フラグを返す。

protected:
	int mess_count_;								// 表示する文字数のカウント

	bool end_flg_;									// メッセージの表示、終了フラグ

	std::string* mess_;								// メッセージ
	MessageUI* mess_ui_;							// メッセージUI

};