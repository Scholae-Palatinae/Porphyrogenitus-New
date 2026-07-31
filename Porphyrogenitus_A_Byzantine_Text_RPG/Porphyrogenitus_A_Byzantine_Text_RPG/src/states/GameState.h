#pragma once
#include "IState.h"

class GameState : public IState
{
private:

public:
	GameState();
	~GameState();
	
	void OnEnter() override;
	void OnExit() override;
	void Update() override;
	void Draw() override;
	void ProcessInputs() override;
	bool Exit() override;

};