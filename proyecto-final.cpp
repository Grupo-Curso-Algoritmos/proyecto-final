#include "pch.h"
#include "libreriajuego.h"

using namespace System;
using namespace std;

int main()
{
    Console::CursorVisible = false;
    definir_pantalla();
    bienvenida();
    creditos();
    mostrar_menu();

    cin.get();
    cin.ignore();
    return 0;
}