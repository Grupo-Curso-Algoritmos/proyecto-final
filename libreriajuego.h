#pragma once
#include <iostream>
#include <conio.h>
#include <math.h>
#include <SFML/Audio.hpp>

#define WIDTH 120
#define HEIGHT 30
#define COLUMNAS 80
#define FILAS 25
#define NIVELES 3
#define arriba  72
#define abajo  80
#define izquierda  75
#define derecha  77
#define escape 27
#define enter 13
#define MILISEGUNDOS 150
#define ll long long
#define caracter_saqueador "<^>"
#define caracter_aliado "\\0/"
#define caracter_hambriento "uwu"

using namespace System;
using namespace sf;
using namespace std;

// Estructuras

struct Coordenadas {
	int x;
	int y;
};

struct Personaje {
	int x;
	int y;
	long velocidad;
	bool vertical;
	int vida;
	bool en_pantalla = false;
	bool vuelta;
	short idx;
};

struct Item {
	int x;
	int y;
	char tipo;
	short idx;
	bool en_pantalla;
};

struct Nivel {
	int personajes_hambrientos;
	int max_personajes_hambrientos;
	int aliados;
	int v_ingredientes;
	int max_ingredientes;
	int v_items_de_vida;
	int max_items_de_vida;
	int v_items_de_velocidad;
	int max_items_de_velocidad;
	int saqueadores;
	int v_personajes_secundarios;
	int v_saqueadores;
	ll tiempo;
};


short velocidad = 3;
float volumen_sonido_mapa = 50.0f;

// Utilidades

void gotoxy(int x, int y) {
	Console::SetCursorPosition(x, y);
}

void definir_pantalla() {
	Console::SetWindowSize(WIDTH, HEIGHT);
}

void bienvenida() {
	ll* tiempo = new ll;
	*tiempo = 0;
	int xl = WIDTH / 2 - 22, x = WIDTH / 2 - 17,
		xg = WIDTH / 2 - 13, y = HEIGHT / 2 - 15 / 2;
	gotoxy(x, y); cout << "+-+-+-+-+-+ +-+ +-+-+-+-+-+-+-+-+";
	gotoxy(x, y + 1); cout << "|G|R|U|P|O| |6| |P|R|E|S|E|N|T|A|";
	gotoxy(x, y + 2); cout << "+-+-+-+-+-+ +-+ +-+-+-+-+-+-+-+-+";
	gotoxy(xg, y + 3); cout << R"(	    /___/\_)";
	gotoxy(xg, y + 4); cout << R"(    _\   \/_/\__)";
	gotoxy(xg, y + 5); cout << R"(  __\       \/_/\)";
	gotoxy(xg, y + 6); cout << R"(  \   __    __ \ \)";
	gotoxy(xg, y + 7); cout << R"( __\  \_\   \_\ \ \   __)";
	gotoxy(xg, y + 8); cout << R"(/_/\\   __   __  \ \_/_/\)";
	gotoxy(xg, y + 9); cout << R"(\_\/_\__\/\__\/\__\/_\_\/)";
	gotoxy(xg, y + 10); cout << R"(   \_\/_/\       /_\_\/)";
	gotoxy(xg, y + 11); cout << R"(	      \_\/       \_\/)";
	gotoxy(xl, y + 12); cout << "-------------------------------------------";
	gotoxy(WIDTH / 2 - 19 / 2, y + 13); cout << "Saciando el hambre";
	gotoxy(WIDTH / 2 - 27 / 2, y + 14); cout << "Presione enter para saltar";
	while (*tiempo < seconds(150).asMilliseconds()) {
		if (_kbhit()) {
			char tecla = _getch();
			if (tecla == enter) break;
		}
		*tiempo += 1;
	}
	delete tiempo;
	tiempo = nullptr;
	Console::Clear();
}

void creditos() {
	ll* tiempo = new ll;
	*tiempo = 0;
	int y = HEIGHT / 2 - 4, x = WIDTH / 2;
	gotoxy(x - 9, y + 0); cout << "+-+-+-+-+-+-+-+-+";
	gotoxy(x - 9, y + 1); cout << "|C|R|E|D|I|T|O|S|";
	gotoxy(x - 9, y + 2); cout << "+-+-+-+-+-+-+-+-+";
	gotoxy(x - 65 / 2, y + 3); cout << "Integrantes:             Carrera:                       Secci" << char(162) << "n:";
	gotoxy(x - 65 / 2, y + 4); cout << "- Kevin Chi              Ingenier" << char(161) << "a de Software         SW1C";
	gotoxy(x - 65 / 2, y + 5); cout << "- Miguel Hallasi";
	gotoxy(x - 65 / 2, y + 6); cout << "- Alejandro Oroncoy";
	gotoxy(x - 27 / 2, y + 7); cout << "Presione enter para saltar";
	while (*tiempo < seconds(150).asMilliseconds()) {
		if (_kbhit()) {
			char tecla = _getch();
			if (tecla == enter) break;
		}
		*tiempo += 1;
	}
	delete tiempo;
	tiempo = nullptr;
	Console::Clear();
}


// Mostrar menús

void mostrar_titulo(int x, int& y) {

	gotoxy(x, y); cout << "  _________             .__                   .___              .__    .__                  ___.";
	gotoxy(x, y + 1); cout << R"( /   _____/____    ____ |__|____    ____    __| _/____     ____ |  |   |  |__ _____    _____\_ |_________   ____)";
	gotoxy(x, y + 2); cout << R"( \_____  \\__  \ _/ ___\|  \__  \  /    \  / __ |/  _ \  _/ __ \|  |   |  |  \\__  \  /     \| __ \_  __ \_/ __ \)";
	gotoxy(x, y + 3); cout << R"( /        \/ __ \\  \___|  |/ __ \|   |  \/ /_/ (  <_> ) \  ___/|  |__ |   Y  \/ __ \|  Y Y  \ \_\ \  | \/\  ___/)";
	gotoxy(x, y + 4); cout << R"(/_______  (____  /\___  >__(____  /___|  /\____ |\____/   \___  >____/ |___|  (____  /__|_|  /___  /__|    \___  >)";
	gotoxy(x, y + 5); cout << R"(        \/     \/     \/        \/     \/      \/             \/            \/     \/      \/    \/            \/ )";

}

void mostrar_nivel(int& nivel, bool seleccionado, int y) {
	int x = nivel * (WIDTH / (NIVELES + 1)) - 2.5;

	if (seleccionado) Console::ForegroundColor = ConsoleColor::Magenta;

	gotoxy(x, y);
	cout << "  Nivel";
	y++;

	for (int i = 0; i < 5; i++) {
		gotoxy(x, y);
		for (int j = 0; j < 5; j++) {
			if (j == 2 && i == 2) cout << nivel << " ";
			else if (j == 0 || i == 0 || j == 4 || i == 4) cout << "* ";
			else cout << "  ";
		}
		y = Console::CursorTop + 1;
	}

	if (seleccionado) Console::ForegroundColor = ConsoleColor::White;


}



