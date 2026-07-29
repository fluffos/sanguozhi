// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Sat May 28 19:21:12 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("wuling");
set_light(50);
set_brief("%^YELLOW%^"+"大道"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/wuling/wl_dadao2.c",

"north":"/a/wuling/wl_yamen.c",

"west":"/a/wuling/wl_ximen.c",

"south":"/a/wuling/tmp.c",
 ]));
set_objects(([M_BOARD : ({ 1,"路边挂着一张皇榜 "+"%^MAGENTA%^"+"武陵留言榜"+"%^RESET%^", "city.wuling" }) ]) );
}
