#pragma once



// 音楽を管理するクラス
class SoundManager {
public:
	static SoundManager* GetInstance();					// インスタンスを返す。
	static void Destroy();									// インスタンスの削除。

	int loadSound(const std::string& snd_path);			// 画像のロード、画像のアドレスを渡す。
	void deleteSound(const std::string& snd_path);		// 画像の削除

private:
	SoundManager();
	~SoundManager();

	std::unordered_map< std::string, int > snd_container_;	// 画像データの格納

};