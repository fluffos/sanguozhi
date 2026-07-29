// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun May  8 21:14:51 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("tianshui");
set_light(50);
set_brief("%^YELLOW%^"+"北大街"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/tianshui/ts_guanzhai.c",

"north":"/a/tianshui/ts_beichengmen.c",

"south":"/a/tianshui/ts_chengzhongxin.c",

"west":"/a/tianshui/ts_junying.c",
 ]));
}
