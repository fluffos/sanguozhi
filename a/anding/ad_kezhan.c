// this room is created by buzzer.c
// driver is ��ɽҹ��
// created date is Fri May 27 19:50:51 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("anding");
set_light(50);
set_brief("%^YELLOW%^"+"��ջ"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/anding/ad_chengnanjie2.c",
 ]));
}
