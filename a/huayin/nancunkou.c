// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Apr 29 12:57:18 2011
#include <mudlib.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("huayin");
set_light(50);
set_brief("%^YELLOW%^"+"南村口"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/huayin/muqiao.c",

"east":"/a/huayin/tmp.c",

"west":"/a/huayin/kedian.c",

"north":"/a/huayin/xiaoxiang.c",
 ]));
}
