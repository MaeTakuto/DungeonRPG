#pragma once
#include "../base/ui_window_base.h"
#include "two_choise_ui.h"


// メッセージを表示するウィンドウクラス
class MessageUI : public WindowUIBase {
public:
	MessageUI(tnl::Vector3 pos, std::string& mess_str, bool anim_flg = false, bool sel_ui_flg = false);
	~MessageUI();

	void update(float delta_time) override;
	void draw() override;

	// 二択コマンドのアドレスを返す。
	inline TwoChoiseUI* getTwoChoiseUI() { return two_choise_ui_; }

	// メッセージが終わっているかどうか
	inline bool getMessEndFlg() { return mess_end_flg_; }

	// メッセージをセット
	inline void setMessage(std::string& mess) {
		count_ = 0;
		text_ = "";
		message_str_ = mess;
		sequence_.change(&MessageUI::seqAnimMess);
	}

private:
	const float STR_DRAW_INTERVEL = 0.02f;			// 文字アニメーションを表示する間隔

	TwoChoiseUI* two_choise_ui_ = nullptr;			// 二択コマンド

	tnl::Sequence<MessageUI> sequence_
		= tnl::Sequence<MessageUI>(this, &MessageUI::seqSelDrawType);

	std::string message_str_;						// 表示するメッセージ
	std::string text_;								// 描画する文字アニメーション

	int count_ = 0;									// 表示する文字のカウント

	float timer_ = 0.0f;							// 文字のアニメーション用タイマー

	bool anim_flg_ = false;							// 文字アニメーションにするかの判定
	bool sel_ui_flg_ = false;						// 二択コマンドを表示するかの判定
	bool mess_end_flg_ = false;						// 文字アニメーションが終了してるかの判定

	tnl::Vector3 two_choise_ui_pos_;				// 二択コマンドUI
	tnl::Vector3 mess_pos_;							// メッセージを表示するポジション

	bool seqSelDrawType(const float delta_time);	// 表示タイプの選択シーケンス
	bool seqDefault(const float delta_time);		// そのまま表示するシーケンス
	bool seqAnimMess(const float delta_time);		// 文字アニメーション処理シーケンス
	bool seqRun(const float delta_time);			// 二択コマンド表示、または何もしない

};