// this room is created by buzzer.c
// driver is �������
// created date is Fri May  6 15:21:27 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit INDOOR_ROOM;
void setup() {
set_area("wuzhangyuan");
set_light(50);
set_brief("%^YELLOW%^"+"դ��"+"%^RESET%^");
set_long("");
set_exits( ([
"south":"/a/wuzhangyuan/wzy_zhalanrukou.c",
 ]));
}
