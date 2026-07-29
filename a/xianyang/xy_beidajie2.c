// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Sat May 28 12:00:16 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xianyang");
set_light(50);
set_brief("%^YELLOW%^"+"北大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/xianyang/xy_beidajie3.c",

"east":"/a/xianyang/xy_junying.c",

"west":"/a/xianyang/xy_yisuo.c",

"south":"/a/xianyang/xy_beidajie1.c",
 ]));
}
