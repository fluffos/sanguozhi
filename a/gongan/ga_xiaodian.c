// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Sun Jul 17 23:17:00 2011
//#include <mudlib.h>
//#include <ansi.h>
inherit INDOOR_ROOM;
inherit STORE;
void setup() {
set_area("gongan");
set_light(50);
set_brief("%^YELLOW%^"+"小店"+"%^RESET%^");
set_long("");
set_exits( ([
"north":"/a/gongan/ga_tulu.c",
 ]));
add_object("/sgdomain/obj/foodanddrink/mantou.c");
add_object("/sgdomain/obj/foodanddrink/ypjd.c");
set_objects( (["/sgdomain/obj/other/well.c" : 1]) );
}
