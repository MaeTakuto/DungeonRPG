#include <vector>
#include "../../dxlib_ext/dxlib_ext.h"
#include "../event/gm_start_event.h"
#include "../common/gm_sound_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include "../base/gm_chara_symbol_base.h"


// �R���X�g���N�^
ScenePlay::ScenePlay() {
	player_symbol_ = new PlayerSymbol();

	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 6, 5, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 15,11, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 30, 10, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 28, 21, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 30, 21, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 6, 21, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 16, 21, 0 }));
	enemy_symbols_.emplace_back(new EnemySymbol(tnl::Vector3{ 9, 19, 0 }));

	tnl::DebugTrace("Player : %d\n", sizeof(PlayerSymbol));
	tnl::DebugTrace("Chara : %d\n", sizeof(CharaSymbol));

	camera_ = new Camera(player_symbol_->getPos());

	// �X�^�[�g���̃C�x���g�𐶐�
	mess_event_ = new StartEvent();

	// BGM�ASE���[�h
	scene_play_snd_ = SoundManager::GetInstance()->loadSound(scene_play_snd_path_);

	enter_se_ = SoundManager::GetInstance()->loadSound(enter_se_path_);
	select_se_ = SoundManager::GetInstance()->loadSound(select_se_path_);
	clear_trans_se_ = SoundManager::GetInstance()->loadSound(clear_trans_se_path_);

	// �}�b�v�`�b�v�̉摜�̃��[�h
	gpc_map_chip_hdls_pass_ = "graphics/mapchip2.png";

	map_chip_width_ = 32;
	map_chip_height_ = 32;
	map_chip_x_size_ = 3;
	map_chip_y_size_ = 1;
	map_chip_all_size_ = map_chip_x_size_ * map_chip_y_size_;
	gpc_map_chip_hdls_ = new int[map_chip_all_size_];

	LoadDivGraph( gpc_map_chip_hdls_pass_.c_str(),
		map_chip_all_size_, 
		map_chip_x_size_,
		map_chip_y_size_,
		GameManager::GPC_CHIP_SIZE,
		GameManager::GPC_CHIP_SIZE,
		gpc_map_chip_hdls_ );

	// �}�b�v�f�[�^�̃��[�h
	map_data_csv_pass_ = "csv/map_data.csv";

	mapchip_data_ = tnl::LoadCsv<int>(map_data_csv_pass_);

	// �}�b�v�f�[�^�̏�����
	map_data_.resize(mapchip_data_.size());

	for (int y = 0; y < mapchip_data_.size(); ++y) {
		map_data_[y].resize(mapchip_data_[y].size());

		for (int x = 0; x < mapchip_data_[y].size(); ++x) {
			map_data_[y][x] = mapchip_data_[y][x];
		}
	}

	if (player_symbol_) setMapData( player_symbol_->getPos(), static_cast<int>( eMapData::PLAYER ) );

	for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
		setMapData( (*it)->getPos(), static_cast<int>( eMapData::ENEMY ) );
	}


	for (int y = 0; y < map_data_.size(); ++y) {
		for (int x = 0; x < map_data_[y].size(); ++x) {
			tnl::DebugTrace("%d, ", map_data_[y][x]);
		}
		tnl::DebugTrace("\n");
	}
}

// �f�X�g���N�^
ScenePlay::~ScenePlay() {

	delete player_symbol_;
	player_symbol_ = nullptr;

	for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
		delete* it;
	}
	enemy_symbols_.clear();

	delete camera_;
	camera_ = nullptr;

	delete menu_ui_;
	menu_ui_ = nullptr;

	delete mess_event_;
	mess_event_ = nullptr;


	StopSoundMem(scene_play_snd_);

	// BGM�ASE�폜
	SoundManager::GetInstance()->deleteSound(scene_play_snd_path_);
	SoundManager::GetInstance()->deleteSound(enter_se_path_);
	SoundManager::GetInstance()->deleteSound(select_se_path_);
	SoundManager::GetInstance()->deleteSound(clear_trans_se_path_);

	// �摜�폜
	for (int i = 0; i < map_chip_all_size_; ++i) {
		DeleteGraph(gpc_map_chip_hdls_[i]);
	}

	delete[] gpc_map_chip_hdls_;
	gpc_map_chip_hdls_ = nullptr;
}

// �V�[���v���C�̃A�b�v�f�[�g
void ScenePlay::update(float delta_time) {

	sequence_.update(delta_time);
}

