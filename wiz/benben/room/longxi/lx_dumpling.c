//  ���ӹ� by benben
// lx_dumpling.c 
#include <mudlib.h>
#include "/wiz/fire/fire.h"
#include <ansi.h>
inherit ROOM;
void setup(){
    set_area("longxi");
    set_light(50);
    set_brief(""+YEL+"--���ӹ�--"+NOR+"");
    set_long("    ������\n");
    set_exits( ([
        "west" :  __DIR__+"lx_bhst1.c",
    ]) );
}
