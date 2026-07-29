// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Thu May 26 20:54:24 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("taiyuan");
set_light(50);
set_brief("%^YELLOW%^"+"北大街"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/taiyuan/ty_beidajie3.c",

"east":"/a/taiyuan/ty_shuyuan.c",

"west":"/a/taiyuan/ty_taixuetang.c",

"south":"/a/taiyuan/ty_beidajie1.c",
 ]));
}
