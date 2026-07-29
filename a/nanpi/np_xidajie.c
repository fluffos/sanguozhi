// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Mon May 30 19:31:27 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("nanpi");
set_light(50);
set_brief("%^YELLOW%^"+"西大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/nanpi/np_xiaolu.c",

"south":"/a/nanpi/np_xiaochang.c",

"east":"/a/nanpi/np_fenghuangtai.c",

"west":"/a/nanpi/np_xichengmen.c",

 ]));
}
