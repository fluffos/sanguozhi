// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Jul 29 10:38:40 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xiangyang");
set_light(50);
set_brief("%^YELLOW%^"+"天池街"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/xiangyang/xy_datiepu.c",

"west":"/a/xiangyang/xy_buzhuang.c",

"south":"/a/xiangyang/xy_tianchijie3.c",
 ]));
}
