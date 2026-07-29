// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Fri May 27 19:22:31 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("anding");
set_light(50);
set_brief("%^YELLOW%^"+"城中心"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/anding/ad_chengnanjie1.c",

"north":"/a/anding/ad_xiaochang.c",

"east":"/a/anding/ad_chengdongjie.c",

"west":"/a/anding/ad_chengxijie.c",

"southeast":"/a/anding/tmp.c",
 ]));
}
