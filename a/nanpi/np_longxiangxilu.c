// this room is created by buzzer.c
// driver is ��ɽҹ��
// created date is Mon May 30 19:12:47 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("nanpi");
set_light(50);
set_brief("%^YELLOW%^"+"������·"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/nanpi/np_nandajie.c",

"west":"/a/nanpi/np_machang.c",

"north":"/a/nanpi/np_lianhuachi.c",
 ]));
}
