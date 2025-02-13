// troop_d.c
// this is used to handle the troops
// because the troop are so complex therefore need a file to contorl them
// by fire on September 17, 1998
#define STAGE_NEW 0
#include <mudlib.h>
#include <security.h>
inherit M_ACCESS;
inherit __DIR__+"troop_d/troop_attack";
inherit __DIR__+"troop_d/consume";
inherit __DIR__+"troop_d/array";
inherit __DIR__+"troop_d/horse";
inherit __DIR__+"troop_d/number";
private mapping troops=([]);
private int p_maxid=1;
static int save_mark;
static int round;
#define SAVE_FILE "/data/daemons/troops"
#define TROOP_TYPE(x) "/sgdomain/troops/"+x+".c"

mixed find_troop(int p_id);
int put_troop(int p_id,string r_id);
int illegal_troop(int t_id);
// Add new function recover energy instead of WARAI_D
void recover_energy(int p_id);
void recover_troop(int p_id);
void add_morale(mixed p_id, int va);
string get_troop_side(int p_id);

void save_data()
{
        save_mark++;
        if((save_mark<0)||(save_mark>20))
        {
                save_mark=0;
                unguarded(1, (: save_object, SAVE_FILE :));
        }
}
void troop_heart()
{
	int* keys;

	string* sol; // soldiers
	remove_call_out("troop_heart");
        call_out("troop_heart",3);
        round++;
        if(round>=5) round=0;
        keys=keys(troops);
        keys=filter_array(keys,(:($1)%5==round:));
	foreach(int p_id in keys)
	{
		object ob;
		int is_auto=1;
		if(illegal_troop(p_id))
		{	
			TROOP_D->remove_troop(p_id);
			continue;
		}
		ob=find_troop(p_id);
		foreach(string p_char in troops[p_id]["chars"])
		{	object o_char;
			o_char=CHAR_D->find_char(p_char);
			if(!objectp(o_char)||(o_char->query_room()!=ob)) 
				CHAR_D->put_char(p_char,file_name(ob));
			if(objectp(find_body(p_char)))
				is_auto=0;
		}
		recover_energy(p_id);
		//if((troops[p_id]["side"]=="a")&&(random(2)==0))
		//	add_morale(p_id,-1); // this work moved into the recover_energy
		if(is_auto)
		  {int task_id=troops[p_id]["task_id"];
		   if (!task_id) return;
		   WARAI_D->auto_action(p_id);
		   if (TASK_D->get_task(task_id,"type") == TT_WAR )
		       if (troops[p_id]["side"] == "d")
		           WARAI_D->auto_jimou(p_id);
		  }
	}
    save_data();
}
int new_troop_id(string nation,string *chars,mapping soldier)
{
        int *list;
        int *sers;
        int p_id=1;
        int p_ser=1;
        int i;
        if(!troops)
                troops=([]);
        list=keys(troops);
		p_maxid++;
		if(p_maxid>1000) p_maxid=1;
        while(member_array(p_maxid,list)!=-1)
                p_maxid++;
		p_id=p_maxid;
        list=filter_array(list,(:troops[($1)]["nation"]==$(nation) :));
        sers=({});
        for(i=0;i<sizeof(list);++i)
                sers+=({ troops[list[i]]["ser"] });
        while(member_array(p_ser,sers)!=-1)
                p_ser++;
        troops[p_id]=([]);
        troops[p_id]["nation"]=nation;
        troops[p_id]["ser"]=p_ser;
        troops[p_id]["chars"]=chars;
		troops[p_id]["stamp"]=time()%1000*1000+random(1000); // special id to identify the troop

	if(!mapp(soldier))
		soldier=([]);
	troops[p_id]["soldier"]=soldier;
	return p_id;
}
mixed get_troop_position(int p_id)
{
	string p_room;
	string *p_part;
	int s;
        p_room=troops[p_id]["room"];
	p_part=explode(p_room,"/");
	s=sizeof(p_part);
	return ({to_int(p_part[s-2]),to_int(p_part[s-1])});
}
string get_troop_name(int p_id)
{
	string p_nation,p_nationname;
	string p_ret;	
	p_nation=troops[p_id]["nation"];
	p_nationname=COUNTRY_D->get_country(p_nation,"name");
	if(!p_nationname)
		p_nationname=p_nation;
	p_ret=p_nationname+"第"+
CHINESE_D->chinese_number(troops[p_id]["ser"])+"军团";
	return p_ret;
}
int get_troop_canbeseen(int t_id)
{
	string p_side;
	int x,y;
	int *pos;
        string *trs;
	string p_m;
	string p_area;
	

	p_area=troops[t_id]["area"];
	p_side=troops[t_id]["side"];
	pos=TROOP_D->get_troops(t_id,"position");
	for(x=pos[0]-3;x<=pos[0]+3;++x)
        for(y=pos[1]-3;y<=pos[1]+3;++y)
	{
		trs=MAP_D->get_map_cell(p_area,y,x,"t");
                if(sizeof(trs))
		{	if(troops[trs[0]]["side"]!=p_side &&
				!TROOP_D->get_troops(t_id,"qibing") && 
				!TROOP_D->get_troops(t_id,"maifu"))
				return 1;
                        if(TROOP_D->get_troops(t_id,"appear"))
                                return 1;
		}
		if(p_side=="a")
		{
			p_m=MAP_D->get_map_cell(p_area,y,x,"m");
			if(MAP_D->is_wall(p_m))
				return 1;
		}
	}
	return 0;
}

