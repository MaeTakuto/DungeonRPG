#pragma once
#include "../base/ui_select_cmd_base.h"

// ���C�����j���[�̃R�}���h
enum class eMainMenuCmd {
	MC_BEGIN = -1,
	MC_GAMEOVER,
	MC_CANCEL,
	MC_END
};


// ���j���[�̑I��������N���X
class MainMenuUI : public SelectUIBase {
public:
	MainMenuUI(const tnl::Vector3& pos);
	~MainMenuUI();

	void update(float delta_time) override;
	void draw() override;

	inline const eMainMenuCmd getSelectCmd() { return select_cmd_; }	// �I�𒆂̃R�}���h��Ԃ��B

private:
	eMainMenuCmd select_cmd_;						// �I�𒆂̃R�}���h 

	std::string cmd_str_[static_cast<int>(eMainMenuCmd::MC_END)];	// �R�}���h�̃e�L�X�g

	tnl::Vector3 cmd_pos_;							// �R�}���h�e�L�X�g�̕\���ʒu

};