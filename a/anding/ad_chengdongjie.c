// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Fri May 27 19:29:07 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("anding");
set_light(50);
set_brief("%^YELLOW%^"+"城东街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/anding/ad_junying.c",

"south":"/a/anding/ad_minzhai.c",

"east":"/a/anding/ad_dongchengmen.c",

"west":"/a/anding/ad_chengzhongxin.c",
 ]));
}