int get_soldier_total_number(int p_id)
{
	mixed s;
	int ret=0;
        string *k;
//        if (p_id < 0 || p_id >= sizeof(troops)) return 0;
        if(!troops[p_id]) return 0;
        s=troops[p_id]["soldier"];
        if(!sizeof(s)) return 0;
        k=keys(s);
        foreach(string p in k)
          {  ret+=s[p]["number"];}

	return ret;
}

string get_troop_side(int p_id) {
  if (!mapp(troops[p_id])) return "Ｕ";
  if ( troops[p_id]["side"] == "a" )
    return "Ａ";
  else if ( troops[p_id]["side"] == "d" )
    return "Ｄ";
  else
    return "Ｕ";
}

mixed get_troop_area(int p_id)
{
   string a_id;
   object o_id,env;
   o_id=find_troop(p_id);
   if(!objectp(o_id)) return 0;
   env=environment(o_id);
   if(!objectp(env)) return 0;
   a_id=env->query_aid();
   return a_id;
}
mixed get_troops(int p_id,string p_name)
{
        if(!troops[p_id])
                return 0;
	
	switch(p_name)
	{
// edc 08/05/2001  to get soldier info of the troop
		case "soldier":
			return troops[p_id]["soldier"];
////			
		case "name":
			return get_troop_name(p_id);
		case "position":
			return get_troop_position(p_id);
		case "canbeseen":
			return get_troop_canbeseen(p_id);
                case "total_num":
		        return get_soldier_total_number(p_id);
		case "attack_kills": // this function how many enemy
                                     // can be killed by one attack
                                     // of this troop, but the real
                                     // number should devided by the
                                     // enemy's defence rate
			return get_troop_attack_kills(p_id);
                case "area":
 			return get_troop_area(p_id);
	}	
        if(!troops[p_id][p_name])
                return 0;
        return troops[p_id][p_name];
}
int set_troops(int p_id,string p_name,mixed p_val)
{
        if(!troops[p_id])
                return 0;
        troops[p_id][p_name]=p_val;
        return 1;
}
mixed query_troops()
{
        return troops;
}
mixed list_troops()
{
        return keys(troops);
}
void create()
{
    unguarded(1, (: restore_object, SAVE_FILE, 1 :));
        call_out("troop_heart",5);
    if(sizeof(troops)) {
        int *ts;
        ts=keys(troops);
        foreach(int p in ts) 
		recover_troop( p);
    }
    return;
}
mixed find_troop(int p_id)
{
	return SGTROOP(p_id);
}
int put_troop(int p_id,string r_id)
{
    mixed o_id;
    object o_room;
    string p_area;
    mixed position;

	if(r_id[0..10]!="/a/warroom/") {
		string *rs,r_tmp;
		rs=explode(r_id,"/");
		rs[2]=rs[1];
		rs[1]="warroom";
		r_id=implode(rs,"/");
	}
	o_id=find_troop(p_id);
	if(!o_id)
		return 0;
    troops[p_id]["room"]=r_id;
    o_room=load_object(r_id);
    if(!objectp(o_room))
		return 0;
    o_id->move(o_room);
	p_area=AREA_D->check_area("area",o_room->get_area())[0];
		set_troops(p_id,"area",p_area);
	position=get_troops(p_id,"position");
	MAP_D->set_map_cell(p_area, position[1],position[0],"addtroop",p_id);
            return 1;
}
object new_troop(string nation,string *chars,mapping soldier,string p_room)
{
	int p_id;
	p_id=new_troop_id( nation,chars,soldier);
	put_troop(p_id,p_room);
	return find_troop(p_id);
}
void remove_troop(int p_id)
{
  object o_id,o_char;
  object o_room;
  string p_area;
  string s_area;
  mixed position,chars;
  if(!troops[p_id])
  return;
  o_id=find_troop(p_id);
  if(o_id)
  {
     o_room=environment(o_id);
     if(objectp(o_room))
     {
//        p_area=AREA_D->check_area("area",o_room->get_area())[0];
		p_area=o_room->query_aid();
		 position=get_troops(p_id,"position");
	    MAP_D->set_map_cell(p_area,position[1],position[0],"subtroop",p_id);
     }
  }
  chars=troops[p_id]["chars"];
  if(sizeof(chars))
  {
     foreach(string char in chars)
     {
		 if(CHAR_D->get_char(char,"is_tmp"))
			   CHAR_D->remove_char(char);
		 else
		 {
			p_area=CHAR_D->get_char(char,"area");
			CHAR_D->put_char(char,AREA_D->get_area(p_area,"path")+
				  AREA_D->get_area(p_area,"meeting"));
			o_char=CHAR_D->find_char(char);
			if(objectp(o_char))
			  o_char->simple_action("$N从战场上撤了下来。\n");
		 }
     }
  }
  if(o_id)
  {
	chars=all_inventory(o_id);
	if(sizeof(chars))
	{
		foreach (object o in chars)
		{
			if(o->is_living())
			{
				o->move(VOID_ROOM); // should be wiz
				o->simple_action("$N被一脚踹到了虚无。\n");
			}
			else
				o->remove();
		}
	}
  }

  if(objectp(o_id))
      o_id->remove();
	s_area=troops[p_id]["source_area"];

	if(AREA_D->area_exist(s_area)) {
		mixed p_s;
		int p_num,p_morale,p_oldsoldier;
		string *lis;
		p_s=troops[p_id]["soldier"];
		lis=keys(p_s);
		if(sizeof(p_s)) {
			foreach(string t in lis){
				if(p_s[t]["number"]) {
					p_num=p_s[t]["number"];
					p_oldsoldier=AREA_D->get_area(s_area,"soldier");
// adding 
		if( t == "commando" )
			AREA_D->set_area(s_area,"population",
				AREA_D->get_area(s_area,"population")+p_num);
		else {
			mixed oldsol;
			oldsol = AREA_D->get_area(s_area, "troop");
			if( !mapp(oldsol) ) oldsol = (["footman":p_oldsoldier]);
			oldsol[t] = oldsol[t] + p_num;
//			AREA_D->set_area(s_area,"soldier",
//                                AREA_D->get_area(s_area,"soldier")+p_num);
			AREA_D->set_area(s_area, "troop", oldsol);
			p_morale=AREA_D->get_area(s_area,"morale");
                	p_morale=(p_morale*p_oldsoldier+p_s[t]["morale"]*(p_num+1))/
                        	(p_oldsoldier+p_num+1); // incase divide by zero
			AREA_D->set_area(s_area,"morale",p_morale);

                        p_morale=AREA_D->get_area(s_area,"train");
			p_morale=(p_morale*p_oldsoldier+p_s[t]["train"]*(p_num+1))/
                        	(p_oldsoldier+p_num+1); // incase divide by zero
                        AREA_D->set_area(s_area,"train",p_morale);
		};
// end
/*					if(t!="commando") {
						p_morale=AREA_D->get_area(s_area,"morale");
						p_morale=(p_morale*p_oldsoldier+p_s[t]["morale"]*p_num)/
						(p_oldsoldier+p_num+1); // incase divide by zero
						AREA_D->set_area(s_area,"morale",p_morale);

						p_morale=AREA_D->get_area(s_area,"train");
						p_morale=(p_morale*p_oldsoldier+p_s[t]["train"]*p_num)/
						(p_oldsoldier+p_num+1); // incase divide by zero
						AREA_D->set_area(s_area,"train",p_morale);
					}


					switch(t) {
					case "infantry": 
						AREA_D->set_area(s_area,"soldier",
							AREA_D->get_area(s_area,"soldier")+p_num);
						break;
					case "cavalry" :
						AREA_D->set_area(s_area,"soldier",
							AREA_D->get_area(s_area,"soldier")+p_num);
						AREA_D->set_area(s_area,"horse",
							AREA_D->get_area(s_area,"horse")+p_num);
						break;
						
					case "bowman"  : 
						AREA_D->set_area(s_area,"soldier",
							AREA_D->get_area(s_area,"soldier")+p_num);
						AREA_D->set_area(s_area,"bow",
							AREA_D->get_area(s_area,"bow")+p_num);
						break;
					case "commando"  :
						AREA_D->set_area(s_area,"population",
						AREA_D->get_area(s_area,"population")+p_num);
						break;
					}
*/
				}
			}
		
		}
	}
	map_delete(troops,p_id);
}
void clear_all()
{
	mixed keys;
	int i,sum;
	keys=keys(troops);
	sum=sizeof(keys);
	for(i=0;i<sum;++i)
	{
		remove_troop(keys[i]);
	}	
}
mixed check_troop(string para_name,mixed para_value)
{
        mixed ret;
        string* list;
        list=keys(troops);
        ret=filter_array(list, (:troops[$1][$(para_name)]==$(para_value):));
        return ret;
}
mixed add_soldier(int p_id,
   string p_type,int p_num,int p_mol,int p_tran,int p_eng)
{
	string s_area;
    if(!troops[p_id])
                return 0;
	if(!troops[p_id]["soldier"][p_type])
	{
		troops[p_id]["soldier"][p_type]=([]);
	}
	if(p_num==0)
	{
            map_delete(troops[p_id]["soldier"],p_type);
	}
    else {
	    troops[p_id]["soldier"][p_type]["type"]=p_type;
        troops[p_id]["soldier"][p_type]["number"]=p_num;
	    troops[p_id]["soldier"][p_type]["morale"]=p_mol;
        troops[p_id]["soldier"][p_type]["train"]=p_tran;
	    troops[p_id]["soldier"][p_type]["energy"]=p_eng;
	}

	s_area=troops[p_id]["source_area"];
	if(AREA_D->area_exist(s_area)&&(p_num))
	{
		if( p_type == "commando" )
			AREA_D->set_area(s_area,"population",
                                AREA_D->get_area(s_area,"population")-p_num);
		else {
			mixed oldsol;
			oldsol = AREA_D->get_area(s_area, "soldier");
			if( mapp(oldsol) && oldsol[p_type] ){
				oldsol[p_type] = oldsol[p_type] - p_num;
				AREA_D->set_area(s_area, "soldier",oldsol);
		}
	}
/*		switch(p_type) 
        {
		case "infantry": 
			AREA_D->set_area(s_area,"soldier",
				AREA_D->get_area(s_area,"soldier")-p_num);
			break;
        case "cavalry" :
			AREA_D->set_area(s_area,"soldier",
				AREA_D->get_area(s_area,"soldier")-p_num);
			AREA_D->set_area(s_area,"horse",
				AREA_D->get_area(s_area,"horse")-p_num);
			break;
			
        case "bowman"  : 
			AREA_D->set_area(s_area,"soldier",
				AREA_D->get_area(s_area,"soldier")-p_num);
			AREA_D->set_area(s_area,"bow",
				AREA_D->get_area(s_area,"bow")-p_num);
			break;
        case "commando"  :
			AREA_D->set_area(s_area,"population",
				AREA_D->get_area(s_area,"population")-p_num);
			break;

		}
*/
	}
	return troops[p_id]["soldier"];
}
mixed set_soldier(int p_id,string p_type,string p_what,mixed p_val)
{
        if(!troops[p_id])
                return 0;
	if(!troops[p_id]["soldier"][p_type])
		return 0;
	if(p_what=="")
		troops[p_id]["soldier"][p_type]=p_val;
	else
		troops[p_id]["soldier"][p_type][p_what]=p_val;
	return troops[p_id]["soldier"][p_type];
}
mixed get_soldier(int p_id,string p_type,string p_what)
{
        if(!troops[p_id])
                return 0;
	if(!troops[p_id]["soldier"][p_type])
		return 0;
	if(!p_what || (p_what==""))
		return troops[p_id]["soldier"][p_type];
	return troops[p_id]["soldier"][p_type][p_what];
}
int illegal_troop(int t_id)
{
	string p_side;
	int task_id,*t;
    	object o,env;

	if(!troops[t_id]) return 1; 
	p_side=troops[t_id]["side"];
	if((p_side!="a")&&(p_side!="d")) return 1;
	task_id=troops[t_id]["task_id"];
	if(p_side=="a")
		t=TASK_D->get_task(task_id,"att_army");
	else
		t=TASK_D->get_task(task_id,"def_army");
	if(!t)t=({});
	if(member_array(t_id,t)==-1) return 2;
	o=find_troop(t_id);
	if(!objectp(o)) return 3;
	env=environment(o);
	if(!objectp(env)) return 4;
	return 0;
}

