//  城中心 by benben
// xy_center.c 
#include <mudlib.h>
#include "/wiz/fire/fire.h"
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup(){
    set_area("xianyang");
    set_light(50);
    set_brief(""+YEL+"城中心"+NOR+"");
    set_long("    描述。\n");
    set_exits( ([
        "east" :  __DIR__+"xy_est1.c",
        "west" :  __DIR__+"xy_wst1.c",
        "south" : __DIR__+"xy_sst1.c",
        "north" : __DIR__+"xy_nst1.c"
    ]) );
}
