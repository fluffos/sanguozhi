// Updated by stefan on 10 Jan 1997
/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** verb_ob.c
**
** This is a standard verb handler.  It handles adding and removing
** verb rules (to/from the parser efuns).
*/

#include <mudlib.h>

/*
** query_verb_info()
**
** This is the heart of this object.  Subclasses should override and
** return an array with 1 or 2 elements.  The first element should
** be an array of rules.  If the second is provided, then it should
** be an array of synonyms.
**
** Extension: You can have more than one set of rules/synonyms.
** Synonyms only correspond to the corresponding rule.  E.g.
** ({ ({ first rules }), ({ syns for first rules }), ({ second rules }),
**    ... etc ... })
*/
array query_verb_info()
{
    return ({ ({ }) });
}

void create()
{
    mixed *     info;
    string      verb;
    
    parse_init();
    verb = split_path(file_name())[1];
    info = query_verb_info();

    // backwards compat
    info[0] = map(info[0], (: (stringp($1) ? $1 : ($1 ? "STR" : "") ) :));
    
    if ( !info || !pointerp(info) || !pointerp(info[0]) )
        throw("bad verb info");

    switch (sizeof(info)) {
    case 0:
        break;
    case 1:
        foreach (string rule in info[0])
            parse_add_rule(verb, rule);
        break;
    case 2:
        foreach (string rule in info[0])
            parse_add_rule(verb, rule);
        foreach (string syn in info[1])
            parse_add_synonym(syn, verb);
        break;
    default:
        for (int i = 0; i < sizeof(info); i += 2) {
            if (i == sizeof(info) - 1)
                foreach (string rule in info[i])
                    parse_add_rule(verb, rule);
            else
                foreach (string rule in info[i]) {
                    parse_add_rule(verb, rule);
                    foreach (string syn in info[i+1])
                        parse_add_synonym(syn, verb, rule);
                }
        }
    }
}

string refer_to_object(object ob) {
    // In the future, this should be smarter.  Ideally it would generate
    // something unique like 'my first sword' or 'the third sword on the table'
    return ob->query_primary_name();
}
 
mixed try_to_acquire(object ob) {
    /* for things that can be used in certain conditions without
     * actually being in the player's inventory
     */
    if (ob->always_usable()) return 1;

    if (environment(ob) == this_body()) return 1;
    //write("(Taking " + ob->short());
    if (!environment(ob)) {
        write("好象是自己眼花了...\n");
        return 0;
    }
    write("(你先");
    if (environment(ob) != environment(this_body()))
        write("从" + environment(ob)->short()+"拿出"
              +ob->short()+")\n");
    else write("拾起"+ob->short()+")\n");
    this_body()->do_game_command("get " + refer_to_object(ob));
    return environment(ob) == this_body();
}     

mixed check_ghost() {
    if (this_body()->query_ghost())
        return "可是你只是一个鬼魂！\n";//"But you're a ghost!\n";
    return 1;
}

mixed check_vision() {
    if (environment(this_body())->query_light())
        return 1;
    return "你什么都看不清楚。。。\n";//"You can't see a thing!\n";
}

mixed check_condition() {
    mixed tmp;
    
    if (tmp = this_body()->check_condition(0))
        return tmp;
    return 1;
}

int need_to_see() {
    return 1;
}

int need_to_be_alive() {
    return 1;
}

int need_to_think() {
    return 1;
}

/* All (most) can_* functions should call this */
mixed default_checks() {
    mixed tmp;

    if (need_to_see() && (tmp = check_vision()) != 1)
        return tmp;
 
    if (need_to_be_alive() && (tmp = check_ghost()) != 1)
        return tmp;
    // This checks stunned, asleep
 
    if (need_to_think())
        return check_condition();

    return 1;
}

void handle_obs(array info, function callback, mixed extra...) {
    foreach (mixed ob in info) {
        if (stringp(ob))
            write(ob);
        else {
            write(ob->short() + ": ");
            evaluate(callback, ob, extra...);
        }
    }
}

/* we defined the rule, so assume by default we allow it */
mixed can_verb_rule(string verb, string rule) {
    return default_checks();
}
