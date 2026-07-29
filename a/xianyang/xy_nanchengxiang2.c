// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sat May 28 13:38:04 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xianyang");
set_light(50);
set_brief("%^YELLOW%^"+"南城巷"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/xianyang/xy_caiyuan.c",

"north":"/a/xianyang/xy_fenci.c",

"east":"/a/xianyang/xy_nanchengxiang.c",
 ]));
}
