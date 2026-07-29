// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Jun  3 21:55:25 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yunnan");
set_light(50);
set_brief("%^YELLOW%^"+"石板路2"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/yunnan/yn_chengzhongxin.c",

"west":"/a/yunnan/yn_roupu.c",

"east":"/a/yunnan/yn_kedian.c",

"south":"/a/yunnan/yn_shibanlu1.c",
 ]));
}
