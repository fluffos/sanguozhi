// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Apr 29 12:48:46 2011
#include <mudlib.h>
#include <ansi.h>
inherit INDOOR_ROOM;
void setup() {
set_area("huayin");
set_light(50);
set_brief("%^YELLOW%^"+"前庭"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/huayin/houtang.c",

"south":"/a/huayin/chufang.c",

"north":"/a/huayin/zhangfang.c",

"west":"/a/huayin/qianyuan.c",
 ]));
}
