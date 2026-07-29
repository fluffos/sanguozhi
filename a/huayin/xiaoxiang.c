// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Apr 29 12:11:42 2011
#include <mudlib.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("huayin");
set_light(50);
set_brief("%^YELLOW%^"+"小巷"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/huayin/nancunkou.c",

"east":"/a/huayin/qianyuan.c",

"west":"/a/huayin/sishu.c",

"north":"/a/huayin/cunzhongxin.c",
 ]));
}
