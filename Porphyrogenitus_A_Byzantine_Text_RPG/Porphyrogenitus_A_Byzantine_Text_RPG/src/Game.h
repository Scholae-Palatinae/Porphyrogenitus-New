#pragma once
#include "Console.h"
#include "inputs/Keyboard.h"

class Game
{
private:
	bool m_bIsRunning;
	
	std::unique_ptr<Console> m_pConsole;
	std::unique_ptr<Keyboard>m_pKeyboard;
	DWORD m_NumRead;
	INPUT_RECORD m_InRecBuf[128];
	HANDLE m_hConsoleIn;

	bool Init();

	void ProcessEvents();
	void ProcessInputs();
	void Update();
	void Draw();

	void KeyEventProcess(KEY_EVENT_RECORD keyEvent);

public:
	Game();
	~Game();

	void Run();
};