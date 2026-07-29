// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Thu May 26 20:46:52 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("taiyuan");
set_light(50);
set_brief("%^YELLOW%^"+"南大街"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/taiyuan/ty_nanchengmen.c",

"west":"/a/taiyuan/ty_bingying.c",

"east":"/a/taiyuan/ty_tiejiangpu.c",

"north":"/a/taiyuan/ty_nandajie1.c",
 ]));
}
