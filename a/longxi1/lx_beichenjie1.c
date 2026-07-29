// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sat May  7 14:31:01 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("longxi");
set_light(50);
set_brief("%^YELLOW%^"+"北宸街"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/longxi/lx_jiaoziguan.c",

"north":"/a/longxi/lx_beichenjie2.c",

"south":"/a/longxi/lx_qianmendajie1.c",
 ]));
}
