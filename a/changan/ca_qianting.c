// this room is created by buzzer.c
// driver is �������
// created date is Tue May  3 20:43:23 2011
#include <mudlib.h>
#include <ansi.h>
inherit INDOOR_ROOM;
void setup() {
set_area("changan");
set_light(50);
set_brief("%^YELLOW%^"+"ǰͥ"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/changan/ca_yamen.c",
 ]));
}
