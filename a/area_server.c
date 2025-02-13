// this will be used to handle all the area rooms
// by fire on July 17, 1999
#include <security.h>

inherit M_ACCESS;

private mapping rooms=([]);
private string m_area;

mixed get_save_file() {

	//if(!AREA_D->area_exist(m_area)) return 0; //remed by suicide in 2002.3.8
	return "/data/area/"+m_area;
}
void save_data()
{
	string f_name;
	if(!get_save_file()) return; 
	f_name=get_save_file();
       unguarded(1, (: save_object, f_name :));
}
void set_area(string area) {
    string f_name;
    set_privilege(1);
    m_area=area;
    f_name=get_save_file();
    if(f_name)
      unguarded(1, (: restore_object, f_name, 1 :));
    m_area=area;

}
string get_room_type(int r) {
	switch (r) {
		case 1:
			return OUTDOOR_ROOM;
		case 2:
			return M_DANGPU;
		case 3: 
			return M_BANK;
		default : return INDOOR_ROOM;
	}
}
mixed get_room(string r_id,string para) {
	if(r_id=="list") return keys(rooms);
	if(r_id=="all") return rooms;
	if(!rooms[r_id]) return 0;
	if(!para||(para=="")) return rooms[r_id];
	switch (para) {
	case "t": // room type
		return get_room_type(rooms[r_id]["t"]);
	default : return rooms[r_id][para];
	}
}
mixed add_room(string r_id) {
	if(mapp(rooms[r_id])) return "room alread exit";
	rooms[r_id]=([]);
	save_data();
}
//added by suicide for delete room
mixed del_room(string r_id) 
{
if(!mapp(rooms[r_id])) return "room not exist";
map_delete(rooms,r_id);
save_data();
}
//added end
//modified by suicide for copy room
mixed set_room(string r_id,string para,mixed val) {
	if(!mapp(rooms[r_id])) return "no such room";
	if(!para||(para=="")) rooms[r_id]=val; //to copy full room mapping data .suicide
	else rooms[r_id][para]=val;
	if(val==0)
		map_delete(rooms[r_id],para);
	save_data();
	return rooms[r_id];
}
//modified end
object virtual_create(string arg)
{
	object room,o;
	string room_file;
	string r_id;
	string *chars;
	mixed exit;
	if(!mapp(rooms[arg])) return 0;
	    	
	room_file=get_room(arg,"t");
	room = new(room_file);
	if(!objectp(room)) return 0;
	room->set_brief(rooms[arg]["b"]);
	room->set_long(rooms[arg]["l"]);
	room->set_area(m_area);
	if(sizeof(rooms[arg]["e"])) {
		exit=keys(rooms[arg]["e"]);
		foreach(string e in exit) {
			if(rooms[arg]["e"][e][0]=='/') 
				room->add_exit(e,rooms[arg]["e"][e]);
			else
				room->add_exit(e,"/a/"+m_area+"/"+rooms[arg]["e"][e]);
		}
	}
	if(arg==AREA_D->get_area(m_area,"meeting")) {
		string nat=AREA_D->get_area(m_area,"nation");
	        if(COUNTRY_D->nation_exist(nat))
	        {
			if(!rooms[arg]["o"]) rooms[arg]["o"]=([]);
			rooms[arg]["o"][M_BOARD]=({1, COUNTRY_D->get_country(nat,"name")+
				"通告","nation."+nat});
		}
	}
	room->set_objects(rooms[arg]["o"]);
	r_id="/a/"+m_area+"/"+arg;
	chars=CHAR_D->check_char("room",r_id);
//	tell_user("fire",sprintf("rid is %s %O\n",r_id,chars));
	if(sizeof(chars)) {
		foreach(string c in chars) {
			o=find_body(c);
			if(!objectp(o)) {
				o=CHAR_D->creat_npc_char(c);
			}
			if(objectp(o)) o->move(room);		
		}
	}
    return room;
}
// Disappear if no longer needed
static void clean_up() {
	return 0; // don't want it is destroyed
}

mixed tran_room() {
	string p_path;
	string *files,*exs,ex;
	object o_room;
	int p_len;
	p_path=AREA_D->get_area(m_area,"path");	
	p_len=sizeof(p_path)-1;
	files = (get_dir(p_path+"*.c"));
	rooms=([]);
	foreach(string f in files) {
		o_room=load_object(p_path+f);
		if(!objectp(o_room)) continue;
		if(f[<2..<1]==".c") f=f[0..<3];
		if(f=="warroom") continue;
		rooms[f]=([]);
		rooms[f]["b"]=o_room->short();
		rooms[f]["l"]=o_room->get_base_long();
		rooms[f]["o"]=o_room->query_objects();
		exs=o_room->query_exit_directions(0);
		rooms[f]["e"]=([]);
		if(sizeof(exs)) {
			foreach(string e in exs) {
				ex=o_room->query_exit_value(e);
				
				if(ex[<2..<1]==".c") ex=ex[0..<3];
				if(ex[0..p_len]==p_path) 
					rooms[f]["e"][e]=ex[sizeof(p_path)..<1];
				else
					rooms[f]["e"][e]=ex;
			}
		}
		if(o_room->is_outdoors())
			rooms[f]["t"]=1; // out door
		if(o_room->is_dangpu())
			rooms[f]["t"]=2; // dangpu
		if(o_room->is_bank())
			rooms[f]["t"]=3; // dangpu
		rooms[f]["o"]=o_room->query_objects();

	}
	save_data();
	return files;
}
mixed trans() {
	string *list;
	string pp;
	int level;
	level=AREA_D->get_area(m_area,"level");
	switch(level) {
		case 1:
		case 2:
			pp="/sgdomain/area/guan/"+m_area+"/";
			break;
		case 3:
			pp="/sgdomain/area/town/"+m_area+"/";
			break;
		default:
			pp="/sgdomain/area/cities/"+m_area+"/";
			break;
	}
	AREA_D->set_area(m_area,"path",pp);
	tran_room();
	AREA_D->set_area(m_area,"path","/a/"+m_area+"/");
	list=CHAR_D->check_char("area",m_area);
	if(sizeof(list)) {
		foreach(string s in list) 
			CHAR_D->remove_npc_char(s);
	}
	return 1;
}

mixed sethere(string s,mixed val) {
	string area,room,f_name, *tmp;
	f_name=file_name(this_body()->query_room());
	if(f_name[0..2]!="/a/") return "这里不是三国常规地区。\n";
	tmp=explode(f_name,"/");
	area=tmp[1];
	room=tmp[2];
	return AREA(area)->set_room(room,s,val);
}
mixed gethere(string s) {
	string area,room,f_name, *tmp;
	f_name=file_name(this_body()->query_room());
	if(f_name[0..2]!="/a/") return "这里不是三国常规地区。\n";
	tmp=explode(f_name,"/");
	area=tmp[1];
	room=tmp[2];
	if(!sizeof(s)) s="";
	return AREA(area)->get_room(room,s);

}

//added by suicide in 20001.03.16 for enter random place by guard
string get_random_room()
{array r_ids;
 r_ids = keys(rooms);
 return r_ids[random(sizeof(rooms))];
}

string get_area()
{
return m_area;
}
