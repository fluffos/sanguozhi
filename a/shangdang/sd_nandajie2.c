// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Wed Jun 15 15:59:06 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("shangdang");
set_light(50);
set_brief("%^YELLOW%^"+"南大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/shangdang/sd_nandajie1.c",

"south":"/a/shangdang/sd_nanchengmen.c",

"west":"/a/shangdang/sd_kezhan.c",

"east":"/a/shangdang/sd_machang.c",
 ]));
}
