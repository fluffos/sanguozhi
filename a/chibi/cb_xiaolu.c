// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Mon Jul 25 23:30:55 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("chibi");
set_light(50);
set_brief("%^YELLOW%^"+"小路"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/chibi/cb_bingying.c",

"east":"/a/chibi/cb_jiaochang.c",

"south":"/a/chibi/cb_zhalan.c",

"west":"/a/chibi/cb_xiaodao.c",
 ]));
}
