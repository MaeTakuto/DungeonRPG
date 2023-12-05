#include "../../dxlib_ext/dxlib_ext.h"
#include "gm_sound_manager.h"



// �R���X�g���N�^
SoundManager::SoundManager() {

}

// �f�X�g���N�^
SoundManager::~SoundManager() {

	for (auto it = snd_container_.begin(); it != snd_container_.end(); ++it) {
		DeleteSoundMem(it->second);
	}
	snd_container_.clear();
}

// �A�h���X��n���B
SoundManager* SoundManager::GetInstance() {
	static SoundManager* instance = nullptr;
	if (!instance) {
		instance = new SoundManager();
	}
	return instance;
}

// �C���X�^���X�̃����������
void SoundManager::Destroy() {
	delete GetInstance();
}

// ���[�h�܂��́A�ۑ����ꂽbgm�Ase��n��
int SoundManager::loadSound(const std::string& snd_path) {
	
	auto it = snd_container_.find(snd_path);
	if (it != snd_container_.end()) return snd_container_[snd_path];
	int gpc_hdl = LoadSoundMem(snd_path.c_str());
	snd_container_.insert(std::make_pair(snd_path, gpc_hdl));
	return gpc_hdl;
}

// bgm�Ase���폜
void SoundManager::deleteSound(const std::string& snd_path) {

	DeleteSoundMem(snd_container_[snd_path]);
	snd_container_.erase(snd_path);
}

