#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{

	TextureManager::Instance()->draw("StartScreen", 400, 300, 0, 255, true);

	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{

	TextureManager::Instance()->load("../Assets/textures/StartScreen.png", "StartScreen");

	const SDL_Color blue = { 0, 0, 255, 255 };
	
	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 275.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	//Instructions Button
	m_pInstructButton = new Button("../Assets/textures/InstructionsButton.png", "InstructionButton", INSTRUCT_BUTTON);
	m_pInstructButton->getTransform()->position = glm::vec2(400.0f, 350.0f);

	m_pInstructButton->addEventListener(CLICK, [&]()-> void
		{
			m_pInstructButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pInstructButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pInstructButton->setAlpha(128);
		});

	m_pInstructButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pInstructButton->setAlpha(255);
		});
	addChild(m_pInstructButton);

	
}

