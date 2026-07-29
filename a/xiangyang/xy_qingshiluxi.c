// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Jul 29 11:07:28 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xiangyang");
set_light(50);
set_brief("%^YELLOW%^"+"青石路西"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/xiangyang/xy_xichengmen.c",

"south":"/a/xiangyang/xy_qingzhuxiaojing.c",

"north":"/a/xiangyang/xy_huadian.c",

"east":"/a/xiangyang/xy_chengzhongxin.c",
 ]));
}
