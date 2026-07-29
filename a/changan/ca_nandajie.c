// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Tue May  3 21:26:35 2011
#include <mudlib.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("changan");
set_light(50);
set_brief("%^YELLOW%^"+"南大街"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/changan/ca_nanchengmen.c",

"east":"/a/changan/ca_sihaijiulou.c",

"west":"/a/changan/ca_yaopu.c",

"north":"/a/changan/ca_czx.c",
 ]));
}
