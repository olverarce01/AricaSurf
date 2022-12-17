#include "stdafx.h"
#include "MyGame.h"

float turn = 0;
bool colisionOnda = false;
float monedasContador = 0;
float variacion = 1;
bool creciente = true;
bool Gderecha = false;
bool Gizquierda = false;
int frameCaida = 0;
float frameFondo = 0;
bool caida = false;
double coefVelocidad = 30;
int inicio = 0;
int lamba = 0;
double fuerzaPeso = 1;
double fuerzaX = 0;
double fuerzaY = 0;
double aceleracionX=0;
double aceleracionY=0;
double velocidadX=0;
double velocidadY=0;
int tiempoMaximo = 60000;

CMyGame::CMyGame(void) : 
	m_sprite(200, 100, "s1.png", 0),
	m_background(400, 300,800,800, "agua.gif", 0),
	m_morro(90, 430,300,150, "morro.png", 0),
	m_rozeAgua(200, 530, "rozeAgua.png", 0),
	m_scoreboard(670,570, "scoreboard.png",0),
	m_timer(680, 60, "timer.png", 0),
	m_anillos(380, 570, 100, 100, "anillos.png", 0)
{
	menu.LoadImage("menu.jpg");
	menu.SetImage("menu.jpg");
	menu.SetPosition(400, 300);
}
CMyGame::~CMyGame(void)
{
}
void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();
	switch (int(frameFondo))
	{
		case 0: m_background.SetImage("1b"); break;
		case 1: m_background.SetImage("2b"); break;
		case 2: m_background.SetImage("3b"); break;
		case 3: m_background.SetImage("4b"); break;
		case 4: m_background.SetImage("5b"); break;
		case 5: m_background.SetImage("6b"); break;
		case 6: m_background.SetImage("7b"); break;
		case 7: m_background.SetImage("8b"); break;
		case 8: m_background.SetImage("9b"); break;
		case 9: m_background.SetImage("10b"); break;
		case 10: m_background.SetImage("11b"); break;
		case 11: m_background.SetImage("12b"); break;
		default: frameFondo = 0; break;
	}
	frameFondo=frameFondo+0.1;
	if (IsGameMode()) {
		if (GetTime()>tiempoMaximo) {
			GameOver();
		}
		if (rand() % 60 == 0) {
			CSprite* nube= new CSprite(700, 560, 100, 100, "nube.png", 0);
			nube->SetXVelocity(-20);
			m_nubes.push_back(nube);
		}
		if (m_lanchas.empty()) {
			CSprite* lancha= new CSprite(-100, 380, 70, 30, "lancha.png", 0);
			lancha->SetXVelocity(20);
			m_lanchas.push_back(lancha);
		}
		if (rand() % 60 == 0) {
			CSprite* moneda = new CSprite(200 + rand() % (600 - 200), 390, 15, 15, "moneda-dolar.png", 0);
			m_moneda.push_back(moneda);
		}
		if (rand() % 100 == 0) {
			CSprite* roca = new CSprite(200 + rand() % (600 - 200), 390, 40, 10, "roca2.png", 0);
			m_roca.push_back(roca);
		}
		for (CSprite* nube : m_nubes)
		{
			if (nube->GetX() < 0) {
				nube->Delete();
			}
		}m_nubes.delete_if(deleted);
		for (CSprite* lancha : m_lanchas)
		{
			if (lancha->GetX() > 800) {
				lancha->Delete();
			}
		}m_lanchas.delete_if(deleted);

		for (CSprite* roca : m_roca)
		{
			if (roca->GetX() < 0 || roca->GetY() < 0) {
				roca->Delete();
			}
		}m_roca.delete_if(deleted);
		for (CSprite* roca : m_roca) {
			if (m_sprite.HitTest(roca)) {
				c_sprite.SetPosition(roca->GetX(), roca->GetY());
				roca->Delete();
				sonido_caida.Play("caida_surf.wav", 0);
				caida = true;
				GameOver();
			}
		}
		m_roca.delete_if(deleted);
		for (CSprite* moneda : m_moneda)
		{
			if (moneda->GetX() < 0 || moneda->GetY() < 0) {
				moneda->Delete();
			}
		}m_moneda.delete_if(deleted);
		for (CSprite* moneda : m_moneda) {
			if (m_sprite.HitTest(moneda)) {
				monedasContador=monedasContador+0.1;
				moneda->Delete();
				sonido_moneda.Play("moneda.wav", 0);
			}
		}
		m_moneda.delete_if(deleted);
		if (m_sprite.GetX() < 20) {
			m_sprite.SetX(20);
		}
		if (m_sprite.GetX() > 770) {
			m_sprite.SetX(770);
		}
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
		for (CSprite* roca : m_roca)
		{
			int x_moneda = roca->GetX();
			int y_moneda = roca->GetY();
			float w_moneda = roca->GetW();
			float h_moneda = roca->GetH();
			roca->SetX(x_moneda - 1);
			roca->SetY(y_moneda - 3);
			roca->SetSize(w_moneda + 0.2, h_moneda + 0.4);
		}
		for (CSprite* moneda : m_moneda) {
			moneda->Update(t);
		}
		for (CSprite* roca : m_roca) {
			roca->Update(t);
		}
	}
	int velocidadCrecimientoOnda = 1;
	if (level == 1) {
		velocidadCrecimientoOnda = 3;
	}
	else if (level == 2) {
		velocidadCrecimientoOnda = 5;
	}
	else if (level == 3) {
		velocidadCrecimientoOnda = 1;
	}
	else if (level == 4) {
		velocidadCrecimientoOnda = 3;
	}
	else if (level == 5) {
		velocidadCrecimientoOnda = 5;
	}

	float i = 0;
	float alturaOnda = 1;
	if (level == 1) {
		alturaOnda = 60;
	}
	else if (level == 2) {
		alturaOnda = 70;
	}
	else if (level == 3) {
		alturaOnda = 80;
	}
	else if (level == 4) {
		alturaOnda = 90;
	}
	else if (level == 5) {
		alturaOnda = 100;
	}
	if (rand() % 60 == 0) {
		if (variacion >= alturaOnda)
			creciente = false;
		if (variacion <= 1)
			creciente = true;
		if (creciente)
			variacion=variacion+velocidadCrecimientoOnda;
		if (!creciente)
			variacion=variacion- velocidadCrecimientoOnda;
	}
	float velocidadOnda = 1;
	if (level == 1) {
		velocidadOnda = 1;
	}
	else if(level==2){
		velocidadOnda = 1.5;
	}
	else if (level == 3) {
		velocidadOnda = 1;
	}
	else if (level == 4) {
		velocidadOnda = 1.5;
	}
	else if (level == 5) {
		velocidadOnda = 1;
	}
	fuerzaY = -fuerzaPeso;
	aceleracionY = fuerzaY / 1;
	velocidadY = m_sprite.GetYVelocity() + aceleracionY * GetDeltaTime();

	float longitudOnda = 1;
	if (level == 1) {
		longitudOnda = 0.3;
	}
	else if (level == 2) {
		longitudOnda = 0.4;
	}
	else if (level == 3) {
		longitudOnda = 0.1;
	}
	else if (level == 4) {
		longitudOnda = 0.3;
	}
	else if (level == 5) {
		longitudOnda = 0.4;
	}
	for (CSprite* onda : m_ondas)
	{
		onda->SetY(50 * (variacion * 0.02) * sin(DEG2RAD((t*velocidadOnda / 5 + i))));
		if (m_sprite.HitTest(onda)) {
			if (turn >= 0)
			{
				fuerzaX = fuerzaPeso * sin(DEG2RAD((t* velocidadOnda / 5 + i)));
			}
			else {
				fuerzaX = -fuerzaPeso * sin(DEG2RAD((t* velocidadOnda / 5 + i)));
			}
			aceleracionX = fuerzaX / 1;
			velocidadX = m_sprite.GetXVelocity() + aceleracionX * GetDeltaTime();
			velocidadY = 0;

			if (turn >= 0)
			{
				velocidadX += coefVelocidad;
			}
			else {
				velocidadX -= coefVelocidad;
			}
		}
		i=i+longitudOnda;
	}
	i = 0;
	for (CSprite* espuma : m_espuma)
	{
		espuma->SetY(100+50 * (variacion * 0.02) * sin(DEG2RAD((t * velocidadOnda / 5 + i))));
		i = i + longitudOnda;
	}
	i = 0;
	if (IsGameMode()) {
		m_sprite.SetXVelocity(velocidadX);
		m_sprite.SetYVelocity(velocidadY);
		for (CSprite* onda : m_ondas) {
			if (m_sprite.HitTest(onda)) {
				int x = m_sprite.GetX();
				int y = m_sprite.GetY();
				m_sprite.SetPosition(x, y + 10);
				m_rozeAgua.SetPosition(onda->GetX(), onda->GetY() + 100);
				colisionOnda = true;
			}
		}
	}
	if (IsGameMode()) {
		if (Gderecha)
			turn = turn + 0.5;
		if (Gizquierda)
			turn = turn - 0.5;
		if (turn == -6)
			turn = 5;
		if (turn == 6)
			turn = -5;
		if (turn <= 1)
			m_sprite.SetImage("1");
		else if (turn <= 2)
			m_sprite.SetImage("2");
		else if (turn <= 3)
			m_sprite.SetImage("3");
		else if (turn <= 4)
			m_sprite.SetImage("4");
		else if (turn <= 5)
			m_sprite.SetImage("5");
		if (turn <= -5)
			m_sprite.SetImage("6");
		else if (turn <= -4)
			m_sprite.SetImage("7");
		else if (turn <= -3)
			m_sprite.SetImage("8");
		else if (turn <= -2)
			m_sprite.SetImage("9");
		else if (turn <= -1)
			m_sprite.SetImage("10");
	}
	if (IsGameOver()) {
		m_sprite.SetXVelocity(0);
		if (rand() % 2 == 0 && caida==true) {

			switch (frameCaida)
			{
			case 0: m_sprite.SetImage("11"); break;
			case 1: m_sprite.SetImage("12"); break;
			case 2: m_sprite.SetImage("13");
			default: break;
			}
			frameCaida++;
		}
	}
	m_sprite.Update(t);
	for (CSprite* onda : m_ondas) {
		onda->Update(t);
	}
	for (CSprite* espuma : m_espuma) {
		espuma->Update(t);
	}
	for (CSprite* nube: m_nubes) {
		nube->Update(t);
	}
	for (CSprite* lancha : m_lanchas) {
		lancha->Update(t);
	}
	m_background.Update(t);
	m_morro.Update(t);
	m_rozeAgua.Update(t);
	m_scoreboard.Update(t);
	m_timer.Update(t);
	m_anillos.Update(t);
}
void CMyGame::OnDraw(CGraphics* g)
{
	if (IsMenuMode())
	{
		menu.Draw(g);
		return;
	}
	m_background.Draw(g);
	m_morro.Draw(g);
	for (CSprite* moneda : m_moneda) {
		moneda->Draw(g);
	}
	for (CSprite* roca : m_roca) {
		roca->Draw(g);
	}
	for (CSprite* onda : m_ondas) {
		onda->Draw(g);
	}
	for (CSprite* espuma : m_espuma) {
		espuma->Draw(g);
	}
	for (CSprite* nube: m_nubes) {
		nube->Draw(g);
	}
	for (CSprite* lancha : m_lanchas) {
		lancha->Draw(g);
	}
	m_sprite.Draw(g);
	if (colisionOnda) {
		m_rozeAgua.Draw(g);
	}
	colisionOnda = false;
	m_scoreboard.Draw(g);
	m_timer.Draw(g);
	m_anillos.Draw(g);

	if (IsGameOverMode())
	{
		*g << font(48) << color(CColor::Black()) << vcenter << center << "Juego Terminado" << endl;
		*g << font(24);
		*g << "Puntaje: " << monedasContador << "/0.5" << flush;
		*g << font(24) << bottom << right << color(0, 4, 33) << margins(30, 125, 30, 30) << timetext(0);
	}
	if (IsGameMode())
	{
		if (GetTime() < tiempoMaximo)
		{
			*g << font(24) << bottom << right << color(0, 4, 33) << margins(30, 125, 30, 30) << timetext(tiempoMaximo - GetTime());
		}
		else {
			*g << font(24) << bottom << right << color(0, 4, 33) << margins(30, 125, 30, 30) << timetext(0);
		}
	}
	*g << font(20) << top << right << margins(30, 30, 30, 30) << monedasContador<<"/" << 0.5;
	*g << font(20) << top << right << margins(30, 30, 60, 30) << "Nivel: " << level;
}

