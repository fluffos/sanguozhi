// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sat May  7 13:54:45 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("longxi");
set_light(50);
set_brief("%^YELLOW%^"+"前门大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/longxi/lx_yamen.c",

"west":"/a/longxi/lx_qianmendajie5.c",

"south":"/a/longxi/lx_liangcang.c",

"east":"/a/longxi/lx_qianmendajie3.c",
 ]));
}
