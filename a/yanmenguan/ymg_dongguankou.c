// this room is created by buzzer.c
// driver is ��ɽҹ��
// created date is Wed Jun 15 22:24:50 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yanmenguan");
set_light(50);
set_brief("%^YELLOW%^"+"���ؿ�"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/yanmenguan/ymg_guanqianxiaodao.c",

"west":"/a/yanmenguan/ymg_houshanlu.c",
 ]));
}
