#include "Game.h"
#include "Logger.h"
#include <iostream>

bool Game::Init()
{
    try
    {
        m_pConsole = std::make_unique<Console>();
    }
    catch(std::exception& e)
    {
        std::string error = e.what();
        TRPG_ERROR(error);
        return false;
    }

    m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

    return true;
}

void Game::ProcessEvents()
{
    // Get the number of Console Inputs
    if (!GetNumberOfConsoleInputEvents(m_hConsoleIn, &m_NumRead))
    {
        DWORD error = GetLastError();
        TRPG_ERROR("Failed to get number of console input events!" + error);
        return;
    }

    if (m_NumRead <= 0)
        return;

    if (!PeekConsoleInput(m_hConsoleIn, m_InRecBuf, 128, &m_NumRead))
    {
        DWORD error = GetLastError();
        TRPG_ERROR("Failed to Peek Events!" + error);
        return;
    }

    for (int i = 0; i < m_NumRead;i++)
    {
        switch (m_InRecBuf[i].EventType)
        {
        case KEY_EVENT:
            KeyEventProcess(m_InRecBuf[i].Event.KeyEvent);
            break;
        default:
            break;

        }
    }

    // Clear or Fluch Other inputs
    FlushConsoleInputBuffer(m_hConsoleIn);

}

void Game::ProcessInputs()
{

}

void Game::Update()
{

}

void Game::Draw()
{
    m_pConsole->Write(10, 10, L"Hello World!", RED);
    m_pConsole->Draw();
}

void Game::KeyEventProcess(KEY_EVENT_RECORD keyEvent)
{
    if (keyEvent.bKeyDown)
    {
        // TO DO : Keyboard clas goes here!
        std::cout << "Key Pressed!" << keyEvent.wVirtualKeyCode << std::endl;
    }
    else
    {
        std::cout << "Key Released!" << keyEvent.wVirtualKeyCode << std::endl;
    }
}

Game::Game()
    :m_bIsRunning{true}
{

}

Game::~Game()
{

}

void Game::Run()
{
    if (!Init())
        m_bIsRunning = false;

    while (m_bIsRunning)
    {
        ProcessInputs();
        ProcessEvents();
        Update();
        Draw();
    }
}
