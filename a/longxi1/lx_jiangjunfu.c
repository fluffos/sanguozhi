// this room is created by buzzer.c
// driver is �������
// created date is Sat May  7 12:20:17 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit INDOOR_ROOM;
void setup() {
set_area("longxi");
set_light(50);
set_brief("%^YELLOW%^"+"������"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/longxi/lx_dounanjie3.c",
 ]));
}
