// this room is created by buzzer.c
// driver is �������
// created date is Sat Jul 23 22:16:01 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("jiangxia");
set_light(50);
set_brief("%^YELLOW%^"+"������"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/jiangxia/jx_xijie.c",
 ]));
}
