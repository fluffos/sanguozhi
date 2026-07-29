//  小店
// vstore.c write by fire on 12.19.1997
#include <mudlib.h>
#include <sanguo.h>
#include <ansi.h>

inherit ROOM;
inherit STORE;

void setup(){
    set_area("xbv_area");
    set_light(50);
    set_brief(""+YEL+"--乡村小店--"+NOR+"");
    set_long(
"    你走进村中唯一的一个小店，因为村中人少，这里的生意也不太
好。店小二正懒洋洋地坐在一旁打瞌睡。房间的一角有个大水缸。看
来可以灌水。\n\n"
);
    set_exits( ([
        "east" :  __DIR__+"vcenter.c"
    ]) );
  add_object( FOBJPATH+"candy.c");
  add_object( FOBJPATH+"yangpi_jiudai.c");
  add_object( FOBJPATH+"huoba.c");
  add_object( FOBJPATH+"dart.c");
  set_objects( ([
                        FNPCPATH+"xiaoer" : 1,
  ]) );
}
