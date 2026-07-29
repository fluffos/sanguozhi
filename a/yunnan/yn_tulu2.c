// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Jun  3 22:08:43 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yunnan");
set_light(50);
set_brief("%^YELLOW%^"+"土路2"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/yunnan/yn_zahuopu.c",

"west":"/a/yunnan/yn_maowu.c",

"north":"/a/yunnan/yn_beichengmen.c",

"south":"/a/yunnan/yn_tulu1.c",
 ]));
}
