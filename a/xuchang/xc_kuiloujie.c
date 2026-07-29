// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Sun May 29 11:52:40 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xuchang");
set_light(50);
set_brief("%^YELLOW%^"+"奎楼街"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/xuchang/xc_chunqiulou.c",

"east":"/a/xuchang/xc_qianzhuang.c",

"west":"/a/xuchang/xc_dangpu.c",

"north":"/a/xuchang/xc_dongjieyi.c",
 ]));
}
