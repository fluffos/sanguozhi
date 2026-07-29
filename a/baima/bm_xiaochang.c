// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Thu Jun  2 21:21:30 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("baima");
set_light(50);
set_brief("%^YELLOW%^"+"校场"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/baima/bm_yingzhai.c",

"south":"/a/baima/bm_suishilu.c",

"east":"/a/baima/bm_yingfang.c",

"west":"/a/baima/bm_tulu.c",
 ]));
}
