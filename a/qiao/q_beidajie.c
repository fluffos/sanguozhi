// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun May 29 20:49:32 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("qiao");
set_light(50);
set_brief("%^YELLOW%^"+"北大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/qiao/q_beichengmen.c",

"east":"/a/qiao/q_wanfujiulou.c",

"west":"/a/qiao/q_guanzhai.c",

"south":"/a/qiao/q_xiaochang.c",
 ]));
}
