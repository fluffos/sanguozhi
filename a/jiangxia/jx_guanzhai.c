// this room is created by buzzer.c
// driver is �������
// created date is Sat Jul 23 22:07:43 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit INDOOR_ROOM;
void setup() {
set_area("jiangxia");
set_light(50);
set_brief("%^YELLOW%^"+"��լ"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/jiangxia/jx_huating.c",

"east":"/a/jiangxia/jx_xiaochang.c",
 ]));
}
