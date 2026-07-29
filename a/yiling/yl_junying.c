// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun Jul  3 10:28:50 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yiling");
set_light(50);
set_brief("%^YELLOW%^"+"军营"+"%^RESET%^");
set_long("");
set_exits( ([
"east":"/a/yiling/yl_liangcaotunjichu.c",

"south":"/a/yiling/yl_shuaizhang.c",

"west":"/a/yiling/yl_caochang.c",
 ]));
}