// �V�[���v���C�̕`��
void ScenePlay::draw() {

	// �}�b�v�̕\��
	for (int y = 0; y < mapchip_data_.size(); ++y) {
		for (int x = 0; x < mapchip_data_[y].size(); ++x) {
			tnl::Vector3 draw_pos = tnl::Vector3(x * GameManager::GPC_DRAW_CHIP_SIZE, y * GameManager::GPC_DRAW_CHIP_SIZE, 0)
				- camera_->getPos() + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
			
			// �`��
			DrawExtendGraph(draw_pos.x, draw_pos.y, 
				draw_pos.x + GameManager::GPC_DRAW_CHIP_SIZE, draw_pos.y + GameManager::GPC_DRAW_CHIP_SIZE
				, gpc_map_chip_hdls_[mapchip_data_[y][x]], true);
		}
	}

	if (player_symbol_) player_symbol_->draw(camera_->getPos());

	for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
		if(camera_) (*it)->draw(camera_->getPos());
	}

	if (menu_ui_) menu_ui_->draw();

	if (mess_event_) mess_event_->draw();

	SetFontSize(DEFAULT_FONT_SIZE);
	DrawStringEx(10, 40, -1, "camera_x = %.2f, camera_y = %.2f", camera_->getPos().x, camera_->getPos().y);
}

// �X�^�[�g�C�x���g
bool ScenePlay::seqStartEvent(const float delta_time) {

	// �t�F�[�h���o�I����
	if (!GameManager::GetInstance()->isTransition()) {
		if (mess_event_) {
			mess_event_->update(delta_time);

			// ���b�Z�[�W�C�x���g�I����
			if (mess_event_->getEndFlg()) {
				delete mess_event_;
				mess_event_ = nullptr;
				sequence_.change(&ScenePlay::seqPlayerAct);
				PlaySoundMem(scene_play_snd_, DX_PLAYTYPE_LOOP, true);
			}
		}
	}

	return true;
}

// �v���C���[�s���V�[�P���X
bool ScenePlay::seqPlayerAct(const float delta_time) {

	charaUpdate(delta_time);

	if (!player_symbol_) return false;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		menu_ui_ = new MenuUICommander();
		sequence_.change(&ScenePlay::seqMenuSelect);
		return true;
	}

	// �s���J�n��
	if (player_symbol_->getActState() == eActState::ACT) {

		// �����蔻��
		if (getMapNum(player_symbol_->getNextPos()) == static_cast<int>(eMapData::WALL)) {
			player_symbol_->setIsCollision(true);
		}
		else if (getMapNum(player_symbol_->getNextPos()) == static_cast<int>(eMapData::ENEMY)) {
			player_symbol_->setIsCollision(true);
		}
		else {
			// �}�b�v�f�[�^�̍X�V
			setMapData(player_symbol_->getPos(), getMapChipData(player_symbol_->getPos()));
			setMapData(player_symbol_->getNextPos(), static_cast<int>(eMapData::PLAYER));

			sequence_.change(&ScenePlay::seqEnemyAct);

		}
	}

	// �U���s���J�n��
	if (player_symbol_->getActState() == eActState::ATTACK) {
		sequence_.change(&ScenePlay::seqPlayerAttack);
	}

	return true;
}

// �v���C���[�U���V�[�P���X
bool ScenePlay::seqPlayerAttack(const float delta_time) {

	charaUpdate(delta_time);

	// �U�����Ȃ�A�����͂����܂�
	if (player_symbol_->getActState() == eActState::ATTACK) return true;
	
	sequence_.change(&ScenePlay::seqEnemyAct);

	return true;
}

// �G�̍s���V�[�P���X
bool ScenePlay::seqEnemyAct(const float delta_time) {
	
	charaUpdate(delta_time);

	 // �����蔻��
	for (auto enemy_symbol : enemy_symbols_) {

		enemy_symbol->beginAct();

		if (getMapNum(enemy_symbol->getNextPos()) == static_cast<int>(eMapData::PLAYER)) {
			enemy_symbol->setIsCollision(true);
		}
		else if (getMapNum(enemy_symbol->getNextPos()) == static_cast<int>(eMapData::GROUND)) {
			setMapData(enemy_symbol->getPos(), getMapChipData(enemy_symbol->getPos()));
			setMapData(enemy_symbol->getNextPos(), static_cast<int>(eMapData::ENEMY));
		}
		else {
			enemy_symbol->setIsCollision(true);
		}
	}
	sequence_.change(&ScenePlay::seqCheckActEnd);
	
	return true;
}

// �s���I���m�F�V�[�P���X
bool ScenePlay::seqCheckActEnd(const float delta_time) {

	charaUpdate(delta_time);

	if (!player_symbol_) return false;
	if (player_symbol_->getActState() != eActState::END) return true;

	for (auto enemy_symbol : enemy_symbols_) {
		if (enemy_symbol->getActState() != eActState::END) return true;
	}

	if (getMapChipData(player_symbol_->getPos()) == static_cast<int>(eMapData::GOAL)) {
		sequence_.change(&ScenePlay::seqChangeResultScene);
		return true;
	}

	player_symbol_->beginAct();
	sequence_.change(&ScenePlay::seqPlayerAct);

	return true;
}

// ���j���[�I���V�[�P���X
bool ScenePlay::seqMenuSelect(const float delta_time) {

	if (menu_ui_ == nullptr) return false;

	menu_ui_->update(delta_time);

	if (menu_ui_->isSelectMenu() == false) {
		sequence_.change(&ScenePlay::seqPlayerAct);
		return true;
	}
	if (menu_ui_->isEndGameSign()) {
		sequence_.change(&ScenePlay::seqChangeTitleScene);
		return true;
	}

	return true;
}

