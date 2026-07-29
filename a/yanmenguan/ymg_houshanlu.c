// this room is created by buzzer.c
// driver is 巴山夜雨
// created date is Wed Jun 15 22:21:52 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yanmenguan");
set_light(50);
set_brief("%^YELLOW%^"+"后山路"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/yanmenguan/ymg_dongguankou.c",

"south":"/a/yanmenguan/ymg_liangcang.c",

"north":"/a/yanmenguan/ymg_shulin.c",

"west":"/a/yanmenguan/ymg_qianshanlu.c",
 ]));
}