void CMyGame::OnInitialize()
{
}
void CMyGame::OnDisplayMenu()
{
	musica_juego.Play("sounds/musica_juego.wav",-1);
	m_sprite.SetPos(200, 100);
	c_sprite.SetPos(-100, -100);
}
void CMyGame::OnStartGame()
{
	musica_juego.Stop();
	musica_surf.Play("sounds/musica_surf.wav", -1);
	frameCaida = 0;
	monedasContador = 0;
	m_sprite.SetPosition(200,100);
	m_sprite.SetVelocity(0,0);
	m_sprite.SetImage("1");
	caida = false;
	for (CSprite* onda : m_ondas)
	{
		onda->Delete();
	}m_ondas.delete_if(deleted);
	for (CSprite* espuma : m_espuma)
	{
		espuma->Delete();
	}m_espuma.delete_if(deleted);
	CSprite* moneda = new CSprite(200 + rand() % (600 - 200), 470, 15, 15, "moneda-dolar.png", 0);
	m_moneda.push_back(moneda);
	for (int i = 0; i < 850; i++)
	{
		CSpriteRect* onda = new CSpriteRect(i, 50*sin(DEG2RAD(i)), 5, 200, CColor::LightCyan(), CColor::LightCyan(), 0);
		CSprite* espuma = new CSprite(i, 50 * sin(DEG2RAD(i)), 20,50, "espuma.png", 0);
		m_ondas.push_back(onda);
		m_espuma.push_back(espuma);
	}
	m_sprite.LoadImageW("s1.png", "1");
	m_sprite.LoadImageW("s2.png", "2");
	m_sprite.LoadImageW("s3.png", "3");
	m_sprite.LoadImageW("s4.png", "4");
	m_sprite.LoadImageW("s5.png", "5");
	m_sprite.LoadImageW("s6.png", "6");
	m_sprite.LoadImageW("s7.png", "7");
	m_sprite.LoadImageW("s8.png", "8");
	m_sprite.LoadImageW("s9.png", "9");
	m_sprite.LoadImageW("s10.png", "10");
	m_sprite.LoadImageW("s11.png", "11");
	m_sprite.LoadImageW("s12.png", "12");
	m_sprite.LoadImageW("s13.png", "13");
	m_background.LoadImageW("1.gif", "1b");
	m_background.LoadImageW("2.gif", "2b");
	m_background.LoadImageW("3.gif", "3b");
	m_background.LoadImageW("4.gif", "4b");
	m_background.LoadImageW("5.gif", "5b");
	m_background.LoadImageW("6.gif", "6b");
	m_background.LoadImageW("7.gif", "7b");
	m_background.LoadImageW("8.gif", "8b");
	m_background.LoadImageW("9.gif", "9b");
	m_background.LoadImageW("10.gif", "10b");
	m_background.LoadImageW("11.gif", "11b");
	m_background.LoadImageW("12.gif", "12b");
}
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}
void CMyGame::OnGameOver()
{
	musica_surf.Stop();
	if (caida) {
		m_sprite.SetYVelocity(0);
		m_sprite.Accelerate(0, -300);
	}
	else {
		m_sprite.SetPosition(900,900);
	}
	musica_juego.Pause();
	for (CSprite* roca : m_roca)
	{
		roca->Delete();
	}m_roca.delete_if(deleted);
	for (CSprite* moneda : m_moneda)
	{
		moneda->Delete();
	}m_moneda.delete_if(deleted);
	if (monedasContador >= 0.5 && level<5)
	{
		level++;
	}
}
void CMyGame::OnTerminate()
{
}
void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_r)
		NewGame();
	if (sym == SDLK_LEFT)
	{
		Gizquierda = true;
	}
	if (sym == SDLK_RIGHT)
	{
		Gderecha = true;
	}
	if (sym == SDLK_a)
		lamba++;
	if (sym == SDLK_s)
		lamba--;
	if (sym == SDLK_d)
		coefVelocidad = 30;
	if (IsMenuMode() && sym == SDLK_SPACE)
	{
		StartGame();
	}
}
void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_LEFT)
	{
		Gizquierda = false;
	}
	if (sym == SDLK_RIGHT)
	{
		Gderecha = false;
	}
	if (sym == SDLK_d)
		coefVelocidad = 5;
}
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