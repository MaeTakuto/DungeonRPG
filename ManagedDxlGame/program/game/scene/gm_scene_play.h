#pragma once
#include "../base/gm_scene_base.h"
#include "../gm_obj/gm_player_symbol.h"
#include "../gm_obj/gm_enemy_symbol.h"
#include "../gm_obj/gm_camera.h"
#include "../ui/menu_ui_commander.h"
#include "../base/gm_message_event_base.h"


class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	// �}�b�v�f�[�^�̏��
	enum class eMapData {
		GROUND = 0,					// ��
		WALL,						// ��
		GOAL,						// �o��
		PLAYER,						// �v���C���[
		ENEMY						// �G�l�~�[
	};

	static const int ENEMY_MAX_NUM = 8;								// �G�l�~�[�̍ő吶����

	void update(float delta_time) override;							// �V�[���v���C�̃A�b�v�f�[�g
	void draw() override;											// �V�[���v���C�`��

	inline bool isTransitionProcess() { return is_transition_process_; }

private:
	PlayerSymbol* player_symbol_ = nullptr;						// �v���C���[�V���{��
	std::list<EnemySymbol*> enemy_symbols_;						// �G�l�~�[

	Camera* camera_ = nullptr;									// �J����
	MenuUICommander* menu_ui_ = nullptr;						// ���j���[UI
	MessageEvent* mess_event_ = nullptr;						// �C�x���g

	tnl::Sequence<ScenePlay> sequence_ 
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::seqStartEvent);	// �v���C�V�[���̃V�[�P���X
	bool is_scene_change_ = false;								// 

	std::string scene_play_snd_path_ 
		= "sound/MusMUs/play_scene_bgm02.mp3";					// �v���C�V�[��BGM�p�X
	
	std::string enter_se_path_ = "sound/button_se.mp3";			// ����{�^��SE�p�X
	std::string select_se_path_ = "select_se.mp3";				// �I����SE�p�X
	std::string clear_trans_se_path_ = "sound/transition_se.mp3";		// �N���A���J��SE�p�X

	int scene_play_snd_;										// �v���C�V�[��BGM
	int enter_se_;												// ����{�^��SE
	int select_se_;												// �I����SE
	int clear_trans_se_;										// �N���A���J��SE

	std::string gpc_map_chip_hdls_pass_;						// �摜�p�X
	int map_chip_width_;										// �}�b�v�`�b�v�̕�
	int map_chip_height_;										// �}�b�v�`�b�v�̍���
	int map_chip_all_size_;										// �}�b�v�`�b�v�̑��t���[����
	int map_chip_x_size_;										// �}�b�v�`�b�v�̉��t���[����
	int map_chip_y_size_;										// �}�b�v�`�b�v�̏c�t���[����
	int* gpc_map_chip_hdls_;									// �摜�f�[�^�i�[

	std::string map_data_csv_pass_;								// �}�b�vCSV�f�[�^�̃p�X
	std::vector< std::vector< int > > mapchip_data_;			// �}�b�v�`�b�v�̃f�[�^
	std::vector< std::vector< int > > map_data_;				// �}�b�v�f�[�^ ( �G��v���C���[�Ȃǂ̈ʒu���܂� )

	bool seqStartEvent(const float delta_time);					// �X�^�[�g�C�x���g���Đ�����V�[�P���X
	bool seqPlayerAct(const float delta_time);					// �v���C���[�s���V�[�P���X
	bool seqEnemyAct(const float delta_time);					// �G�̍s���V�[�P���X
	bool seqCheckActEnd(const float delta_time);				// �v���C���[�A�G�̍s���I�����m�F����V�[�P���X
	bool seqMenuSelect(const float delta_time);					// ���j���[��ʑI���V�[�P���X
	bool seqChangeResultScene(const float delta_time);			// ���U���g�V�[���ɐ؂�ւ�
	bool seqChangeTitleScene(const float delta_time);			// 
	bool seqEndEvent(const float delta_time);					// �I���C�x���g�Đ��V�[�P���X

	void charaUpdate(float delta_time);							// �L�����N�^�[�A�b�v�f�[�g

public:

	// ======================================
	//      �}�b�v�̔ԍ���Ԃ�
	// ======================================
	inline int getMapNum(const tnl::Vector3& pos) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		return map_data_[y][x];
	}

	// ======================================
	//         �}�b�v��̃f�[�^�̍X�V
	// ======================================
	inline void setMapData(const tnl::Vector3& pos, int num) {
		int y = (int)pos.y;
		int x = (int)pos.x;

		map_data_[y][x] = num;
	}

	// ======================================
	//      �}�b�v�`�b�v�̔ԍ���Ԃ�
	// ======================================
	inline int getMapChipData(const tnl::Vector3& pos) {
		int x = pos.x;
		int y = pos.y;

		return mapchip_data_[y][x];
	}

	// ======================================
	//     ����̃G�l�~�[�̃A�h���X��n��
	// ======================================
	inline EnemySymbol* getTargetEnemy(const tnl::Vector3& pos) {

		for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
			if ((*it)->getPos().x == pos.x && (*it)->getPos().y == pos.y) {
				return *it;
			}
		}
		return nullptr;
	}

	// ===============================================
	//     �w�肳�ꂽ�L�����Ƀ_���[�W��^����
	// ===============================================
	inline void applyDamage(EnemySymbol* target, int damage) {

		tnl::DebugTrace("�G��%d�_���[�W�󂯂�\n", target->applyDamage(damage));

		if (target->isAlive() == false)
			for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end();) {
				if ((*it) == target) {
					tnl::DebugTrace("�G��|�����B\n");
					setMapData( (*it)->getPos(), getMapChipData( (*it)->getPos() ) );
					delete* it;
					it = enemy_symbols_.erase(it);
					break;
				}
				it++;
			}
	}

	inline void applyDamage(PlayerSymbol* target, int damage) {

		tnl::DebugTrace("�G��%d�_���[�W�󂯂�\n", target->applyDamage(damage));

		if (target->isAlive() == false) {

		}
	}

};
