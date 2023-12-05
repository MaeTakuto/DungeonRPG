#pragma once
#include "../base/gm_scene_base.h"


class SceneResult : public SceneBase {
public:
	SceneResult();
	~SceneResult();

	void update(float delta_time) override;
	void draw() override;

	inline bool isTransitionProcess() override { return is_transition_process_; }

private:
	int background_ = 0;

};