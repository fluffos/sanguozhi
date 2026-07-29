// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Tue May  3 19:53:03 2011
#include <mudlib.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("changan");
set_light(50);
set_brief("%^YELLOW%^"+"马场"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/changan/ca_beidajie1.c",

"north":"/a/changan/ca_yingfang.c",

"west":"/a/changan/ca_xintian.c",

"south":"/a/changan/ca_yongchangjie3.c",
 ]));
set_objects( (["/wiz/ljty/npc/mafu.c" : 1 ]) );
}
