//  北大街 by benben
// xy_nst3.c 
#include <mudlib.h>
#include "/wiz/fire/fire.h"
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup(){
    set_area("xianyang");
    set_light(50);
    set_brief(""+YEL+"北大街"+NOR+"");
    set_long("    描述。\n");
    set_exits( ([
        "east" :  __DIR__+"xy_ysht.c",
        "west" :  __DIR__+"xy_jl.c",
        "south" : __DIR__+"xy_nst2.c",
        "north" : __DIR__+"xy_guanzhai.c"
    ]) );
}