int seleccionar_nivel() {
	int opcion = 1, x = WIDTH / 2 - 21, y = HEIGHT / 2 - 16 / 2;
	char caracter;
	gotoxy(x, y); cout << "	   _   _______    __________    ___________" << endl;
	gotoxy(x, y + 1); cout << "   / | / /  _/ |  / / ____/ /   / ____/ ___/" << endl;
	gotoxy(x, y + 2); cout << "  /  |/ // / | | / / __/ / /   / __/  \\__ \\" << endl;
	gotoxy(x, y + 3); cout << " / /|  // /  | |/ / /___/ /___/ /___ ___/ /" << endl;
	gotoxy(x, y + 4); cout << "/_/ |_/___/  |___/_____/_____/_____//____/" << endl;
	gotoxy(WIDTH / 2 - 26, y + 14);
	cout << "Escoge entre los niveles usando las direccionales [" << char(174) << "," << char(175) << "]";
	gotoxy(WIDTH / 2 - 19, y + 15);
	cout << "Presiona enter para elegir el nivel...";
	for (int i = 1; i <= NIVELES; i++) {
		mostrar_nivel(i, opcion == i, y + 7);
	}
	do {
		caracter = _getch();
		if (caracter == izquierda) {
			mostrar_nivel(opcion, false, y + 7);
			opcion--;
			if (opcion < 1) opcion = NIVELES;
			mostrar_nivel(opcion, true, y + 7);
		};
		if (caracter == derecha) {
			mostrar_nivel(opcion, false, y + 7);
			opcion++;
			if (opcion > NIVELES) opcion = 1;
			mostrar_nivel(opcion, true, y + 7);
		};

	} while (caracter != enter);
	return opcion - 1;
}



void mostrar_instrucciones() {
	Console::Clear();
	cout << R"(

    INSTRUCCIONES

    -El objetivo del juego es alimentar a todos los seres hambrientos del nivel dentro del limite de tiempo
    -Los seres hambrientos apareceran conforme vayas alimentandolos
    -Para conseguir comida para alimentarlos tendras que recolectar ingredientes
    -Una vez que tengas por lo menos ingredientes, podras enviarlo al chef para que 
        cree una comida
    -Una vez que tengas la comida solo faltara acercarte a los seres hambrientos para alimentarlos
    -Si logras alimentarlos a todos ganaras el nivel, si por otro lado se acaba el tiempo o se te 
        acaban las vidas pierdes.
	-Presiona el boton de escape para pausar el juego.

    EL PERSONAJE PRINCIPAL

    -Tu personaje tiene las siguientes caracteristicas:
        Se mueve con las teclas direccionales
        Puede almacenar hasta 3 ingredientes
        Puede almacenar hasta 2 comidas
        Empieza inicialmente con 3 vidas

    ALIADOS Y ENEMIGOS

    -Tu mision es complicada, pero hay companeros que te apoyaran
    -Los aliados son 2: El chef, los repartidores
        El chef prepara comida cuando le llevas ingredientes
        Despues de cierto tiempo apareceran repartidores (aliados), los cuales al tocarlos te daran una
			comida instantanea.

    -Cuidado, por tu camino te encontraras a agentes dispuestos a interrumpir tu cometido
        Los agentes estan distribuidos por el mapa
        Si un aliado o el jugador los tocan, sera eliminado o en el caso del jugador perdera una vida

    POWER-UPS y PODER ESPECIAL

    -Por el mapa puede aparecer un power-up, que te dara una vida extra.
        
    -El tiempo es corto y se debe alimentar a mucha gente, pero no te preocupes, tienes una habilidad especial
        Puedes precionar la barra espaciadora para alimentar automaticamente a todos los seres
            hambrientos de la pantalla, luego de ello tendra que recargarse antes de volver a usarla)";
	cout << "\n\n";
	system("pause");
}

// Asignar Niveles

void actualizar_nivel(Nivel& nivel, short& nivel_seleccionado) {
	nivel.v_personajes_secundarios = 250 - 50 * velocidad;
	nivel.v_saqueadores = nivel.v_personajes_secundarios * (31 / 30 - (7 / 20) * nivel_seleccionado);
}

Nivel* generar_niveles() {
	Nivel* niveles = new Nivel[NIVELES];
	for (int i = 0; i < NIVELES; i++) {
		niveles[i].aliados = 2;
		niveles[i].saqueadores = 3;
		niveles[i].personajes_hambrientos = 4.5 + 5 * (i + 1);
		niveles[i].max_personajes_hambrientos = 3;
		niveles[i].tiempo = 60 * (3 + i * 0.15) * MILISEGUNDOS;
		niveles[i].v_ingredientes = 4 * MILISEGUNDOS;
		niveles[i].max_ingredientes = 4;
		// niveles[i].v_items_de_velocidad = 70 * MILISEGUNDOS;
		niveles[i].v_items_de_vida = 70 * MILISEGUNDOS;
		// niveles[i].max_items_de_velocidad = 1;
		niveles[i].max_items_de_vida = 1;
		niveles[i].v_personajes_secundarios = 250 - 50 * velocidad;
		niveles[i].v_saqueadores = niveles[i].v_personajes_secundarios * (31 / 30 - (7 / 20) * i);
	}

	return niveles;
}


void pintar_mapa(short nivel, int mapa[FILAS][COLUMNAS], bool solo_pintar = false) {
	if (nivel == 0) {

		int x = WIDTH / 2 - 40, y = HEIGHT / 2 - 25 / 2;
		int mapa_temporal[FILAS][COLUMNAS] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		};

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 80; j++) {
				if (!solo_pintar) mapa[i][j] = mapa_temporal[i][j];
				gotoxy(x + j, y + i);

				if (mapa[i][j] == 1) Console::ForegroundColor = ConsoleColor::DarkCyan;
				if (mapa[i][j] == 0) Console::ForegroundColor = ConsoleColor::Black;
				if (mapa[i][j] == 2) Console::ForegroundColor = ConsoleColor::White;
				if (mapa[i][j] == 3) Console::ForegroundColor = ConsoleColor::Blue;
				cout << char(219);
			}
		}
		Console::ForegroundColor = ConsoleColor::White;
	}
	if (nivel == 1) {

		int x = WIDTH / 2 - 40, y = HEIGHT / 2 - 25 / 2;
		int mapa_temporal[FILAS][COLUMNAS] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,3,3,3,3,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,2,2,2,2,2,2,2,2,1},
			{1,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 80; j++) {
				if (!solo_pintar) mapa[i][j] = mapa_temporal[i][j];
				gotoxy(x + j, y + i);

				if (mapa[i][j] == 1) Console::ForegroundColor = ConsoleColor::DarkMagenta;
				if (mapa[i][j] == 0) Console::ForegroundColor = ConsoleColor::Black;
				if (mapa[i][j] == 2) Console::ForegroundColor = ConsoleColor::White;
				if (mapa[i][j] == 3) Console::ForegroundColor = ConsoleColor::Blue;
				cout << char(219);
			}
		}
		Console::ForegroundColor = ConsoleColor::White;
	}
	if (nivel == 2) {

		int x = WIDTH / 2 - 40, y = HEIGHT / 2 - 25 / 2;
		int mapa_temporal[FILAS][COLUMNAS] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 80; j++) {
				if (!solo_pintar) mapa[i][j] = mapa_temporal[i][j];
				gotoxy(x + j, y + i);

				if (mapa[i][j] == 1) Console::ForegroundColor = ConsoleColor::Yellow;
				if (mapa[i][j] == 0) Console::ForegroundColor = ConsoleColor::Black;
				if (mapa[i][j] == 2) Console::ForegroundColor = ConsoleColor::White;
				if (mapa[i][j] == 3) Console::ForegroundColor = ConsoleColor::Blue;
				cout << char(219);
			}
		}
		Console::ForegroundColor = ConsoleColor::White;
	}
}

