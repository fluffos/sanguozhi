// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Jul 29 10:52:12 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xiangyang");
set_light(50);
set_brief("%^YELLOW%^"+"青石路东"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/xiangyang/xy_dongchengmen.c",

"south":"/a/xiangyang/xy_bingqipu.c",

"north":"/a/xiangyang/xy_yushi.c",

"west":"/a/xiangyang/xy_chengzhongxin.c",
 ]));
}
