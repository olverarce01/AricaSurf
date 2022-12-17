#pragma once

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite m_sprite;	// Sample sprite
	CSprite m_background;	// Sample sprite
	CSpriteList m_ondas;
	CSpriteList m_espuma;
	CSpriteList m_nubes;
	CSpriteList m_lanchas;


	CSpriteList m_moneda;
	CSprite m_morro;
	CSprite m_rozeAgua;


	CSprite m_scoreboard;
	CSprite m_timer;
	CSprite m_anillos;


	int level=1;
	CSprite menu;

	CSprite c_sprite;
	CSoundPlayer musica_juego; // Musica juego
	CSoundPlayer musica_surf; // Musica juego

	CSoundPlayer sonido_caida; // Sonido 
	CSoundPlayer sonido_moneda; // Sonido 

	CSoundPlayer sonido_surf;
	CSpriteList m_roca; // Rocas 



public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