bool revisar_colision_personaje(int& xj, int& yj, Personaje personaje) {
	return (
		(
			personaje.x <= xj && xj <= personaje.x + 2 ||
			personaje.x <= xj + 2 && xj + 2 <= personaje.x + 2
			) && yj == personaje.y
		);
}

bool revisar_colision_coords(int& xj, int& yj, int& base_x, int& base_y, Coordenadas coords) {
	return (
		(
			coords.x + base_x <= xj && xj <= base_x + coords.x + 2 ||
			coords.x + base_x <= xj + 2 && xj + 2 <= base_x + coords.x + 2
			) && yj == base_y + coords.y
		);
}

bool revisar_colision_item(int& xj, int& yj, Item item) {
	return (
		(xj <= item.x && item.x <= xj + 2)
		&& yj == item.y
		);
}

Personaje* colision_personajes(int x, int y, Personaje* personajes, int& l_personajes) {
	for (int i = 0; i < l_personajes; i++) {
		if (personajes[i].en_pantalla && revisar_colision_personaje(x, y, personajes[i])) return &personajes[i];
	}
	return nullptr;
}

Item* colision_items(int x, int y, Item* items, int& l_items) {
	for (int i = 0; i < l_items; i++) {
		if (items[i].en_pantalla && revisar_colision_item(x, y, items[i])) return &items[i];
	}
	return nullptr;
}

// Generar mapa

Coordenadas generar_coords_rectangulo_chef(int mapa[FILAS][COLUMNAS], int& base_x, int& base_y) {
	Coordenadas coords;
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (mapa[i][j] == 3) {
				coords.x = base_x + j;
				coords.y = base_y + i;
				break;
			};
		}
	}
	return coords;
}

bool igual_posicion_saqueador(Personaje* saqueadores, int& l_saqueadores, int x, int y) {
	bool igual_posicion = false;
	for (int i = 0; i < l_saqueadores; i++) {
		if (saqueadores[i].vertical ? (
			saqueadores[i].x == x ||
			saqueadores[i].x + 1 == x ||
			saqueadores[i].x + 2 == x
			) : saqueadores[i].y == y
			) {
			igual_posicion = true;
			break;
		};
	}
	return igual_posicion;
}

Coordenadas generar_x_y(int& xj, int& yj, int& base_x, int& base_y, int mapa[FILAS][COLUMNAS], Personaje* saqueadores, int& l_saqueadores,
	int l_personajes_hambrientos = -1, Personaje* personajes_hambrientos = nullptr,
	int l_items = -1, Item* items = nullptr, int l_aliados = -1, Personaje* aliados = nullptr) {
	Random r;
	Coordenadas coords, coords_rectangulo_chef = generar_coords_rectangulo_chef(mapa, base_x, base_y);
	do {
		coords.x = r.Next(0, COLUMNAS);
		coords.y = r.Next(0, FILAS);
	} while (
		mapa[coords.y][coords.x] != 0 || mapa[coords.y][coords.x + 1] != 0 || mapa[coords.y][coords.x + 2] != 0
		|| coords.x > coords_rectangulo_chef.x - 2 && coords.x < coords_rectangulo_chef.x + 7 && coords.y < 3
		|| igual_posicion_saqueador(saqueadores, l_saqueadores, base_x + coords.x, base_y + coords.y)
		|| l_personajes_hambrientos > 0 && colision_personajes(base_x + coords.x, base_y + coords.y, personajes_hambrientos, l_personajes_hambrientos) != nullptr
		|| l_aliados > 0 && colision_personajes(base_x + coords.x, base_y + coords.y, aliados, l_aliados) != nullptr
		|| revisar_colision_coords(xj, yj, base_x, base_y, coords)
		|| l_items > 0 && colision_items(base_x + coords.x, base_y + coords.y, items, l_items) != nullptr
		);
	coords.x += base_x;
	coords.y += base_y;
	return coords;
}


// Información de la partida

void HUD(int& vidas, int& ingredientes, int& personajes_hambrientos, int& comida, Nivel nivel, ll& tiempo) {
	gotoxy(WIDTH / 2 - 42 - vidas, 1);
	for (int i = 0; i < vidas - 1; i++) {
		cout << " ";
	}
	cout << "[Vidas: ";
	Console::ForegroundColor = ConsoleColor::Red;
	for (short i = 0; i < vidas; i++) {
		cout << char(3) << " ";
	}
	Console::ForegroundColor = ConsoleColor::White;
	cout << "] Ingredientes[";
	for (int i = 0; i < 3; i++) {
		if (i < ingredientes) {
			Console::ForegroundColor = ConsoleColor::Green;
			cout << " " << char(5) << " ";
			Console::ForegroundColor = ConsoleColor::White;
		}
		else cout << " - ";
		cout << (i != 2 ? "|" : "");
	};
	cout << "] Gente hambrienta[" << personajes_hambrientos << "] Comida[";
	for (int i = 0; i < 2; i++) {
		if (i < comida) cout << " 1 ";
		else cout << " - ";
		cout << (i != 1 ? "|" : "");
	};
	cout << "] ";
	ll tiempoMostrado = nivel.tiempo - tiempo;
	int minutos = trunc(tiempoMostrado / (MILISEGUNDOS * 60));
	int segundos = (tiempoMostrado % (MILISEGUNDOS * 60)) / MILISEGUNDOS;

	cout << "Tiempo: " << (minutos < 10 ? "0" : "") << minutos << "m " << (segundos < 10 ? "0" : "") << segundos << "s   ";
}
void actualizar_valor(int& valor, int nuevo_valor) {
	valor = nuevo_valor;
}


// Funciones del jugador

void usar_power_up_especial(int& barra_de_poder, Personaje* personajes_hambrientos,
	int& l_nivel_personajes_hambrientos, int& max_nivel_personajes_hambrientos, int& ph_en_pantalla,
	bool& listo_barra_de_poder) {

	if (listo_barra_de_poder) {
		for (short i = 0; i < min(l_nivel_personajes_hambrientos, max_nivel_personajes_hambrientos); i++) {
			if (personajes_hambrientos[i].en_pantalla) {
				personajes_hambrientos[i].en_pantalla = false;
				gotoxy(personajes_hambrientos[i].x, personajes_hambrientos[i].y); cout << "   ";
			}
		}
		actualizar_valor(l_nivel_personajes_hambrientos,
			l_nivel_personajes_hambrientos < max_nivel_personajes_hambrientos ? 0 :
			l_nivel_personajes_hambrientos - max_nivel_personajes_hambrientos
		);
		actualizar_valor(barra_de_poder, 0);
		actualizar_valor(ph_en_pantalla, 0);
		listo_barra_de_poder = false;
	}
}


// Funciones de los personajes secundarios

void generar_jugador() {
	cout << "<o>";
}

void borrar_personaje(int& x, int& y) {
	gotoxy(x, y); cout << "   ";
}

