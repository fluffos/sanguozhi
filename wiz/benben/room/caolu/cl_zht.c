//  中堂
// cl_zht.c by benben
#include <mudlib.h>
#include <sanguo.h>
#include <ansi.h>
inherit OUTDOOR_ROOM;
void setup(){
    set_area("caolu_area");
    set_light(50);
    set_brief(""+YEL+"中堂"+NOR+"");
    set_long("    这儿是诸葛草庐的中堂。\n");
    set_exits( ([
        "east" :  __DIR__+"cl_wsh.c",
        "west" :  __DIR__+"cl_shuf.c",
        "south" : __DIR__+"cl_qt.c",
        "north" : __DIR__+"cl_ht.c"
    ]) );
}
