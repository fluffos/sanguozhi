// Updated by tset on 17 Sep 1998
// Updated by stefan on 10 Jan 1997
/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** objfind.c
**
** Find the locations (environments) of instances of the given class
**
** 07-Nov-94. Created. Deathblade.
*/

#include <mudlib.h>

inherit CMD;

mapping envs;

private void main(string arg)
{
    object * obs;

    if( !arg )
    {
        write( "�÷���Idfind <id>\n");
        return;
    }
    obs = objects( (: $1->id($(arg)) :));

    envs = ([ ]);
    map_array(obs, (: envs[$1] = environment($1) :));

    out(sprintf("%O\n", envs));
}
