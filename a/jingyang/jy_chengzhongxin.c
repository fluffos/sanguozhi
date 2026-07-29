// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Fri May 27 18:44:19 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("jingyang");
set_light(50);
set_brief("%^YELLOW%^"+"城中心"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/jingyang/jy_chengnanjie.c",

"east":"/a/jingyang/jy_chengdongjie.c",

"north":"/a/jingyang/jy_majiu.c",

"west":"/a/jingyang/jy_chengxijie.c",

"southwest":"/a/jingyang/tmp.c",
 ]));
}
