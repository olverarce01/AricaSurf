#include "stdafx.h"
#include "MyGame.h"

int turn = 0;

CMyGame::CMyGame(void) : 
	m_sprite(200, 100, "spriteSurfer.png", 0),
	m_background(400, 300, "fondo.png", 0)
	// to initialise more sprites here use a comma-separated list
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

void movimientoMoneda(CSprite m_moneda) {

}
/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	if (rand() % 60 == 0) {
		CSprite* moneda = new CSprite(400, 600, 20, 20, "moneda-dolar.png", 0);
		m_moneda.push_back(moneda);
	}
	if (rand() % 60 == 0) {
		CSprite* ola = new CSprite(400, 600, 150, 150, "ola.png", 0);
		m_ola.push_back(ola);
	}
	for (CSprite* ola : m_ola)
	{
		if (ola->GetX()<0 || ola->GetY()<0) {
			ola->Delete();
		}
	}m_ola.delete_if(deleted);
	for (CSprite* moneda : m_moneda)
	{
		if (moneda->GetX() < 0 || moneda->GetY() < 0) {
			moneda->Delete();
		}
	}m_moneda.delete_if(deleted);


	for (CSprite* moneda : m_moneda) {
		if (m_sprite.HitTest(moneda)) {
			GameOver();
			moneda->Delete();
		}
	}
	m_moneda.delete_if(deleted);

	if (turn > 0)
		m_sprite.SetRotation(m_sprite.GetRotation() + 1);
	if (turn < 0)
		m_sprite.SetRotation(m_sprite.GetRotation() - 1);

	for (CSprite* moneda : m_moneda)
	{
		int x_moneda = moneda->GetX();
		int y_moneda = moneda->GetY();
		float w_moneda = moneda->GetW();
		float h_moneda = moneda->GetH();
		moneda->SetX(x_moneda - 1);
		moneda->SetY(y_moneda - 3);
		moneda->SetSize(w_moneda + 0.2, h_moneda + 0.2);
	}
	for (CSprite* ola : m_ola)
	{
		int x_ola = ola->GetX();
		int y_ola = ola->GetY();
		float w_ola = ola->GetW();
		float h_ola = ola->GetH();

		ola->SetX(x_ola - 1);
		ola->SetY(y_ola - 3);
		ola->SetSize(w_ola + 0.4, h_ola + 0.4);

	}

	m_sprite.Update(t);	// this will update the sample rocket sprite
	for (CSprite* ola : m_ola)
	{
		ola->Update(t);
	}
	for (CSprite* moneda : m_moneda) {
		moneda->Update(t);
	}
	m_background.Update(t);
}


void CMyGame::OnDraw(CGraphics* g)
{
	m_background.Draw(g);
	for (CSprite* ola : m_ola) {
		ola->Draw(g);
	}
	for (CSprite* moneda : m_moneda) {
		moneda->Draw(g);
	}
	m_sprite.Draw(g);	// this will draw the sample rocket sprite

	// this will print the game time
	*g << bottom << left << "Time elapsed: " << timetext(GetTime());
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	StartGame();	// exits the menu mode and starts the game mode
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	CSprite* moneda = new CSprite(400, 600, 20, 20, "moneda-dolar.png", 0);
	m_moneda.push_back(moneda);
	CSprite* ola = new CSprite(400, 600, 150, 150, "ola.png", 0);
	m_ola.push_back(ola);
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();


	if (sym == SDLK_LEFT)
	{
		m_sprite.Accelerate(-100, 0);
	}
	if (sym == SDLK_RIGHT)
	{
		m_sprite.Accelerate(100, 0);
	}
	if (sym == SDLK_UP)
	{
		turn--;
	}
	if (sym == SDLK_DOWN)
	{
		turn++;
	}
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_LEFT)
	{
		m_sprite.Accelerate(100, 0);
	}
	if (sym == SDLK_RIGHT)
	{
		m_sprite.Accelerate(-100, 0);
	}
	if (sym == SDLK_UP)
	{
		turn++;
	}
	if (sym == SDLK_DOWN)
	{
		turn--;
	}
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
