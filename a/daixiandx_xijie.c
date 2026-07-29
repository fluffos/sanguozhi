// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Mon May 30 19:54:51 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("daixian");
set_light(50);
set_brief("%^YELLOW%^"+"西街"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/daixiandx_xichengmen.c",

"north":"/a/daixiandx_minfang.c",

"east":"/a/daixiandx_xijie.c",

"west":"/a/daixiandx_xijie.c",
 ]));
}