void mover_jugador(int& x, int& y, int& base_x, int& base_y, int mapa[FILAS][COLUMNAS], int& vidas, int& comida, int& ingredientes,
	Personaje* personajes_hambrientos, int& l_nivel_personajes_hambrientos, Item* items,
	Personaje* saqueadores, int& l_items, Nivel& nivel, int& ph_en_pantalla, int& barra_de_poder, bool& listo_barra_de_poder,
	bool& pausa
) {
	int x_matriz, y_matriz;
	if (_kbhit())
	{
		char tecla = _getch();
		x_matriz = x - base_x;
		y_matriz = y - base_y;
		//borrar
		int _x = x;
		int _y = y;
		if (tecla == escape) pausa = true;

		if (tecla == 32)
			usar_power_up_especial(barra_de_poder, personajes_hambrientos, l_nivel_personajes_hambrientos,
				nivel.max_personajes_hambrientos, ph_en_pantalla, listo_barra_de_poder);

		if (tecla == derecha && (mapa[y_matriz][x_matriz + 3] == 0 || mapa[y_matriz][x_matriz + 3] == 3))
		{
			borrar_personaje(x, y); x++;
		}
		if (tecla == izquierda && (mapa[y_matriz][x_matriz - 1] == 0 || mapa[y_matriz][x_matriz - 1] == 3))
		{
			borrar_personaje(x, y); x--;
		}
		if (tecla == arriba && (
			mapa[y_matriz - 1][x_matriz] == 0 && mapa[y_matriz - 1][x_matriz + 1] == 0 && mapa[y_matriz - 1][x_matriz + 2] == 0 ||
			mapa[y_matriz - 1][x_matriz] == 3 || mapa[y_matriz - 1][x_matriz + 1] == 3 || mapa[y_matriz - 1][x_matriz + 2] == 3
			))
		{
			borrar_personaje(x, y); y--;
		}
		if (tecla == abajo && (
			mapa[y_matriz + 1][x_matriz] == 0 && mapa[y_matriz + 1][x_matriz + 1] == 0 && mapa[y_matriz + 1][x_matriz + 2] == 0 ||
			mapa[y_matriz + 1][x_matriz] == 3 || mapa[y_matriz + 1][x_matriz + 1] == 3 || mapa[y_matriz + 1][x_matriz + 2] == 3
			))
		{
			borrar_personaje(x, y); y++;
		}

		x_matriz = x - base_x;
		y_matriz = y - base_y;

		Personaje* personaje_hambriento_colisionado = colision_personajes(x, y, personajes_hambrientos, nivel.max_personajes_hambrientos);
		Item* item_colisionado = colision_items(x, y, items, l_items);
		// colision
		if (mapa[y_matriz][x_matriz] == 3 && mapa[y_matriz][x_matriz + 2] == 3) {
			if (ingredientes >= 2) {
				actualizar_valor(ingredientes, comida == 2 ? ingredientes : ingredientes - 2);
				actualizar_valor(comida, comida == 2 ? comida : comida + 1);
			}
		}
		else {
			if (personaje_hambriento_colisionado != nullptr) {
				if (comida <= 0) {
					x = _x;
					y = _y;
				}
				else {
					Media::SoundPlayer sonido;
					sonido.SoundLocation = ".\\assets\\alimentar.wav";
					sonido.Play();
					actualizar_valor(ph_en_pantalla, ph_en_pantalla - 1);
					personaje_hambriento_colisionado->en_pantalla = false;
					gotoxy(personaje_hambriento_colisionado->x, personaje_hambriento_colisionado->y); cout << "   ";
					actualizar_valor(l_nivel_personajes_hambrientos, l_nivel_personajes_hambrientos - 1);
					actualizar_valor(comida, comida - 1);
				}
			}
			if (item_colisionado != nullptr) {
				item_colisionado->en_pantalla = false;
				gotoxy(item_colisionado->x, item_colisionado->y); cout << "   ";
				if (item_colisionado->tipo == 'I') {
					actualizar_valor(ingredientes, ingredientes == 3 ? ingredientes : ingredientes + 1);
					Media::SoundPlayer sonido;
					sonido.SoundLocation = ".\\assets\\recoger_ingredientes.wav";
					sonido.Play();
				}
				if (item_colisionado->tipo == 'H') {
					Media::SoundPlayer sonido;
					sonido.SoundLocation = ".\\assets\\ganar_vida.wav";
					sonido.Play();
					actualizar_valor(vidas, vidas + 1);
				}
			}
		}

		gotoxy(x, y);
		generar_jugador();

	}
}

void mover_saqueador(Personaje& saqueador, int mapa[FILAS][COLUMNAS], int base_x, int base_y,
	int& xj, int& yj, int& vidas, int& ingredientes, int& comida, ll& tiempo, int& v_personajes_secundarios) {
	int _y = saqueador.y - base_y, _x = saqueador.x - base_x;
	saqueador.velocidad = v_personajes_secundarios;
	if (tiempo % saqueador.velocidad == 0) {
		if (saqueador.vertical == 1) {
			if (saqueador.y > base_y && saqueador.y < base_y + FILAS) {
				Console::ForegroundColor = ConsoleColor::Black;
				gotoxy(saqueador.x, saqueador.y); cout << "   ";

				Console::ForegroundColor = ConsoleColor::DarkRed;


				if (saqueador.vuelta && mapa[int(_y + 1)][_x] != 0
					|| mapa[int(_y + 1)][_x + 1] != 0
					|| mapa[int(_y + 1)][_x + 2] != 0) saqueador.vuelta = false;


				if (!saqueador.vuelta && mapa[int(_y - 1)][_x] != 0
					|| mapa[int(_y - 1)][_x + 1] != 0
					|| mapa[int(_y - 1)][_x + 2] != 0) saqueador.vuelta = true;


				if (saqueador.vuelta) saqueador.y++;
				else saqueador.y--;

				gotoxy(saqueador.x, saqueador.y); cout << caracter_saqueador;
				Console::ForegroundColor = ConsoleColor::White;
			}
		}
		else {
			if (saqueador.x > base_x && saqueador.x < base_x + COLUMNAS) {
				Console::ForegroundColor = ConsoleColor::Black;
				gotoxy(saqueador.x, saqueador.y); cout << "   ";

				Console::ForegroundColor = ConsoleColor::DarkRed;


				if (saqueador.vuelta && mapa[_y][int(_x + 3)] != 0) saqueador.vuelta = false;


				if (!saqueador.vuelta && mapa[_y][int(_x - 1)] != 0) saqueador.vuelta = true;


				if (saqueador.vuelta) saqueador.x++;
				else saqueador.x--;

				gotoxy(saqueador.x, saqueador.y); cout << caracter_saqueador;
				Console::ForegroundColor = ConsoleColor::White;
			}
		}
	}

	// revisar si a mato al jugador
	bool colision = revisar_colision_personaje(xj, yj, saqueador);
	if (colision) {

		Media::SoundPlayer sonido;
		sonido.SoundLocation = ".\\assets\\perder_vida.wav";
		sonido.Play();

		borrar_personaje(xj, yj);
		actualizar_valor(vidas, vidas - 1);
		actualizar_valor(ingredientes, 0);
		actualizar_valor(comida, 0);
		xj = base_x + COLUMNAS / 2 - 1.5;
		yj = base_y + FILAS / 2;
		gotoxy(xj, yj); generar_jugador();

		return;
	}


}


