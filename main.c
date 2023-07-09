#include "lib/lib.h"

#include "lib/define.h"
#include "lib/var.h"

#include "lib/functions.h"
#include "lib/other.h"
#include "lib/easteregg.h"
#include "lib/mainmenu.h"
#include "lib/settingmenu.h"
#include "lib/singleplayer.h"
#include "lib/multiplayer.h"
#include "lib/classifica.h"

int main(int argc, char const *argv[])
{
    Initialize(argc, argv);
    do {} while (MainMenu());
    Terminate();
    return 0;
}