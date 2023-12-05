#pragma once
#include "../base/ui_select_cmd_base.h"


// コマンドの種類
enum class TwoChoiseCmd {
	TCC_BEGIN = -1,
	TCC_YES,
	TCC_NO,
	TCC_END
};

// 「はい」か「いいえ」を選択するクラス
class TwoChoiseUI : public SelectUIBase {
public:
	TwoChoiseUI(const tnl::Vector3& pos);
	~TwoChoiseUI();

	void update(float delta_time) override;
	void draw() override;

	inline const TwoChoiseCmd& getSelectCmd() { return select_cmd_; }		// 選択中のコマンドを返す。

private:

	TwoChoiseCmd select_cmd_;						// 選択中のコマンド

	// コマンドテキスト
	std::string cmd_str_[static_cast<int>(TwoChoiseCmd::TCC_END)];

	tnl::Vector3 cmd_pos_;							// コマンドテキストの表示位置

};