void mover_aliado(Personaje& aliado, int mapa[FILAS][COLUMNAS], int base_x, int base_y, int& xj, int& yj,
	int& vidas, int& ingredientes, int& comida,
	ll& tiempo, Personaje* saqueadores, int& l_saqueadores, int& v_personajes_secundarios) {
	int _y = aliado.y - base_y, _x = aliado.x - base_x;
	aliado.velocidad = v_personajes_secundarios;
	if (tiempo % aliado.velocidad == 0) {
		if (aliado.vertical == 1) {
			if (aliado.y > base_y && aliado.y < base_y + FILAS) {
				Console::ForegroundColor = ConsoleColor::Black;
				gotoxy(aliado.x, aliado.y); cout << "   ";

				Console::ForegroundColor = ConsoleColor::Yellow;


				if (aliado.vuelta && mapa[int(_y + 1)][_x] != 0
					|| mapa[int(_y + 1)][_x + 1] != 0
					|| mapa[int(_y + 1)][_x + 2] != 0) aliado.vuelta = false;


				if (!aliado.vuelta && mapa[int(_y - 1)][_x] != 0
					|| mapa[int(_y - 1)][_x + 1] != 0
					|| mapa[int(_y - 1)][_x + 2] != 0) aliado.vuelta = true;


				if (aliado.vuelta) aliado.y++;
				else aliado.y--;

				gotoxy(aliado.x, aliado.y); cout << caracter_aliado;
				Console::ForegroundColor = ConsoleColor::White;
			}
		}
		else {
			if (aliado.x > base_x && aliado.x < base_x + COLUMNAS) {
				Console::ForegroundColor = ConsoleColor::Black;
				gotoxy(aliado.x, aliado.y); cout << "   ";

				Console::ForegroundColor = ConsoleColor::Yellow;


				if (aliado.vuelta && mapa[_y][int(_x + 3)] != 0) aliado.vuelta = false;


				if (!aliado.vuelta && mapa[_y][int(_x - 1)] != 0) aliado.vuelta = true;


				if (aliado.vuelta) aliado.x++;
				else aliado.x--;

				gotoxy(aliado.x, aliado.y); cout << caracter_aliado;
				Console::ForegroundColor = ConsoleColor::White;
			}
		}
	}

	// revisar si a mato al jugador
	bool colision_jugador = revisar_colision_personaje(xj, yj, aliado);
	Personaje* colision_saqueador = colision_personajes(aliado.x, aliado.y, saqueadores, l_saqueadores);

	if (colision_jugador) {
		actualizar_valor(comida, comida == 2 ? comida : comida + 1);
		borrar_personaje(aliado.x, aliado.y);
		aliado.en_pantalla = false;
	}

	if (colision_saqueador != nullptr) {
		borrar_personaje(aliado.x, aliado.y);
		aliado.en_pantalla = false;
		return;
	}

}

void generar_chef(int chef_x, int chef_y) {
	gotoxy(chef_x, chef_y); cout << "chef";
}

// Generación de items

Item generar_item(int x, int y, int base_x, int base_y, int mapa[FILAS][COLUMNAS], Personaje* saqueadores, int& l_saqueadores,
	Personaje* personajes_hambrientos, int l_personajes_hambrientos, bool en_pantalla = false, char tipo = 'I') {
	Coordenadas coords = generar_x_y(x, y, base_x, base_y, mapa, saqueadores, l_saqueadores, l_personajes_hambrientos, personajes_hambrientos);
	Item item;
	item.x = coords.x;
	item.y = coords.y;
	item.en_pantalla = en_pantalla;
	item.tipo = tipo;
	return item;
}


// Generaciones de personajes del juego 

Personaje generar_aliado(int x, int y, int base_x, int base_y, int velocidad, int mapa[FILAS][COLUMNAS],
	Personaje* saqueadores, int& l_saqueadores, Personaje* personajes_hambrientos,
	int l_personajes_hambrientos, bool en_pantalla = false) {
	Random r;
	Coordenadas coords = generar_x_y(x, y, base_x, base_y, mapa, saqueadores, l_saqueadores);
	Personaje aliado;
	aliado.x = coords.x;
	aliado.vertical = r.Next(0, 2);
	aliado.y = coords.y;
	aliado.velocidad = velocidad;
	aliado.en_pantalla = en_pantalla;
	return aliado;
}

Personaje generar_saqueador(int x, int y, int velocidad, bool vertical, bool vuelta = false) {
	Personaje saqueador;
	saqueador.x = x;
	saqueador.y = y;
	saqueador.velocidad = velocidad;
	saqueador.vertical = vertical;
	saqueador.vuelta = vuelta;
	Console::ForegroundColor = ConsoleColor::DarkRed;
	gotoxy(saqueador.x, saqueador.y); cout << caracter_saqueador;
	Console::ForegroundColor = ConsoleColor::White;
	return saqueador;
}

Personaje generar_personaje_hambriento(int x, int y, int base_x, int base_y, int mapa[FILAS][COLUMNAS], Personaje* saqueadores, int& l_saqueadores,
	Personaje* personajes_hambrientos, int& l_personajes_hambrientos, bool en_pantalla = false) {
	Coordenadas coords = generar_x_y(x, y, base_x, base_y, mapa, saqueadores, l_saqueadores, l_personajes_hambrientos, personajes_hambrientos);
	Personaje personaje_hambriento;
	personaje_hambriento.x = coords.x;
	personaje_hambriento.y = coords.y;
	personaje_hambriento.en_pantalla = en_pantalla;
	return personaje_hambriento;
}


void pintar_rectangulo_chef(int mapa[FILAS][COLUMNAS], int& base_x, int& base_y, int& x, int& y, Coordenadas& coords) {
	int _x = coords.x, _y = coords.y;
	Console::BackgroundColor = ConsoleColor::Blue;

	for (int i = 0; i < 4; i++) {
		gotoxy(_x + i, _y);
		if (_y == y) {
			if (x == _x + i || x + 1 == _x + i || x + 2 == _x + i) {
				if (x == _x + i) {
					cout << "<";
				}
				if (x + 1 == _x + i) {
					cout << "o";
				}
				if (x + 2 == _x + i) {
					cout << ">";
				}
			}
			else {
				cout << ' ';
			}
		}
		else {
			cout << ' ';
		}
	}
	Console::BackgroundColor = ConsoleColor::Black;
}


// Animaciones

void animacion_de_victoria() {
	string message = "Ganaste, compa :D";
	Console::Clear();
	gotoxy(WIDTH / 2 - message.length() / 2, HEIGHT / 2);
	for (int i = 0; i < message.length(); i++) {
		cout << message[i];
		_sleep(100);
	}
}

void animacion_de_perdida() {
	string message = "Perdiste, compa :'(";
	Console::Clear();
	gotoxy(WIDTH / 2 - message.length() / 2, HEIGHT / 2);
	for (int i = 0; i < message.length(); i++) {
		cout << message[i];
		_sleep(100);
	}
}



void pintar_barra_de_poder(ll& tiempo, int& barra_de_poder, bool& listo) {
	string message = "Presiona espacio para activar";
	const int MAX_BARRA = 15;
	int l = MAX_BARRA * 2 + 3;

	gotoxy(WIDTH / 2 - l / 2, HEIGHT - 2);
	cout << "[";
	if (tiempo > 0 && tiempo % (MILISEGUNDOS * 4) == 0) {
		barra_de_poder = (barra_de_poder < MAX_BARRA) ? barra_de_poder + 1 : MAX_BARRA;
	}

	if (barra_de_poder < MAX_BARRA) {
		for (short i = 0; i < MAX_BARRA; i++) {
			if (i < barra_de_poder) {
				cout << char(219) << char(219);
			}
			else {
				cout << "  ";
			}
		}
	}
	else {
		Console::BackgroundColor = ConsoleColor::White;
		Console::ForegroundColor = ConsoleColor::Black;
		for (short i = 0; i < message.length(); i++) {
			cout << message[i];
		}
		Console::BackgroundColor = ConsoleColor::Black;
		Console::ForegroundColor = ConsoleColor::White;
	}
	if (barra_de_poder == MAX_BARRA) listo = true;
	cout << "]";
	cout << " " << (barra_de_poder * 100 / MAX_BARRA) << "%  ";
}

