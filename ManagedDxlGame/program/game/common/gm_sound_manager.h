#pragma once



// ���y���Ǘ�����N���X
class SoundManager {
public:
	static SoundManager* GetInstance();					// �C���X�^���X��Ԃ��B
	static void Destroy();									// �C���X�^���X�̍폜�B

	int loadSound(const std::string& snd_path);			// �摜�̃��[�h�A�摜�̃A�h���X��n���B
	void deleteSound(const std::string& snd_path);		// �摜�̍폜

private:
	SoundManager();
	~SoundManager();

	std::unordered_map< std::string, int > snd_container_;	// �摜�f�[�^�̊i�[

};