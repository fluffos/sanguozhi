// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Tue May  3 21:17:39 2011
#include <mudlib.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("changan");
set_light(50);
set_brief("%^YELLOW%^"+"东大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/changan/ca_zhubaodian.c",

"east":"/a/changan/ca_dongdajie2.c",

"west":"/a/changan/ca_czx.c",

"northwest":"/a/changan/ca_yizhan.c",
 ]));
}
