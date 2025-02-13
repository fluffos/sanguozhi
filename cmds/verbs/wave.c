// Updated by stefan on 10 Jan 1997
/* Do not remove the headers from this file! see /USAGE for more info. */

#include <mudlib.h>
#include <setbit.h>

inherit VERB_OB;
inherit M_PARSING;

// Anything can be waved at/be waved.  Might not do anything, tho :)
mixed direct_wave_obj(object ob) {
    return 1;
}

mixed direct_wave_obj_at_obj(object ob1, object ob2) {
    return 1;
}

mixed indirect_wave_obj_at_obj(object ob1, object ob2) {
    return 1;
}

mixed do_wave_it(object ob, object with)
{
//suspended by row    if (!try_to_acquire(ob))
//        return;
    
    if (!ob->wave(with)) {
        write(useless("�Ӷ�"+ob->short()));
    }
}

void do_wave_obj(object ob) {
    do_wave_it(ob, 0);
}

void do_wave_obj_at_obj(object ob1, object ob2) {
    do_wave_it(ob1, ob2);
}

array query_verb_info()
{
    return ({ ({ "OBJ", "OBJ at OBJ:v" }) });
}