// Funcionas de victoria, y perdida

bool victoria(short& nivel_seleccionado) {
	int tecla;
	animacion_de_victoria();

	do {
		Console::Clear();
		if (nivel_seleccionado >= 3) {
			gotoxy(WIDTH / 2 - 42, HEIGHT / 2);
			cout << "Ganaste el juego, presiona 1 para regresar al nivel 1 o 2 para regresar al menu... ";
		}
		else {
			gotoxy(WIDTH / 2 - 41, HEIGHT / 2);
			cout << "Ganaste, presiona 1 para avanzar al siguiente nivel o 2 para regresar al menu... ";
		}
		cin >> tecla;
	} while (tecla != 1 && tecla != 2);
	if (tecla == 1 && nivel_seleccionado >= 3) nivel_seleccionado = 0;
	return (tecla == 1);
}

bool perdida() {
	int tecla;
	animacion_de_perdida();
	do {
		Console::Clear();
		gotoxy(WIDTH / 2 - 36, HEIGHT / 2);
		cout << "Perdiste, presiona 1 para volver a jugar o 2 para salir del programa... ";
		cin >> tecla;
	} while (tecla != 1 && tecla != 2);
	return (tecla == 1);
}

void pintar_barra_volumen(float& volumen, int& y, bool activo) {
	gotoxy(WIDTH / 2 - 77 / 2, y);
	if (activo) Console::ForegroundColor = ConsoleColor::Magenta;
	cout << "Volumen del fondo: ";
	cout << "[";
	for (int i = 0; i < 50; i++) {
		if (i < volumen / 2) {
			cout << char(219);
		}
		else {
			cout << " ";
		}
	}
	cout << "]";
	cout << " " << volumen << "%  ";
	Console::ForegroundColor = ConsoleColor::White;
}

void pintar_velocidad(short& velocidad, int y, bool activo) {
	gotoxy(WIDTH / 2 - 77 / 2, y);
	if (activo) Console::ForegroundColor = ConsoleColor::Magenta;
	cout << "Velocidad del juego: ";
	cout << "[";
	for (int i = 0; i < 4; i++) {
		if (i < velocidad) {
			cout << char(219) << char(219) << char(219) << char(219);
		}
		else {
			cout << "    ";
		}
	}
	cout << "]";
	cout << " x" << velocidad;
	Console::ForegroundColor = ConsoleColor::White;
}

void imprimir_boton_guardar(int& y, bool activo) {
	if (activo) Console::ForegroundColor = ConsoleColor::Magenta;
	y -= 3 / 2;
	int _x = WIDTH / 2 - 9;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(_x + j * 2, y + i);
			if (i == 0 || j == 0 || i == 4 || j == 8) cout << "* ";
		}
	}
	gotoxy(WIDTH / 2 - 4, y + 2); cout << "Guardar";


	Console::ForegroundColor = ConsoleColor::White;
}

void pintar_opciones(Sound& sonido_mapa, float& volumen, Nivel& nivel, short& nivel_seleccionado) {
	int base_y = HEIGHT / 2;
	short opcion_activo = 1;
	Console::Clear();

	do {
		for (short i = 1; i <= 4; i++) {
			int y = i * (HEIGHT / 5);
			if (i == 1) pintar_barra_volumen(volumen, y, opcion_activo == 1);
			if (i == 2) pintar_velocidad(velocidad, y, opcion_activo == 2);
			if (i == 3) imprimir_boton_guardar(y, opcion_activo == 3);
			if (i == 4) {
				gotoxy(WIDTH / 2 - 81 / 2, y); cout << "Puedes utilizar las flechas direccionales [" << char(24) << "," << char(25) << "] para moverte entre las opciones";
				gotoxy(WIDTH / 2 - 67 / 2, y + 1); cout << "Puedes cambiar el valor utilizando las flechas direccionales [" << char(174) << "," << char(175) << "]";
			}

		}
		if (_kbhit()) {
			char tecla = _getch();
			if (tecla == derecha) {
				if (opcion_activo == 1) {
					volumen += 2.0f;
					if (volumen >= 100.0f) volumen = 100.0f;
					sonido_mapa.setVolume(volumen);
				}
				if (opcion_activo == 2) {
					velocidad += 1;
					if (velocidad >= 4) velocidad = 4;
					actualizar_nivel(nivel, nivel_seleccionado);
				}
			}
			if (tecla == izquierda) {
				if (opcion_activo == 1) {
					volumen -= 2.0f;
					if (volumen <= 0.0f) volumen = 0.0f;
					sonido_mapa.setVolume(volumen);
				}
				if (opcion_activo == 2) {
					velocidad -= 1;
					if (velocidad <= 1) velocidad = 1;
					actualizar_nivel(nivel, nivel_seleccionado);
				}
			}
			if (tecla == arriba) {
				opcion_activo--;
				if (opcion_activo <= 0) opcion_activo = 3;
			}
			if (tecla == abajo) {
				opcion_activo++;
				if (opcion_activo >= 4) opcion_activo = 1;
			}

			if (tecla == enter && opcion_activo == 3) break;
		}
	} while (1);

}

void pintar_configuracion(float& volumen) {
	int base_y = HEIGHT / 2;
	short opcion_activo = 1;
	Console::Clear();

	do {
		for (short i = 1; i <= 4; i++) {
			int y = i * (HEIGHT / 5);
			if (i == 1) pintar_barra_volumen(volumen, y, opcion_activo == 1);
			if (i == 2) pintar_velocidad(velocidad, y, opcion_activo == 2);
			if (i == 3) imprimir_boton_guardar(y, opcion_activo == 3);
			if (i == 4) {
				gotoxy(WIDTH / 2 - 81 / 2, y); cout << "Puedes utilizar las flechas direccionales [" << char(24) << "," << char(25) << "] para moverte entre las opciones";
				gotoxy(WIDTH / 2 - 67 / 2, y + 1); cout << "Puedes cambiar el valor utilizando las flechas direccionales [" << char(174) << "," << char(175) << "]";
			}

		}
		if (_kbhit()) {
			char tecla = _getch();
			if (tecla == derecha) {
				if (opcion_activo == 1) {
					volumen += 2.0f;
					if (volumen >= 100.0f) volumen = 100.0f;
				}
				if (opcion_activo == 2) {
					velocidad += 1;
					if (velocidad >= 4) velocidad = 4;
				}
			}
			if (tecla == izquierda) {
				if (opcion_activo == 1) {
					volumen -= 2.0f;
					if (volumen <= 0.0f) volumen = 0.0f;
				}
				if (opcion_activo == 2) {
					velocidad -= 1;
					if (velocidad <= 1) velocidad = 1;
				}
			}
			if (tecla == arriba) {
				opcion_activo--;
				if (opcion_activo <= 0) opcion_activo = 3;
			}
			if (tecla == abajo) {
				opcion_activo++;
				if (opcion_activo >= 4) opcion_activo = 1;
			}

			if (tecla == enter && opcion_activo == 3) break;
		}
	} while (1);

}

