// this room is created by buzzer.c
// driver is �������
// created date is Sat May 28 13:38:44 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit INDOOR_ROOM;
void setup() {
set_area("xianyang");
set_light(50);
set_brief("%^YELLOW%^"+"���"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/xianyang/xy_nanchengxiang2.c",
 ]));
}
