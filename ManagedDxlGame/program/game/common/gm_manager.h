#pragma once


class SceneBase;

// �t�F�[�h�C���A�A�E�g�̃J���[
enum class eFadeColor {
	BLACK,
	WHITE,
	MAX
};

class GameManager {
public:
	static constexpr int TITLE_FONT_SIZE = 100;								// �^�C�g���̃t�H���g�T�C�Y
	static constexpr int NORMAL_FONT_SIZE = 30;								// �m�[�}���̃t�H���g�T�C�Y

	static constexpr int GPC_CHIP_SIZE = 32;								// �摜�̃`�b�v�T�C�Y
	static constexpr int GPC_DRAW_CHIP_SIZE = GPC_CHIP_SIZE * 2;			// ��ʂɕ\������T�C�Y


	static GameManager* GetInstance(SceneBase* start_scene = nullptr);		// �Q�[���}�l�[�W���[�̃A�h���X��Ԃ�
	inline static void Destroy() { delete GetInstance(); }					// �A�h���X�̍폜

	void update(float delta_time);											// �Q�[���}�l�[�W���[�̍X�V
	void changeScene( SceneBase* next_scene, 
		eFadeColor fade_color = eFadeColor::BLACK, float fade_time = 2.0f);	// �V�[���̐؂�ւ����s��
	inline SceneBase* getSceneInstance() { return now_scene_; }				// �V�[���̃C���X�^���X��Ԃ��B
	inline bool isTransition() { return is_transition_; }				// �t�F�[�h���o�t���O��Ԃ��B

private:
	GameManager(SceneBase* start_scene);									// �R���X�g���N�^

	SceneBase* now_scene_ = nullptr;										// ���݂̃V�[��
	SceneBase* next_scene_ = nullptr;										// ���̃V�[��

	eFadeColor fade_color_ = eFadeColor::BLACK;								// �t�F�[�h�J���[

	std::string transition_gpc_hdl_path_[static_cast<int>(eFadeColor::MAX)];	// �t�F�[�h���o�摜�p�X

	int transition_gpc_hdl_[static_cast<int>(eFadeColor::MAX)];				// �t�F�[�h���o�摜
	float fade_time_ = 0.0f;												// �t�F�[�h���o����
	float fade_time_wait_ = 0.25f;											// �t�F�[�h���o�ҋ@����
	bool is_transition_ = false;											// �t�F�[�h���o�t���O

	tnl::Sequence<GameManager> sequence_
		= tnl::Sequence<GameManager>(this, &GameManager::seqRun);			// �Q�[���}�l�[�W���[�̏��

	bool seqRun(const float delta_time);									// �������Ȃ�
	bool seqTransOut(const float delta_time);								// �t�F�[�h�A�E�g
	bool seqWait(const float delta_time);									// �t�F�[�h���o�ҋ@
	bool seqTransIn(const float delta_time);								// �t�F�[�h�C��

};