// Updated by stefan on 10 Jan 1997
/* Do not remove the headers from this file! see /USAGE for more info. */

// Written by Rust.
// I wrote this? I thought Beek did.
// I did.  People should be more careful adding attributions if they aren't
// sure. -Beek

#include <mudlib.h>

inherit OBJ;
inherit M_GETTABLE;

void setup() {
    set_id("camera", "�����", "button");
    set_long("It's a polaroid camera!  There is a button on top.\n");
    set_gettable(1);
}

int press(string s) {
    object picture;

    this_body()->simple_action("$N $vtake a picture with $p $o.\nA polaroid picture slides out the front of $o.\n", this_object());

    picture = new(__DIR__ "picture");
    if (picture->move(this_body()))
        picture->move(environment(this_body()));

    return 1;
}

string get_item_desc(string str) {
    if (str == "button")
	return "Hmm.  A button on a camera.  My, my, whatever might it do?";
}

/*
string direct_press_obj(object ob, string name) {
    printf("%O\n", name);
    if (name == "camera")
	return "Pressing the button is probably a better idea.\n";
}

*/




