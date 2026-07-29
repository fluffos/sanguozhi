// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sat Jul 23 22:09:43 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("jiangxia");
set_light(50);
set_brief("%^YELLOW%^"+"碎石小路"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/jiangxia/jx_nanjie.c",

"west":"/a/jiangxia/jx_guangchang.c",

"east":"/a/jiangxia/jx_zahuopu.c",

"north":"/a/jiangxia/jx_xiaochang.c",

"southeast":"/a/jiangxia/jx_xingyunshi.c",
 ]));
}