bool poner_pausa(int& xj, int& yj, Sound& sonido_mapa, float& volumen, Nivel& nivel, short& nivel_seleccionado, int mapa[FILAS][COLUMNAS], bool& pausa, int& chef_x, int& chef_y) {
	sonido_mapa.pause();
	Console::Clear();
	short opcion = 1;
	string opciones[3] = { "Regresar al nivel", "Configuracion", "Regresar al menu" };
	Console::ForegroundColor = ConsoleColor::Cyan;
	gotoxy(WIDTH / 2 - opciones[0].length() / 2, HEIGHT / 2 - 2); cout << opciones[0];
	Console::ForegroundColor = ConsoleColor::White;
	gotoxy(WIDTH / 2 - opciones[1].length() / 2, HEIGHT / 2); cout << opciones[1];
	gotoxy(WIDTH / 2 - opciones[2].length() / 2, HEIGHT / 2 + 2); cout << opciones[2];
	char tecla;
	int y = HEIGHT / 2 - 2;
	do {
		if (_kbhit()) {
			tecla = _getch();
			if (tecla == arriba || tecla == abajo) {
				Media::SoundPlayer sonido;
				sonido.SoundLocation = ".\\assets\\menu.wav";
				sonido.Play();
			}
			if (tecla == arriba) {
				Console::ForegroundColor = ConsoleColor::White;
				gotoxy(WIDTH / 2 - opciones[opcion - 1].length() / 2, y); cout << opciones[opcion - 1];

				opcion--;
				if (opcion <= 0) {
					opcion = 3;
					y = HEIGHT / 2 + 2;
				}
				else y -= 2;
				Console::ForegroundColor = ConsoleColor::Cyan;
				gotoxy(WIDTH / 2 - opciones[opcion - 1].length() / 2, y); cout << opciones[opcion - 1];
				Console::ForegroundColor = ConsoleColor::White;
			}
			if (tecla == abajo) {
				Console::ForegroundColor = ConsoleColor::White;
				gotoxy(WIDTH / 2 - opciones[opcion - 1].length() / 2, y); cout << opciones[opcion - 1];
				opcion++;
				if (opcion >= 4) {
					opcion = 1;
					y = HEIGHT / 2 - 2;
				}
				else y += 2;
				Console::ForegroundColor = ConsoleColor::Cyan;
				gotoxy(WIDTH / 2 - opciones[opcion - 1].length() / 2, y); cout << opciones[opcion - 1];
				Console::ForegroundColor = ConsoleColor::White;
			}
		}
	} while (tecla != enter && tecla != escape);

	if (opcion == 3) return true;
	if (opcion == 2) {
		pintar_opciones(sonido_mapa, volumen, nivel, nivel_seleccionado);
	}
	if (opcion == 1 || tecla == escape) {
		pintar_mapa(nivel_seleccionado, mapa, true);
		generar_chef(chef_x, chef_y);
		gotoxy(xj, yj);
		generar_jugador();
		pausa = false;
	}
	return false;
}


