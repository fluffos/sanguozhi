// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Sun May 29 12:17:34 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xuchang");
set_light(50);
set_brief("%^YELLOW%^"+"清虚街北"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/xuchang/xc_xiaoxihu.c",

"north":"/a/xuchang/xc_shusi.c",

"east":"/a/xuchang/xc_machang.c",

"south":"/a/xuchang/xc_qingxujienan.c",

"northeast":"/a/xuchang/xc_bingqipu.c",
 ]));
}
