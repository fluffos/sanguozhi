//  斗南街 by benben
// lx_dnst2.c 
#include <mudlib.h>
#include "/wiz/fire/fire.h"
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup(){
    set_area("longxi");
    set_light(50);
    set_brief(""+YEL+"--斗南街--"+NOR+"");
    set_long("    描述。\n");
    set_exits( ([
        "east" :  __DIR__+"lx_bdch.c",
        "west" :  __DIR__+"lx_dxp.c",
        "south" : __DIR__+"lx_dnst3.c",
        "north" : __DIR__+"lx_dnst1.c",
    ]) );
}
