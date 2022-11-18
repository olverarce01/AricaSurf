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
	if (IsGameOverMode()) {
		return;
	}

	Uint32 t = GetTime();

	if (rand() % 60 == 0) {
		CSprite* moneda = new CSprite(400, 600, 20, 20, "moneda-dolar.png", 0);
		m_moneda.push_back(moneda);
	}
	if (rand() % 60 == 0) {
		CSprite* ola = new CSprite(400, 600, 150, 150, "ola.png", 0);
		m_ola.push_back(ola);
	}
	if (rand() % 60 == 0) {
		CSprite* roca1 = new CSprite(280, 600, 20, 40, "roca1.png", 0);
		m_roca1.push_back(roca1);
	}
	if (rand() % 60 == 0) {
		CSprite* roca2 = new CSprite(600, 600, 20, 40, "roca2.png", 0);
		m_roca2.push_back(roca2);
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
			m_bscore++;
			moneda->Delete();
		}
	}
	m_moneda.delete_if(deleted);
	for (CSprite* roca1 : m_roca1)
	{
		if (roca1->GetX() < 0 || roca1->GetY() < 0) {
			roca1->Delete();
		}
	}m_roca1.delete_if(deleted);
	for (CSprite* roca2 : m_roca2)
	{
		if (roca2->GetX() < 0 || roca2->GetY() < 0) {
			roca2->Delete();
		}
	}m_roca2.delete_if(deleted);

	for (CSprite* roca1 : m_roca1) {
		if (m_sprite.HitTest(roca1)) {
			GameOver();
			m_sprite.SetPos(-100, -100);
		}
	}
	for (CSprite* roca2 : m_roca2) {
		if (m_sprite.HitTest(roca2)) {
			GameOver();
			m_sprite.SetPos(-100, -100);
		}
	}

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
	for (CSprite* roca1 : m_roca1)
	{
		int x_roca1 = roca1->GetX();
		int y_roca1 = roca1->GetY();
		float w_roca1 = roca1->GetW();
		float h_roca1 = roca1->GetH();

		roca1->SetX(x_roca1 - 1);
		roca1->SetY(y_roca1 - 3);
		roca1->SetSize(w_roca1 + 0.2, h_roca1 + 0.2);

	}
	for (CSprite* roca2 : m_roca2)
	{
		int x_roca2 = roca2->GetX();
		int y_roca2 = roca2->GetY();
		float w_roca2 = roca2->GetW();
		float h_roca2 = roca2->GetH();

		roca2->SetX(x_roca2 - 1);
		roca2->SetY(y_roca2 - 3);
		roca2->SetSize(w_roca2 + 0.2, h_roca2 + 0.2);

	}

	m_sprite.Update(t);	// this will update the sample rocket sprite
	for (CSprite* ola : m_ola)
	{
		ola->Update(t);
	}
	for (CSprite* moneda : m_moneda) {
		moneda->Update(t);
	}
	for (CSprite* roca1 : m_roca1) {
		roca1->Update(t);
	}
	for (CSprite* roca2 : m_roca2) {
		roca2->Update(t);
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
	for (CSprite* roca1 : m_roca1) {
		roca1->Draw(g);
	}
	for (CSprite* roca2 : m_roca2) {
		roca2->Draw(g);
	}
	m_sprite.Draw(g);	// this will draw the sample rocket sprite

	// this will print the game time
	if (IsGameOverMode()) {
		*g << font(48) << color(CColor::Black()) << vcenter << center << "GAME OVER" << endl;
		*g << font(24);
		*g << "You survived " << GetTimeGameOver() / 1000 << " seconds" << endl;
		*g << "Score: " << m_bscore << flush;
	}
	else {
		*g << font(18) << color(CColor::Black());
		*g << bottom << left << "Time elapsed: " << timetext(GetTime());
		*g << right << "Score: " << m_bscore << flush;
	}
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
	m_sprite.SetPos(200, 100);
	m_sprite.SetXVelocity(0);
	m_bscore = 0;
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
	if (sym == SDLK_a)
		NewGame();


	if (sym == SDLK_LEFT)
	{
		m_sprite.Accelerate(-200, 0);
	}
	if (sym == SDLK_RIGHT)
	{
		m_sprite.Accelerate(200, 0);
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
