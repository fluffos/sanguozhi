// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun May  8 21:14:33 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("tianshui");
set_light(50);
set_brief("%^YELLOW%^"+"南大街"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/tianshui/ts_nandajie1.c",

"west":"/a/tianshui/ts_yamen.c",

"east":"/a/tianshui/ts_qianzhuang.c",

"north":"/a/tianshui/ts_chengzhongxin.c",
 ]));
}
