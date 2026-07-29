// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Sat May 28 11:17:36 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xianyang");
set_light(50);
set_brief("%^YELLOW%^"+"东大街"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/xianyang/xy_dongdajie1.c",

"north":"/a/xianyang/xy_chunhualou.c",

"east":"/a/xianyang/xy_dongchengmen.c",

"south":"/a/xianyang/tmp.c",
 ]));
}
