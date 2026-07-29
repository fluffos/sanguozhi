// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri May  6 15:20:25 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("wuzhangyuan");
set_light(50);
set_brief("%^YELLOW%^"+"栅栏入口"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/wuzhangyuan/wzy_xiaolu2.c",

"south":"/a/wuzhangyuan/wzy_zhalan2.c",

"north":"/a/wuzhangyuan/wzy_zhalan1.c",

"west":"/a/wuzhangyuan/wzy_dalu1.c",
 ]));
}
