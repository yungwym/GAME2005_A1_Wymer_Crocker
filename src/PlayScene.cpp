#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("PlayScreen", 400, 300, 0, 255, true);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				//m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
			//	m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					//m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					//m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
		//	m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			//m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				//m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				//m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{

	//Load Background and Textures 
	TextureManager::Instance()->load("../Assets/textures/PlayScreen_F.png", "PlayScreen");

	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Player Sprite
	m_pCrate = new Crate();
	addChild(m_pCrate);

	//Enemy Sprite
	m_pTriangle = new Triangle();
	addChild(m_pTriangle);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 530.0f);

	addChild(m_pInstructionsLabel);
}

void PlayScene::GUI_Function() const
{
	//Variables
	static int xTriPos = 400;
	static int triHeight = 200;
	static int triWidth = 300;

	glm::vec2 lineAStart = glm::vec2(xTriPos, 410);
	glm::vec2 lineAEnd = glm::vec2(xTriPos, triHeight);

	static int yCratePos = 93;
	static int xCratePos = 400;


	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Game Physics - Assignment 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	
	if(ImGui::Button("Drop Crate"))
	{
		
	}

	ImGui::Separator();

	static bool isGravityEnabled = false;
	if (ImGui::Checkbox("Gravity", &isGravityEnabled))
	{
		//m_pBall->isGravityEnabled = isGravityEnabled;
	}

	if (ImGui::SliderInt("Triangle Position X", &xTriPos, 45, 590))
	{
		m_pTriangle->getTransform()->position.x = xTriPos;
		m_pTriangle->setLineA(triHeight);
		m_pTriangle->setLineB(triWidth);
	}

	if (ImGui::SliderInt("Triangle Height", &triHeight, 10, 235))
	{
		m_pTriangle->setLineA(triHeight);
	}


	if (ImGui::SliderInt("Triangle Width", &triWidth, 10, 700))
	{
		m_pTriangle->setLineB(triWidth);
	}

	ImGui::Separator();
	ImGui::Spacing();
	//Crate Position  
	
	if (ImGui::SliderInt("Crate Position X", &xCratePos, 90, 710))
	{
		m_pCrate->getTransform()->position.x = xCratePos;
	}


	if (ImGui::SliderInt("Crate Position Y", &yCratePos, 80, 230))
	{
		m_pCrate->getTransform()->position.y = yCratePos;
	}

	ImGui::End();
	
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
