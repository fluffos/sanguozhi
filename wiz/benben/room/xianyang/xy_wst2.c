//  ����� by benben
// xy_wst2.c 
#include <mudlib.h>
#include "/wiz/fire/fire.h"
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup(){
    set_area("xianyang");
    set_light(50);
    set_brief(""+YEL+"�����"+NOR+"");
    set_long("    ������\n");
    set_exits( ([
        "east" :  __DIR__+"xy_wst1.c",
        "west" :  __DIR__+"xy_wgate.c",
        "south" : __DIR__+"xy_tmy.c",
    ]) );
}
