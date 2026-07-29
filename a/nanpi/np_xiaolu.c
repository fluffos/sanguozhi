// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Mon May 30 19:30:05 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("nanpi");
set_light(50);
set_brief("%^YELLOW%^"+"小路"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/nanpi/np_hualang.c",

"south":"/a/nanpi/np_xidajie.c",

"west":"/a/nanpi/np_xiaokezhan.c",

"north":"/a/nanpi/np_xinyueqiao.c",
 ]));
}
