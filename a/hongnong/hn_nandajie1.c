// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Wed Jun 15 20:03:00 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("hongnong");
set_light(50);
set_brief("%^YELLOW%^"+"南大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/hongnong/hn_nandajie2.c",

"west":"/a/hongnong/hn_yamen.c",

"south":"/a/hongnong/hn_chengyipu.c",

"east":"/a/hongnong/tmp.c",
 ]));
}
