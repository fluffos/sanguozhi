// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun Jul  3 10:31:08 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yiling");
set_light(50);
set_brief("%^YELLOW%^"+"栅栏"+"%^RESET%^");
set_long("");
set_exits( ([
"west":"/a/yiling/yl_laofang.c",

"north":"/a/yiling/yl_caodi.c",

"east":"/a/yiling/yl_xiaolu.c",

"south":"/a/yiling/yl_caochang.c",
 ]));
}
