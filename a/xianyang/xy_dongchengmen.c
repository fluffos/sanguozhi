// this room is created by buzzer.c
// driver is ��ɽҹ��
// created date is Sat May 28 11:24:24 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("xianyang");
set_light(50);
set_brief("%^YELLOW%^"+"������"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/xianyang/xy_dongdajie2.c",
 ]));
}
