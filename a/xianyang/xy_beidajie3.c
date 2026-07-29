// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Sat May 28 12:08:46 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xianyang");
set_light(50);
set_brief("%^YELLOW%^"+"北大街"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/xianyang/xy_yishiting.c",

"west":"/a/xianyang/xy_jiling.c",

"north":"/a/xianyang/xy_guanzhai.c",

"south":"/a/xianyang/xy_beidajie2.c",
 ]));
}