int get_char_troop(string id) {
	int *t;
	string *cs; //chars
	t=keys(troops);
	if(!sizeof(t)) return 0; // no troop
	foreach(int mt in t) {
		cs=troops[mt]["chars"];
		if(!sizeof(cs)) continue;
		if(member_array(id,cs)!=-1) return mt;
	}
	return 0;
}
// New function recover energy
private void recover_energy(int p_id)
{
        int i, x, y, weather;
        mapping sol;
        string area, *list, envir, type;
        object ob, env;

	int task_id=troops[p_id]["task_id"];
	if(TASK_D->get_task(task_id,"start_war")!="yes")
		return;

	if((troops[p_id]["side"]=="a")&&(random(2)==0))
		add_morale(p_id,-1);
        ob = find_troop(p_id);
        env = environment(ob);
        area = env->query_aid();
        weather = AREA_D->get_area(area, "weather");

        x = env->query_pos()[0];
        y = env->query_pos()[1];
        envir = MAP_D->get_map_cell(area, x, y, "m");

        sol = troops[p_id]["soldier"];
        list = keys(sol);
        for( i = 0; i < sizeof(list); i++){
                type = list[i];
                if( file_size(TROOP_TYPE(type)) != -1 )
                        sol[type]["energy"] = sol[type]["energy"] +
				load_object(TROOP_TYPE(type))->query_energy_recover(envir, weather,ob->query("zhenfa"))
				*((sol[type]["morale"]+sol[type]["train"])/8+5)/10;
                else sol[type]["energy"] = sol[type]["energy"] +load_object(TROOP_TYPE("commando"))->query_energy_recover(envir,weather,ob->query("zhenfa"))
			*((sol[type]["morale"]+sol[type]["train"])/8+5)/10;
		if( sol[type]["energy"] > 30 ) sol[type]["energy"] = 30;
        };
}
void recover_troop(int p_id) {
   string p_room;
   p_room=troops[p_id]["room"];
   put_troop(p_id,p_room);   

}
void remove() {
	save_mark=20;
	save_data();
}
int clean_up() {
   return 0; // means never_again
}
void add_morale(mixed p_id, int va) {
	mixed sol;
	string *ss;
	if(arrayp(p_id)) {
		if(sizeof(p_id)) {
			foreach(int v in p_id)
				add_morale(v,va);
		}
		return;
	}
	if(!mapp(troops[p_id])) return;
	sol=troops[p_id]["soldier"];
	if(!sizeof(sol)) return;
	ss=keys(sol);
	foreach(string s in ss) {
		troops[p_id]["soldier"][s]["morale"]+=va;
		if(troops[p_id]["soldier"][s]["morale"]<0)
			troops[p_id]["soldier"][s]["morale"]=0;
		if(troops[p_id]["soldier"][s]["morale"]>200)
			troops[p_id]["soldier"][s]["morale"]=200;

	}
}

void add_train(mixed p_id, int va) {
	mixed sol;
	string *ss;
	if(arrayp(p_id)) {
		if(sizeof(p_id)) {
			foreach(int v in p_id)
				add_train(v,va);
		}
		return;
	}
	if(!mapp(troops[p_id])) return;
	sol=troops[p_id]["soldier"];
	if(!sizeof(sol)) return;
	ss=keys(sol);
	foreach(string s in ss) {
		troops[p_id]["soldier"][s]["train"]+=va;
		if(troops[p_id]["soldier"][s]["train"]<0)
			troops[p_id]["soldier"][s]["train"]=0;
		if(troops[p_id]["soldier"][s]["train"]>200)
			troops[p_id]["soldier"][s]["train"]=200;

	}
}
int troop_exist(int t_id) {
	return mapp(troops[t_id]);
}
// don't call this until you know what you are going to do
int force_clear() {
	troops=([]);
	save_data();
	return 1;
}
