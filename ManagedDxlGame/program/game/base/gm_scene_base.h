#pragma once


class SceneBase {
public:
	virtual ~SceneBase() {};

	virtual bool isTransitionProcess() = 0;

	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;

protected:
	bool is_transition_process_ = false;

};