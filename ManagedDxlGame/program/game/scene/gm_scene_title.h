#pragma once
#include "../base/gm_scene_base.h"


class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle();

	void update(float delta_time);
	void draw();

	inline bool isTransitionProcess() override { return is_transition_process_; }

private:
	const std::string TITLE_LOGO = "ñ¿Ç¢ÇÃêX";

	const tnl::Vector3 TITLE_LOGO_POS = { 420, 100, 0 };

	std::string background_path_ = "graphics/Title.JPG";
	std::string title_snd_path_ = "sound/MusMus/title_bgm.mp3";

	int background = 0;
	int title_snd_ = 0;

	tnl::Sequence<SceneTitle> sequence_
		= tnl::Sequence<SceneTitle>(this, &SceneTitle::seqCheckTrans);

	bool seqCheckTrans(const float delta_time);
	bool seqSelectMenu(const float delta_time);

};