// �^�C�g���V�[���ɕς���
bool ScenePlay::seqChangeTitleScene(const float delta_time) {

	if (is_scene_change_) return true;

	GameManager::GetInstance()->changeScene(new SceneTitle(), eFadeColor::BLACK);
	is_scene_change_ = true;
	is_transition_process_ = true;

}

// ���U���g�V�[���ɕς���
bool ScenePlay::seqChangeResultScene(const float delta_time) {

	if (CheckSoundMem(clear_trans_se_) == false) {
		is_transition_process_ = true;
	}

	if (is_scene_change_) return true;

	PlaySoundMem(clear_trans_se_, DX_PLAYTYPE_BACK);
	GameManager::GetInstance()->changeScene(new SceneResult(), eFadeColor::WHITE);
	is_scene_change_ = true;
	is_transition_process_ = false;

	return true;
}

// �L�����N�^�[�A�b�v�f�[�g
void ScenePlay::charaUpdate(float delta_time) {

	// �v���C���[�̃A�b�v�f�[�g
	if (player_symbol_) {
		player_symbol_->update(delta_time);

		// �J�����A�b�v�f�[�g
		if (camera_) camera_->update(player_symbol_->getPos());
	}

	// �e�G�l�~�[�̃A�b�v�f�[�g
	for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
		(*it)->update(delta_time);
	}

}

//// �T���V�[�P���X
//bool ScenePlay::seqPlayerAct(const float delta_time) {
//
//	if (!scene_change_flg_) {
//
//		// �Z���N�g���j���[���o�Ă��邩�ǂ���
//		if (!select_ui_flg_) {
//
//			// �v���C���[�̃A�b�v�f�[�g
//			if (player_symbol_) {
//				player_symbol_->update(delta_time);
//
//				// �����蔻��
//				if ( getMapNum( player_symbol_->getNextPos() ) == static_cast<int>( eMapData::WALL ) ) {
//					player_symbol_->setColFlg(true);
//				}
//				else if( getMapNum( player_symbol_->getNextPos() ) == static_cast<int>( eMapData::ENEMY ) ) {
//					player_symbol_->setColFlg(true);
//				}
//				else {
//					// �}�b�v�f�[�^�̍X�V
//					setMapData(player_symbol_->getPos(), getMapChipData( player_symbol_->getPos() ) );
//					setMapData(player_symbol_->getNextPos(), static_cast<int>(eMapData::PLAYER));
//				}
//
//				// �s���I����
//				if (player_symbol_->getAct() == eCharaAct::END) {
//
//					// �S�[�����B��
//					if ( getMapChipData( player_symbol_->getPos() ) == static_cast<int>( eMapData::GOAL ) ) {
//						PlaySoundMem(clear_trans_se_, DX_PLAYTYPE_BACK);
//						GameManager::GetInstance()->changeScene(new SceneResult(), eFadeColor::WHITE);
//						scene_change_flg_ = true;
//					}
//				}
//
//				// �J�����A�b�v�f�[�g
//				if (camera_) camera_->update(player_symbol_->getPos());
//			}
//
//			// �e�G�l�~�[�̃A�b�v�f�[�g
//			for (auto it = enemy_symbols_.begin(); it != enemy_symbols_.end(); ++it) {
//
//				// �s�����邩�̔���
//				if (player_symbol_) {
//					if (player_symbol_->getAct() == eCharaAct::BEGIN) {
//						(*it)->setAct(eCharaAct::BEGIN);
//					}
//				}
//
//				(*it)->update(delta_time);
//
//				// �s���J�n��
//				if ( (*it)->getAct() == eCharaAct::BEGIN ) {
//
//					// �����蔻��
//					if (getMapNum((*it)->getNextPos()) == static_cast<int>( eMapData::PLAYER ) ) {
//						(*it)->setColFlg(true);
//					}
//					else if (getMapNum((*it)->getNextPos()) == static_cast<int>( eMapData::GROUND ) ) {
//						setMapData( (*it)->getPos(), getMapChipData( (*it)->getPos() ) );
//						setMapData( (*it)->getNextPos(), static_cast<int>( eMapData::ENEMY ) );
//					}
//					else {
//						(*it)->setColFlg(true);
//					}
//					
//				}
//			}		
//		}
//
//		if (menu_ui_) menu_ui_->update(delta_time);
//
//		if (player_symbol_->getAct() == eCharaAct::END) {
//			tnl::DebugTrace("�}�b�v�f�[�^\n");
//			for (int y = 0; y < map_data_.size(); ++y) {
//				for (int x = 0; x < map_data_[y].size(); ++x) {
//					tnl::DebugTrace("%d, ", map_data_[y][x]);
//				}
//				tnl::DebugTrace("\n");
//			}
//		}
//	}
//
//	return true;
//}
