// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Mon May  9 09:18:00 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("jiangling");
set_light(50);
set_brief("%^YELLOW%^"+"瑞平路"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/jiangling/jl_nanchengmen.c",

"west":"/a/jiangling/jl_bingying.c",

"east":"/a/jiangling/jl_xiaochang.c",

"north":"/a/jiangling/jl_ruipinglu1.c",
 ]));
}
