// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Wed Jun 15 16:33:28 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("shangdang");
set_light(50);
set_brief("%^YELLOW%^"+"北大街"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/shangdang/sd_junying.c",

"east":"/a/shangdang/sd_liangcang.c",

"north":"/a/shangdang/sd_beichengmen.c",

"south":"/a/shangdang/sd_chengzhongxin.c",
 ]));
}
