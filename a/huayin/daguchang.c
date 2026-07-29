// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Fri Apr 29 10:57:19 2011
#include <mudlib.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("huayin");
set_light(50);
set_brief("%^YELLOW%^"+"打谷场"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/huayin/zhulin.c",

"south":"/a/huayin/qianzhuang.c",

"north":"/a/huayin/dangpu.c",

"west":"/a/huayin/lukou.c",
 ]));
}
