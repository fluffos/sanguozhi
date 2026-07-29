// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri May  6 22:00:59 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("wuguan");
set_light(50);
set_brief("%^YELLOW%^"+"大道"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/wuguan/wg_guankou.c",

"south":"/a/wuguan/wg_xiaodian.c",

"west":"/a/wuguan/wg_yingzhai.c",
 ]));
}
