// this is used to handle auto cast
// by suicide on 2001.4.29
#define __SGJI__ "/sgdomain/jimou/"

string point_tostring(mixed point);
int can_fenfa(int p_id)
{
        int* troops;
        string where;
        int i,x,y,xtmp,ytmp,cn,x2,y2,id;
 
        troops = TROOP_D->list_troops();
        troops = troops - ({ p_id });
        if( !sizeof(troops) )return 0;
        where = TROOP_D->get_troop_area(p_id);
        if(sizeof(troops) < 2)return 0;
 
        cn =0;
        xtmp = -1;   
        ytmp= -1;
        x = TROOP_D->get_troop_position(p_id)[0];
        y = TROOP_D->get_troop_position(p_id)[1];
        for( i = 0; i < sizeof(troops); i++ ){
                id = troops[i];
                x2 = TROOP_D->get_troop_position(id)[0];
                y2 = TROOP_D->get_troop_position(id)[1];
 
                if( TROOP_D->get_troop_area(id) != where )continue;
                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 1 ||
        TROOP_D->get_troop_side(id)==TROOP_D->get_troop_side(p_id))continue;
                if(xtmp== -1 || ytmp == -1)
                { xtmp = x2;
                 ytmp = y2;
                                cn =1;
                }
                else {if (xtmp != x2 || ytmp!= y2)
                cn++;
                }
                }
        if(cn<2)return 0;
return cn;
}

int can_cast(int p_id)
{
        int* list;
        int* troops; 
        string where, sid;
        int x,y,x2,y2;

        troops = TROOP_D->list_troops();
        troops -= ({p_id});
        list = troops;

        if( !sizeof(troops) )return 0;
        where = TROOP_D->get_troop_area(p_id);
        sid = TROOP_D->get_troop_side(p_id);
        foreach(int e_id in troops)
        {
        x =TROOP_D->get_troop_position(p_id)[0];
        y = TROOP_D->get_troop_position(p_id)[1];
        
        x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];
                if( TROOP_D->get_troop_area(e_id) != where )
                {list-=({e_id});
                        continue;
                }
                if(TROOP_D->get_troop_side(e_id) == sid)
                {       list-=({e_id});
                        continue;
                }
                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 9 )
                {list-=({e_id});
                        continue;
                }
        }
                 
        if(sizeof(list))
        {
            //added by suicide in 2001.5.9 to select leader to cast jimou
            string leader;
            int task_id,leader_troop;
            task_id=TROOP_D->get_troops(p_id,"task_id");
            if (!task_id)  return 0;
            if (sid=="D") leader=TASK_D->get_task(task_id,"def_leader");
            else leader=TASK_D->get_task(task_id,"att_leader"); 
            if (!leader) return 0;
            leader_troop=CHAR_D->get_char(leader,"troop");
            if (!leader_troop) return list[random(sizeof(list))];
            else
              if (member_array(leader_troop,list)!=-1) return leader_troop;
            else
            //added end;
	      return list[random(sizeof(list))];
	}
                        
        return 0;
}




void cast_jm(string p_id, int t_id, int skill, int type)
{
        object ob;
        int e_id;
        int i;
        string e_name;
        string* e_chars;
        mapping cond;
        
        ob= CHAR_D->find_char(p_id);

        if(type ==0 )
        {
         if(i=can_fenfa(t_id))
          { __SGJI__"fenfa.c"->main(ob);
           SGSYS(p_id+"use fenfa skill.");
           //if (i<4) //不被四面围攻就逃回城
              {
              mixed mtmp=TROOP_D->get_troops(t_id,"command");
              mtmp["action"]="match";
              mtmp["target"]=point_tostring(MAP_D->get_city(CHAR_D->get_char(p_id,"area"),"center")); 
              TROOP_D->set_troops(t_id,"command",mtmp);
              SGSYS(sprintf("troop%d Go back to City center.",t_id));
              }
           return;
          }
         }

        if(type == 1)
        {
         e_id = can_cast(t_id);
         if(e_id)
          {
           //added by suicide in 2001.5.9 for pursue player troop to attack.
           //modified by suicide in 2001.7.25 for forbid persue when def leader is online.
           string leader;
           int task_id;
           mixed mtmp=TROOP_D->get_troops(t_id,"command");

           task_id=TROOP_D->get_troops(t_id,"task_id");
           if (!task_id)  return 0;
           //for only def side NPC troops can call this part, so 
           //no judge which side the troop is at.def side is default .
           leader=TASK_D->get_task(task_id,"def_leader");
           if (CHAR_D->get_char(leader,"status")!=STATUS_ONLINE)
              i=random(2);
           /*{
           if (!mtmp||((mtmp["action"]!="match")&&(mtmp["action"]!="pursue")))
            {
           mtmp["action"]="pursue";
           mtmp["aim"]=e_id;
           TROOP_D->set_troops(t_id,"command",mtmp);
           SGSYS(sprintf("troop%d pursue troop%d.",t_id,e_id));
           return;
            }
           }*/
           else
             return;  //for player leader online , so npc no use jimou 
        
           //ended 
           i = random(2);
           if(i)
           {
            e_chars = TROOP_D->get_troops(e_id,"chars");
            e_name = e_chars[random(sizeof(e_chars))];
            if(!e_chars) return;
            SGSYS(p_id+"use hunluan skill.");
            __SGJI__"hunluan.c"->show_result(ob,e_name,skill,t_id,e_id);
            return;
           }
          }
         else 
           {   
           e_chars = TROOP_D->get_troops(e_id,"chars");
           if(!e_chars) return;
           e_name = e_chars[random(sizeof(e_chars))];
           SGSYS(p_id+"use shidu skill.");
           __SGJI__"shidu.c"->show_result(ob,e_name,skill,t_id,e_id);
           return;
           }
         SGSYS("no target.");
        }
        
        if(type == 2)
        {
         if(t_id)
            { cond = TROOP_D->get_troops(t_id,"conds");
              if (!cond) return;
                  if(cond["poison"])
                {
                SGSYS(p_id+"use jiedu skill.");
                __SGJI__"jiedu.c"->show_result(ob," ",skill,t_id,t_id);
                }       
                 if(cond["confuse"])
                {
                SGSYS(p_id+"use shoushi skill.");
                __SGJI__"shoushi.c"->show_result(ob," ",skill,t_id,t_id);
                }
            }
        }
                        
return;
}        


void auto_jimou(int t_id)
{
mixed  npc_char=TROOP_D->get_troops(t_id,"chars");
if (!npc_char) return;
if (arrayp(npc_char)) 
    npc_char=TROOP_D->get_troops(t_id,"chars")[0];
if (!random(3))  //1/3机会
    cast_jm(npc_char,t_id,100,2);  //用100的技能去完全解除npc部队的中毒或者是混乱状态。
if (random(3)==1)
   cast_jm(npc_char,t_id,100,0);
else 
   if (!random(3))
   cast_jm(npc_char,t_id,100,1);

}
