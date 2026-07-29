// this room is created by buzzer.c
// driver is 花儿朵朵
// created date is Tue May  3 21:16:35 2011
#include <mudlib.h>
#include <ansi.h>
inherit INDOOR_ROOM;
inherit STORE;

void setup() {
set_area("changan");
set_light(50);
set_brief("%^YELLOW%^"+"兵器铺"+"%^RESET%^");
set_long("
    你走进兵器铺，不由得眼前一亮，宽敞的屋子里陈列着各式
各样的精致的兵器，木架上竖立着长柄大刀，花枪，长剑等。每
一件都让你爱不释手。用list指令列出兵器和价格，用buy指令
购买。\n\n");
set_exits( ([
"east":"/a/changan/ca_xiaolu.c",
 ]));
add_object("/sgdomain/obj/weapon/blade/qixing.c");
add_object("/sgdomain/obj/weapon/blade/sanjian.c");
add_object("/sgdomain/obj/weapon/hammer/tiechui.c");
add_object("/sgdomain/obj/weapon/ji/changji.c");
add_object("/sgdomain/obj/weapon/ji/ji.c");
add_object("/sgdomain/obj/weapon/sword/gangjian.c");
}
