// this room is created by buzzer.c
// driver is ��ɽҹ��
// created date is Sun Jun 12 20:16:26 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("bailangshan");
set_light(50);
set_brief("%^YELLOW%^"+"ɽ·"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/bailangshan/bls_xuanya.c",

"south":"/a/bailangshan/bls_xiaochang.c",
 ]));
}
