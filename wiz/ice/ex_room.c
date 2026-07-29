/* ex_room
** Coded by 玄冰@三国志总站
** Code generated with RoomMaker v0.9.1 coded by Onyx@RedDragon
** Do not remove this header.
*/
#include <ansi.h>


inherit ROOM;

void setup(){
    set_light(50);
        set_brief(""+YEL+"展览厅"+NOR+"");
    set_long(
"\n    这里是家具展览厅，到处摆的都是家具。\n\n",
);
    set_exits( ([
"up" :  "/wiz/ice/idleroom",
"hell":"/wiz/ice/gate",
    ]) );
    set_objects( ([
"/wiz/ice/obj/furniture/hmbed.c":1,
"/wiz/ice/obj/furniture/szbed.c":1,
"/wiz/ice/obj/furniture/xmkbed.c":1,
"/wiz/ice/obj/furniture/xmbed.c":1,
"/wiz/ice/obj/furniture/ztbed.c":1,
"/wiz/ice/obj/furniture/bed.c":1,
"/wiz/ice/obj/furniture/sofa.c":1,
    ]) );
}
