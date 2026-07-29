// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun Jul  3 10:32:02 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup() {
set_area("yiling");
set_light(50);
set_brief("%^YELLOW%^"+"草地"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/yiling/yl_shanlu.c",

"east":"/a/yiling/yl_shandi.c",

"south":"/a/yiling/yl_zhalan.c",
 ]));
}