void generar_mapa(short& nivel_seleccionado) {
	// SFML
	SoundBuffer buffer_mapa;
	buffer_mapa.loadFromFile(".\\assets\\sonido_principal.ogg");
	Sound sonido_mapa;
	sonido_mapa.setBuffer(buffer_mapa);

	ll tiempo = 0;
	int x, y, vidas = 3, ingredientes = 0, comida = 0, ph_en_pantalla, barra_de_poder = 0;
	bool listo_barra_de_poder = false, pausa = false;
	int chef_x, chef_y;
	int base_x, base_y, mapa[FILAS][COLUMNAS];


	Console::Clear();
	definir_pantalla();

	Nivel* niveles = generar_niveles();

	base_x = WIDTH / 2 - 40, base_y = HEIGHT / 2 - 25 / 2;
	x = base_x + COLUMNAS / 2 - 1.5;
	y = base_y + FILAS / 2;

	Nivel nivel = niveles[nivel_seleccionado];

	HUD(vidas, ingredientes, nivel.personajes_hambrientos, comida, nivel, tiempo);
	pintar_mapa(nivel_seleccionado, mapa);

	sonido_mapa.setLoop(true);
	sonido_mapa.setVolume(volumen_sonido_mapa);
	sonido_mapa.play();

	Coordenadas coords_rectangulo_chef = generar_coords_rectangulo_chef(mapa, base_x, base_y);

	chef_x = coords_rectangulo_chef.x;
	chef_y = base_y + 1;

	ph_en_pantalla = nivel.max_personajes_hambrientos;
	int l_nivel_personajes_hambrientos = nivel.personajes_hambrientos;
	int l_items = nivel.max_ingredientes + nivel.max_items_de_vida;

	Personaje* personajes_hambrientos = new Personaje[nivel.max_personajes_hambrientos];
	Personaje* aliados = new Personaje[nivel.aliados];
	Personaje* saqueadores = new Personaje[nivel.saqueadores];

	Item* items = new Item[l_items];

	generar_chef(chef_x, chef_y);

	for (int i = 0; i < nivel.saqueadores; i++) {
		int _x = 0, _y = 0;
		bool _vertical = false;
		if (nivel_seleccionado == 0) {
			_x = (i == 0 ? 15 : (i == 1 ? 75 : 20));
			_y = (i == 0 ? 9 : (i == 1 ? 11 : 22));
			if (_x == 15 || _x == 20) _vertical = true;
			// nivel 1
		}
		if (nivel_seleccionado == 1) {
			_x = (i == 0 ? 32 : (i == 1 ? 18 : 75));
			_y = (i == 0 ? 14 : (i == 1 ? 21 : 15));
			if (_x == 18) _vertical = true;
		}
		if (nivel_seleccionado == 2) {
			_x = (i == 0 ? 21 : (i == 1 ? 30 : 9));
			_y = (i == 0 ? 7 : (i == 1 ? 13 : 8));
			if (_x == 30) _vertical = true;
			// nivel 3 
		}
		saqueadores[i] = generar_saqueador(_x + base_x, _y + base_y, nivel.v_saqueadores, _vertical);
	};

	for (int i = 0; i < nivel.max_personajes_hambrientos; i++) {
		personajes_hambrientos[i] = generar_personaje_hambriento(x, y, base_x, base_y, mapa, saqueadores, nivel.saqueadores,
			personajes_hambrientos, nivel.max_personajes_hambrientos,
			true);
		personajes_hambrientos[i].idx = i;
		_sleep(0);
	}


	for (int i = 0; i < nivel.aliados; i++) {
		aliados[i] = generar_aliado(x, y, base_x, base_y, nivel.v_personajes_secundarios, mapa, saqueadores, nivel.saqueadores,
			personajes_hambrientos, min(nivel.max_personajes_hambrientos, l_nivel_personajes_hambrientos),
			false);
		personajes_hambrientos[i].idx = i;
		_sleep(0);
	};

	for (int i = 0; i < l_items; i++) {
		items[i] = generar_item(x, y, base_x, base_y, mapa, saqueadores, nivel.saqueadores, personajes_hambrientos, min(nivel.max_personajes_hambrientos, l_nivel_personajes_hambrientos), false, (
			i < nivel.max_ingredientes ? 'I' :
			'H'
			));
		_sleep(0);
	}

	gotoxy(x, y); generar_jugador();

	while (1) {
		if (vidas == 0 || tiempo == nivel.tiempo) {
			sonido_mapa.stop();
			if (perdida()) generar_mapa(nivel_seleccionado);
			break;
		}
		if (l_nivel_personajes_hambrientos == 0) {
			sonido_mapa.stop();
			nivel_seleccionado++;
			if (victoria(nivel_seleccionado)) generar_mapa(nivel_seleccionado);
			break;
		}

		mover_jugador(x, y, base_x, base_y, mapa, vidas, comida, ingredientes, personajes_hambrientos,
			l_nivel_personajes_hambrientos, items, saqueadores,
			l_items, nivel, ph_en_pantalla, barra_de_poder, listo_barra_de_poder, pausa);

		if (pausa) {
			bool detener = poner_pausa(x, y, sonido_mapa, volumen_sonido_mapa, nivel, nivel_seleccionado,
				mapa, pausa, chef_x, chef_y);
			if (detener) break;
			if (!pausa) sonido_mapa.play();
		}

		if (!pausa) pintar_rectangulo_chef(mapa, base_x, base_y, x, y, coords_rectangulo_chef);

		HUD(vidas, ingredientes, l_nivel_personajes_hambrientos, comida, nivel, tiempo);


		for (int i = 0; i < nivel.max_personajes_hambrientos; i++) {
			if (personajes_hambrientos[i].en_pantalla) {
				Console::ForegroundColor = ConsoleColor::White;
				gotoxy(personajes_hambrientos[i].x, personajes_hambrientos[i].y); cout << caracter_hambriento;
			}
			else {
				if (l_nivel_personajes_hambrientos >= nivel.max_personajes_hambrientos || l_nivel_personajes_hambrientos != ph_en_pantalla) {
					Coordenadas coords = generar_x_y(x, y, base_x, base_y, mapa, saqueadores, nivel.saqueadores,
						min(nivel.max_personajes_hambrientos, l_nivel_personajes_hambrientos), personajes_hambrientos, l_items, items, nivel.aliados, aliados);
					personajes_hambrientos[i].x = coords.x;
					personajes_hambrientos[i].y = coords.y;
					personajes_hambrientos[i].en_pantalla = true;
					ph_en_pantalla++;
				}
			}
		}


		for (int i = 0; i < nivel.saqueadores; i++) {
			mover_saqueador(saqueadores[i], mapa, base_x, base_y, x, y, vidas, ingredientes, comida, tiempo, nivel.v_saqueadores);
		};


		for (int i = 0; i < nivel.aliados; i++) {
			if (aliados[i].en_pantalla) {
				mover_aliado(aliados[i], mapa, base_x, base_y, x, y, vidas, ingredientes, comida, tiempo, saqueadores, nivel.saqueadores, nivel.v_personajes_secundarios);
			}
			else {
				if (tiempo > 0 && tiempo % nivel.v_items_de_velocidad == 0) {
					Coordenadas coords = generar_x_y(x, y, base_x, base_y, mapa, saqueadores,
						nivel.saqueadores, min(nivel.max_personajes_hambrientos, l_nivel_personajes_hambrientos),
						personajes_hambrientos, l_items, items, nivel.aliados, aliados
					);
					aliados[i].x = coords.x;
					aliados[i].y = coords.y;
					aliados[i].en_pantalla = true;
				}
			}
		}

		for (int i = 0; i < l_items; i++) {
			if (items[i].en_pantalla) {
				items[i].tipo == 'I' ? Console::ForegroundColor = ConsoleColor::Green :
					(Console::ForegroundColor = ConsoleColor::Red);

				gotoxy(items[i].x, items[i].y);
				cout << (items[i].tipo == 'I' ? char(5) : char(3));
				Console::ForegroundColor = ConsoleColor::White;
			}
			else if (items[i].tipo == 'I' ? tiempo % nivel.v_ingredientes == 0 : tiempo > 0 && tiempo % nivel.v_items_de_velocidad == 0) {
				Coordenadas coords = generar_x_y(x, y, base_x, base_y, mapa, saqueadores, nivel.saqueadores,
					min(nivel.max_personajes_hambrientos, l_nivel_personajes_hambrientos), personajes_hambrientos, l_items, items);
				items[i].x = coords.x;
				items[i].y = coords.y;
				items[i].en_pantalla = true;
			}
		}

		pintar_barra_de_poder(tiempo, barra_de_poder, listo_barra_de_poder);

		tiempo++;
	}
}



// Juego

void juego() {
	Console::Clear();
	short nivel_seleccionado;
	nivel_seleccionado = seleccionar_nivel();

	Console::Clear();
	gotoxy(WIDTH / 2 - 11, HEIGHT / 2); cout << "Cargando nivel " << nivel_seleccionado + 1 << " ...";

	generar_mapa(nivel_seleccionado);
}


void mostrar_menu() {
	string indicador = "=>";
	short opcion = 1;
	int x = WIDTH / 2 - 15, baseY = HEIGHT / 2 - 11 / 2, y;
	y = baseY + 7 + opcion - 1;

	Console::Clear();

	mostrar_titulo(WIDTH / 2 - 57.5, baseY);
	gotoxy(x, baseY + 6); cout << "   " << "---------------";
	Console::ForegroundColor = ConsoleColor::Cyan;
	gotoxy(x, baseY + 7); cout << indicador << " ";
	Console::ForegroundColor = ConsoleColor::White;
	cout << "Iniciar juego";
	gotoxy(x, baseY + 8); cout << "   " << "Instrucciones";
	gotoxy(x, baseY + 9); cout << "   " << "Configuraci" << char(162) << "n";
	gotoxy(x, baseY + 10); cout << "   " << "Salir";

	gotoxy(WIDTH / 2 - 40, baseY + 11); cout << "   " << "Mueve con las flechas direcciones [" << char(24) << "," << char(25) << "] y presione enter para elejir la opci" << char(162) << "n";

	while (1) {
		if (_kbhit()) {
			char caracter = _getch();
			if (caracter == arriba) {
				gotoxy(x, y);
				cout << "   ";
				opcion--;
				y--;
				if (opcion < 1) {
					y = baseY + 10;
					opcion = 4;
				};
				gotoxy(x, y);
				Console::ForegroundColor = ConsoleColor::Cyan;
				cout << indicador;
			}
			if (caracter == abajo) {
				gotoxy(x, y);
				cout << "   ";
				opcion++;
				y++;
				if (opcion > 4) {
					y = baseY + 7;
					opcion = 1;
				};
				gotoxy(x, y);
				Console::ForegroundColor = ConsoleColor::Cyan;
				cout << indicador;
			}
			else if (caracter == enter) {
				Console::ForegroundColor = ConsoleColor::White;
				break;
			};
		}
	}
	

	if (opcion == 1) {
		juego();
		Console::Clear();
		mostrar_menu();
	}
	if (opcion == 2) {
		mostrar_instrucciones();
		Console::Clear();
		mostrar_menu();
	}
	if (opcion == 3) {
		pintar_configuracion(volumen_sonido_mapa);
		Console::Clear();
		mostrar_menu();
	}
	if (opcion == 4) {
		string message = "Ohhh, hasta luego :')";
		Console::Clear();
		gotoxy(WIDTH / 2 - message.length() / 2, HEIGHT / 2);
		for (int i = 0; i < message.length(); i++) {
			cout << message[i];
			_sleep(100);
		}
		exit(0);
	}
}