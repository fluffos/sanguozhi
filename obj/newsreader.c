// Updated by stefan on 10 Jan 1997
/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** newsreader.c
**
** Basic newsreader to interface with the news server.
**
** 941224, Deathblade: created.
** 950702, Rust: added completion and menus for the g command.
** 950811, Deathblade: convert to use class news_msg.
*/


#include <mudlib.h>
#include <classes.h>
#include <edit.h>

inherit M_INPUT;
inherit M_COMPLETE;
inherit M_ACCESS;
inherit M_GRAMMAR;

inherit CLASS_NEWSMSG;


private static string   current_group;

#define TOP_PROMPT      ("(...) " + mud_name() + "新闻 [q?lg] > ")

#define STANDARD_WRAP_WIDTH     68
#define FOLLOWUP_WRAP_WIDTH     76

nomask void receive_top_cmd(string cmd);
nomask void receive_grp_cmd(string cmd);
nomask void receive_msg_cmd(string cmd);


private nomask void quit_news()
{
    /* save the player's news reading state */
    this_body()->save_me();

    modal_pop();
    destruct();
}

varargs private nomask int get_current_id(string group_name)
{
    if ( !group_name )
        group_name = current_group;

    /*
    ** -1 to get the "current" message.  The body records the _next_
    ** message to read.
    */
    return this_body()->get_news_group_id(group_name)-1 ;
}


private int count_unread_messages(string group, int all_messages)
{
    int * ids = NEWS_D->get_messages(group);
    int id;
    class news_msg msg;
    int count = 0;
    int read_thru_id;

    read_thru_id = get_current_id( group );

    if ( !all_messages )
    {
        ids = filter_array(ids, (: $1 > $(read_thru_id):));
    }
    foreach ( id in ids )
    {
        msg = NEWS_D->get_message(group, id);
        if ( msg->body )
        {
            count++;
        }
    }
    return count;
}


private nomask string format_group_line(string group)
{
    int last_id;
    int unread = count_unread_messages(group, 1);

    last_id = NEWS_D->get_group_last_id(group);
    return sprintf("  %-40s (%d 条留言, %d 条未读)",
      group,
      unread,
      count_unread_messages(group, 0));
}

private nomask void add_new_groups()
{
    string * groups;

    groups = NEWS_D->get_groups() - this_body()->subscribed_groups();
    if ( sizeof(groups) == 0 )
        return;

    /* set each next-id-to-read to 1 */
    map_array(groups, "set_news_group_id", this_body(), 1);

    /*
    ** Note: this should occur _after_ the set_news_group_id so that
    ** the number of unread messages is computed correctly.
    **
//### we should ask the user about these. provide options:
//### [ynaql?] or yes (add), no (skip), all, quit (adding), list,
//### and help
    */
    write(//"Auto-subscribing to:\n" +
          "自动登记以下新闻组：\n" +
      implode(map_array(groups, (: format_group_line :)), "\n") + "\n");
}

private nomask string grp_cmd_prompt()
{
    int unread_no;

    unread_no = count_unread_messages(current_group, 0);

    return sprintf("(%s:%d) %d 条留言 %d 条未读 [q?lLmgpnc] > ",
      current_group,
      /* ### hrm. this is current. needs to be NEXT message. */
      get_current_id(current_group),
      count_unread_messages(current_group, 1),
      unread_no
    );
}

private nomask string msg_cmd_prompt()
{
    return sprintf("(%s:%d) %d 条剩余 [q?lLmgprRfFncMD] > ",
      current_group,
      get_current_id(current_group),
      count_unread_messages(current_group, 0)
    );
}

private nomask void switch_to_top()
{
    modal_push((: receive_top_cmd :), TOP_PROMPT);
}

private nomask void switch_to_group()
{
    modal_func((: receive_grp_cmd :), (: grp_cmd_prompt :));
}

private nomask void switch_to_message()
{
    modal_func((: receive_msg_cmd :), (: msg_cmd_prompt :));
}


private static mixed group_selection_menu_items;
private nomask void menu_select_newsgroup(string num)
{
    int index;

    if ( num=="q" )
    {
        //write( "Selection aborted.\n");
        write("放弃选择。\n");
        if( !current_group) destruct( this_object());
        modal_func((: receive_msg_cmd :), (: msg_cmd_prompt :));
        return;
    }

    if ( !sscanf(num,"%d",index) || index < 1 || index > 
      sizeof(group_selection_menu_items) )
    {
        //write("Invalid selection.\n");
        write("非法选择。\n");
        return;
    }

    current_group = group_selection_menu_items[index-1];
    group_selection_menu_items = 0;
    switch_to_group();
}

private nomask void menu_select_movegroup(string num)
{
    string to_group;
    int index;
    if( num == "q" )
    {
        //write( "Aborting Move.\n" );
        write("放弃移动。\n");
        modal_func((: receive_msg_cmd :), (: msg_cmd_prompt :));
        return;
    }
    if( !sscanf( num, "%d", index )|| index < 1 || index >
      sizeof( group_selection_menu_items))
    {
        //write( "Invalid selection.\n");
        write("非法选择。\n");
        return;
    }
    to_group = group_selection_menu_items[index - 1];
    group_selection_menu_items = 0;
    NEWS_D->move_post( current_group, get_current_id(current_group), to_group);
    modal_func( (:receive_msg_cmd :), (: msg_cmd_prompt :));
}

private nomask void read_group(string group)
{
    string* matches;
    int i;

    /*
      if ( group == "" )
      {
      switch_to_top();
      return;
      }
      */

    matches = complete(group, NEWS_D->get_groups());

    switch ( sizeof(matches) )
    {
    case 0:
        //write("No such group.\n");
        write("没有这个新闻组。\n");
        if(!current_group) destruct( this_object());
        return;

    case 1:
        current_group = matches[0];
        break;

    default:
        write("\n请选择新闻组序号：\n" //"\nSelect group by number:\n"
          "----------------------------\n");
        for(i=1; i<=sizeof(matches);i++)
            printf("%-4d%s\n",i,matches[i-1]);

        group_selection_menu_items = matches;
        modal_func((: menu_select_newsgroup:), "[#q] ");

        return;
    }

    switch_to_group();
}

private nomask void receive_group(mixed group)
{
    if ( group == -1 )
        destruct(this_object());

    read_group(trim_spaces(group));
}

private nomask int test_for_new(string group)
{
    if( count_unread_messages( group, 0 )) return 1;
    return 0;
}

private nomask void display_groups_with_new( string arg )
{
    string * groups;

    groups = filter_array(this_body()->subscribed_groups(), (: test_for_new :));

    if ( sizeof(groups) == 0 )
    {
        write("No new news.\n");

        if(arg=="c"||arg=="-c"||arg=="C"||arg=="-C")
        {
            destruct( this_object());
        }
        modal_push((: receive_top_cmd :), TOP_PROMPT);
    }
    else
    {
        string * list;

        modal_push((: receive_grp_cmd :), (: grp_cmd_prompt :));

        current_group = groups[0];

        list = ({//"Groups with new messages:"
                 "有新留言的新闻组：", ""}) +
        map_array(groups, (: format_group_line :));

        more(list);
        if( arg == "C" || arg == "-C")
        {
            quit_news();
        }
    }
}

private nomask void next_group()
{
    string * groups;
    int max_group;
    int i;
    int next_group;

    groups = filter_array(this_body()->subscribed_groups(), (: test_for_new :));
    max_group = sizeof( groups ) - 1;

    if( max_group == -1 )
    {
        //write("No more groups with new news.\n");
        write("没有有新留言的新闻组了。\n");
        switch_to_top();
    }
    else
    {
        for( i = 0; i <= max_group; i++ )
        {
            if( groups[i] == current_group )
            {
                if( i == max_group )
                    next_group = 0;
                else
                    next_group = i + 1;
                break;
            }
        }
        current_group = groups[next_group];
        write("进入: " + current_group + "\n");
        switch_to_group();
    }
}

private nomask varargs
string format_message_line(int short_fmt, int id, int noremoved)
{
    class news_msg msg;
    string subject;

    msg = NEWS_D->get_message(current_group, id);

    if (!msg || ! msg->body) {
        if (noremoved)
            return 0;
        else
            subject = sprintf(short_fmt ? "%d. %s" : "%4d. %-35s", id, " (已删除)");
    } else
        subject = msg->subject;                                                         
                               
    return sprintf(short_fmt ? "%d. %s  [%s on %s]" :
      "%4d. %-35s [%-10s on %s]",
      id,
      subject[0..34],
      msg->poster,
      intp(msg->time) ? ctime(msg->time)[4..9] : msg->time);
}

private nomask void display_messages(int display_all)
{
    int *       ids;
    string *    lines;

    ids = NEWS_D->get_messages(current_group);

    if ( !display_all )
    {
        int read_thru_id;

        read_thru_id = get_current_id();
        ids = filter_array(ids, (: $1 > $(read_thru_id) :) );
    }

    lines = map_array(sort_array(ids, 1), (: format_message_line(0, $1, 1) :)) - ({ 0 });
    lines = ({sprintf("%s 的留言有:", current_group)}) + lines + ({""});
    more(lines);
}

nomask void wrap_post(string * text)
{
    int i = sizeof(text);

    while ( i-- )
    {
        /* only wrap really long lines */
        if ( sizeof(text[i]) > 78 )
        {
            /* wrap to different widths, based on the text */
            int width = text[i][0]=='>' ? FOLLOWUP_WRAP_WIDTH : STANDARD_WRAP_WIDTH;
            if ( sizeof(text[i]) > width )
                text[i] = wrap(text[i], width);
        }
    }
}

private nomask void receive_post_text(string subject, string * text)
{
    int id;

    if ( !text )
    {
        write("Post aborted.\n");
        write("放弃张贴新闻。\n");
        return;
    }

    wrap_post(text);

    id = NEWS_D->post(current_group, subject, implode(text, "\n") + "\n");
    write("Posted:  " + format_message_line(1, id) + "\n");
}

private nomask void receive_post_subject(mixed subject)
{
    if ( subject == -1 )
        destruct(this_object());

    if ( subject == "" )
    {
        //write("Post aborted.\n");
        write("放弃张贴新闻。\n");
        return;
    }

    new(EDIT_OB, EDIT_TEXT, 0, (: receive_post_text, subject :));
}

private nomask void post_message()
{
    //write("Subject: ");
        if ( !NEWS_D->post_permitted(this_user(), current_group)) {
        write("你无权在这个新闻组张贴留言。\n");
        return;
    }

    write("题目：");
    modal_simple((: receive_post_subject :));
}

private nomask class news_msg get_current_message()
{
    class news_msg msg;

    msg = NEWS_D->get_message(current_group, get_current_id());

    if ( !msg || !msg->body )
        return 0;

    return msg;
}

nomask void receive_reply_text( string * text)
{
    class news_msg msg = get_current_message();

    if ( !text )
    {
        //write("Post aborted.\n");
        write("放弃张贴新闻。\n");
        return;
    }

    wrap_post(text);

    this_body()->query_mailer()->send_news_reply(
      "Re: " + msg->subject,
      text,
      lower_case( msg->poster )
    );
}

private nomask void reply_to_message()
{
    class news_msg msg = get_current_message();

    if ( !msg )
    {
        //write("You may not reply to that message -- it was removed.\n");
        write("你无法对它回信 --- 原来的留言已经被删除了。\n");
        return;
    }
    new(EDIT_OB, EDIT_TEXT, 0, (: receive_reply_text :));
}

private nomask void reply_with_message()
{
    class news_msg msg = get_current_message();
    string * lines;

    if ( !msg )
    {
        //write("You may not reply to that message -- it was removed.\n");
        write("你无法对它回信 --- 原来的留言已经被删除了。\n");
        return;
    }

    lines = ({ sprintf("On %s %s wrote post #%d in %s:",
        intp(msg->time) ? ctime(msg->time) : msg->time,
        msg->poster,
        get_current_id(),
        current_group,
      )
    });

    lines += map_array(explode(msg->body, "\n"), (: "> " + $1 :) );

    new(EDIT_OB, EDIT_TEXT, lines, (: receive_reply_text :));
}

nomask void receive_followup_text(string * text)
{
    int id;

    if ( !text )
    {
        //write("Post aborted.\n");
        write("张贴放弃。\n");
        return;
    }

    wrap_post(text);

    /*
    ** -1 to get the "current" message.  The player records the _next_
    ** message to read.
    */
    id = NEWS_D->followup(current_group,
      get_current_id(),
      implode(text, "\n") + "\n");
    write("Posted:  " + format_message_line(1, id) + "\n");
}

private nomask void followup_to_message()
{
    class news_msg msg = get_current_message();

    if ( !msg )
    {
        //write("You may not followup to that message -- it was removed.\n");
        write("你无法张贴续帖 --- 原来的留言已经被删除了。\n");
        return;
    }
    
    if ( !NEWS_D->post_permitted(this_user(), current_group)) {
        write("你无权在这个新闻组张贴留言。\n");
        return;
    }

    new(EDIT_OB, EDIT_TEXT, 0, (: receive_followup_text :));
}

private nomask void followup_with_message()
{
    class news_msg msg = get_current_message();
    string * lines;

    if ( !msg )
    {
        //write("You may not followup to that message -- it was removed.\n");
        write("你无法张贴续帖 --- 原来的留言已经被删除了。\n");
        return;
    }
    if ( !NEWS_D->post_permitted(this_user(), current_group)) {
        write("你无权在这个新闻组张贴留言。\n");
        return;
    }

    lines = ({ sprintf("On %s %s wrote post #%d:",
        intp(msg->time) ? ctime(msg->time) : msg->time,
        msg->poster, get_current_id()) });

    lines += map_array(explode(msg->body, "\n"), (: "> " + $1 :) );

    new(EDIT_OB, EDIT_TEXT, lines, (: receive_followup_text :));
}

private nomask int read_next_message(int skip_allowed)
{
    int msg_id;
    int skipped;
    class news_msg msg;
    string post;
    int last = NEWS_D->get_group_last_id(current_group);
    
    msg_id = get_current_id() + 1;

    do
    {        
        if ( msg_id > last )
        {
            /*
            ** Do a bit of extra work when messages have been skipped.
            */
            if ( skipped )
            {
                printf(//"Skipped %d removed messages.\n",
                       "跳过 %d 封已删除的留言。\n",
                  msg_id - (get_current_id() + 1));

                /*
                ** Update the body's current message number (to mark all
                ** as read).
                */
                this_body()->set_news_group_id(current_group, msg_id);
            }

            //write("No more messages.\n");
            write("没有留言了。\n");
            switch_to_group();
            return 1;
        }
        msg = NEWS_D->get_message(current_group, msg_id);
        
        if ( msg && msg->body )
        {
            /* don't loop any more... take this message */
            skip_allowed = 0;
        }
        else if ( skip_allowed )
        {
            /* mark we have skipped at least one... move ahead for more */
            skipped = 1;
            ++msg_id;
        }

    } while ( skip_allowed );


    if ( skipped )
    {
        printf(//"Skipped %d removed messages.\n",
               "跳过 %d 封已删除的留言。\n",
          msg_id - (get_current_id() + 1));
    }

    /*
    ** Set the next-to-read id.  Always move to the message prompt.
    */
    this_body()->set_news_group_id(current_group, msg_id + 1);
    switch_to_message();

    if ( msg ) {
        post = sprintf("时间:  %-40sPost-id: %d (%d Last)\n"
                "作者:  %s\n"
                "题目:  %s\n"
                "----------------------------------------------------------------------\n"
                "%s",
                intp(msg->time) ? ctime(msg->time) : msg->time,
                msg_id,
                NEWS_D->get_group_last_id(current_group),
                msg->poster,
                msg->subject,
                msg->body ? msg->body : "*** 已删除 ***");
    }
    else {
        post = sprintf("Post-id: %d (%d Last)\n\n*** 已删除 ***",
                       msg_id, NEWS_D->get_group_last_id(current_group));
    }
    more(post);

    return 0;
}

varargs nomask void begin_reading(string arg);
private nomask void global_commands(string cmd)
{
    if( cmd == "q" )
    {
        quit_news();
    }
    else if ( cmd == "")
    {
        if( sizeof(filter_array(this_body()->subscribed_groups(), 
            (: test_for_new :) )) )
        {
            modal_pop();
            begin_reading();
            return;
        }
        else quit_news();
    }
    else if ( cmd[0] == 'g' )
    {
        if ( strlen(cmd) > 1 )
        {
            read_group(trim_spaces(cmd[1..]));
        }
        else
        {
            modal_func((: receive_group :),
              //"Which group (Or enter for a menu)? "
              "哪个新闻组？(或<回车>来显示主选单)");
        }
    }
    else
    {
        write("无此命令，用 ? 来获取帮助信息。\n"); 
        //"Unknown command. Type ? for help.\n");
    }
}

private nomask void group_commands(string cmd)
{
    int id;

    if ( cmd == "l" || cmd == "L" )
    {
        display_messages(cmd == "L");
    }
    else if ( cmd == "m" )
    {
        switch_to_top();
    }
    else if ( cmd == "p" )
    {
        post_message();
    }
    else if ( cmd == "n" )
    {
        next_group();
    }
    else if ( cmd == "c" )
    {
        id = NEWS_D->get_group_last_id(current_group) + 1;
        this_body()->set_news_group_id(current_group, id);
        //write("All posts marked as read.\n");
        write("所有的贴子都设成读过标志。\n");
        next_group();
    }
    else if ( cmd == "" )
    {
        if ( read_next_message(1) )
        {
            next_group();
        }
    }
    else if( id = to_int(trim_spaces(cmd)) )
    {
        if ( id < 1 )
            id = 1;
        else if ( id > NEWS_D->get_group_last_id(current_group) )
            id = NEWS_D->get_group_last_id(current_group);
        this_body()->set_news_group_id(current_group, id);
        read_next_message(0);
    }
    else
    {
        global_commands(cmd);
    }
}

private nomask void receive_remove_verify(string str)
{
    if ( str[0] != 'y' && str[0] != 'Y' )
    {
        //write("Removal aborted.\n");
        write("放弃删除。\n");
        return;
    }

    NEWS_D->remove_post(current_group, get_current_id());
}

private nomask void get_move_group( string str )
{
    string * matches;
    int i;

    matches = complete( str, NEWS_D->get_groups());
    switch( sizeof(matches))
    {
    case 0:
        //write( "No such group.\n");
        write("没有这个新闻组。\n");
        return;
    case 1:
        NEWS_D->move_post( current_group,  get_current_id(current_group), matches[0] );
        break;
    default:
        write(//"\nSelect group by number:\n"
              "\n用新闻组序号来选择：\n"
          "--------------------------------\n");
        for( i = 1; i <= sizeof(matches); i++)
            printf("%-4d%s\n",i,matches[i-1]);

        group_selection_menu_items = matches;
        modal_func((: menu_select_movegroup:), "[#q] ");
        return;
    }
}
private nomask void get_send_email(string email)
{string pid ;
 string data;
 class news_msg msg = get_current_message();
 pid = this_user()->query_userid();
 if (email == "")
     email = this_user()->query_email();
 if (email == ""){
     write("%^RED%^没有找到默认的email地址,无法转发post!%^RESET%^\n"); 
     return;
     }
 data  = "(转发自" + current_group + 
         sprintf("  ID:%d  ",get_current_id(current_group))+
         "作者:" + msg->userid+ ")\n" + msg->body;
NEWS_D->post_to_email(email,msg->subject,data);
}

private nomask void send_post_as_email()
{
    write( //"Move post to: ");
           "留言转发的email[默认为自己注册的email地址]：");
    modal_simple( (: get_send_email :));
}

private nomask void receive_move_verify( string str )
{
    if( str[0] != 'y' && str[0] != 'Y' )
    {
        //write( "Move aborted.\n");
        write("移动放弃。\n");
        return;
    }
    write( //"Move post to: ");
           "把留言移到：");
    modal_simple( (: get_move_group :));
}

private nomask void remove_message()
{
    class news_msg msg = get_current_message();

    if ( !msg )
    {
        //write("This post has already been removed.\n");
        write("这个贴子已经被删除了。\n");
        return;
    }
    if ( !adminp(this_user()) &&
      msg->userid != this_user()->query_userid() )
    {
        //write("You are not allowed to remove that post.\n");
        write("你无权删除那张帖子。\n");
        return;
    }

    printf(//"Removing: %s\nAre you sure? [yn] > ",
           "准备删除：%s\n你确定吗？[yn] > ",
      format_message_line(1, get_current_id()));
    modal_simple((: receive_remove_verify :));
}


private nomask void receive_top_cmd(mixed cmd)
{
    if ( cmd == -1 )
        destruct(this_object());

    cmd = trim_spaces(cmd);
    if ( cmd == "?" )
    {
/*        write("\n" +
          "This is the prompt for commands that apply before "
          "you have picked a newsgroup.  The commands that "
          "apply are:" +
          "\n"
          "  q   quit reading news\n"
          "  ?   this help\n"
          "  l   list newsgroups\n"
          "  g   go to a newsgroup\n"
          "\n"
          "Just type a command at the prompt and hit return.\n"
        );
*/
        write("\n这是当你进入新闻组之前的命令选单：\n"
              "     q   - 退出浏览\n"
              "     ?   - 本帮助\n"
              "     l   - 列出新闻组\n"
              "     g   - 进入新闻组\n"
              "\n"
              "键入命令然后回车就行了。\n");
    }
    else if ( cmd == "l" )
    {
        string * list;

        list = map_array(NEWS_D->get_groups(), (: format_group_line :));
        list = ({ "", //"Available groups are:"
                      "现有的新闻组有：" }) + list;
        more(list);
    }
    else
    {
        global_commands(cmd);
    }
}

private nomask void receive_grp_cmd(mixed cmd)
{
    if ( cmd == -1 )
        destruct(this_object());

    cmd = trim_spaces(cmd);
    if ( cmd == "?" )
    {
/*        write("\n" +
          "This is the prompt for commands that apply to the "
          "current newsgroup you are reading (" + current_group +
          ").  The commands that apply are:" +
          "\n"
          "  q   quit reading news\n"
          "  ?   this help\n"
          "  l   list new messages\n"
          "  L   list all messages\n"
          "  m   main news menu\n"
          "  g   go to a newsgroup\n"
          "  p   post message\n"
          "  n   next newsgroup with new news\n"
          "  c   mark all messages as read (catch up)\n"
          "\n"
          "  g group   goes to newsgroup \"group\"\n"
          "  <return>  read messages or go to next newsgroup with new news\n"
          "\n"
          "Just type a command at the prompt and hit return.\n"
        );
 */
        write("\n这是你进入一个新闻组之后的命令选单：\n"
              "当前新闻组：( "+current_group+" )\n"
              "     q           - 退出浏览新闻\n"
              "     ?           - 本帮助\n"
              "     l           - 列出未读的留言\n"
              "     L           - 列出所有的留言\n"
              "     m           - 返回主选单\n"
              "     g <新闻组>  - 进入新闻组\n"
              "     p           - 张贴留言\n"
              "     n           - 进入下一个有未读留言的新闻组\n"
              "     c           - 把所有的留言都记为已读\n"
              "\n"
              "   <回车>        - 读取下一条留言或进入一个有未读留言的新闻组\n"
              "\n"
              "键入命令然后回车就行了。\n");        
    }
    else
    {
        group_commands(cmd);
    }
}

private nomask void receive_msg_cmd(mixed cmd)
{
    if (cmd == -1) {
        destruct(this_object());
        return;
    }

    cmd = trim_spaces(cmd);
    if ( cmd == "?" )
    {
/*        write("\n" +
          "This is the prompt for commands that apply to the "
          "current newsgroup you are reading (" + current_group +
          ").  The commands that apply are:" +
          "\n"
          "  q   quit reading news\n"
          "  ?   this help\n"
          "  l   list new messages\n"
          "  L   list all messages\n"
          "  m   main news menu\n"
          "  g   go to a newsgroup\n"
          "  p   post message\n"
          "  r   reply to this message\n"
          "  R   reply to this message, quoting it\n"
          "  f   post a followup to this message\n"
          "  F   post a followup to this message, quoting it\n"
          "  n   next newsgroup with new news\n"
          "  c   mark all messages as read (catch up)\n"
          "  M   Move post to a different group [owner/admin]\n"
          "  D   remove this message\n"
          "  g group   goes to newsgroup \"group\"\n"
          "  <return>  read messages or go to next newsgroup with new news\n"
          "\n"
          "Just type a command at the prompt and hit return.\n"
        );
*/
        write("\n这是你进入一个新闻组之后的命令选单：\n"
              "当前新闻组：( "+current_group+" )\n"
              "     q           - 退出浏览新闻\n"
              "     ?           - 本帮助\n"
              "     l           - 列出未读的留言\n"
              "     L           - 列出所有的留言\n"
              "     m           - 返回主选单\n"
              "     g <新闻组>  - 进入新闻组\n"
              "     p           - 张贴留言\n"
              "     r           - 回信留言\n"
              "     R           - 回信留言，并引用它\n"
              "     f           - 张贴一个跟贴\n"
              "     F           - 张贴一个跟贴，并引用它\n"
              "     n           - 进入下一个有未读留言的新闻组\n"
              "     c           - 把所有的留言都记为已读\n"
              "     M           - 把留言移到另一个新闻组 [自己/大神]\n"
              "     E           - 把留言转发到email信箱\n"
              "     D           - 删除目前正在阅读的留言\n"
              "   <回车>        - 读取下一条留言或进入一个有未读留言的新闻组\n"
              "\n"
              "键入命令然后回车就行了。\n");
    }
    else if (cmd == "D" )
    {
        remove_message();
    }
    else if (cmd == "r" )
    {
        reply_to_message();
    }
    else if ( cmd == "R" )
    {
        reply_with_message();
    }
    else if ( cmd == "f" )
    {
        followup_to_message();
    }
    else if ( cmd == "F" )
    {
        followup_with_message();
    }
    else if ( cmd == "M" )
    {
        write( "移动留言？[y/N]");
        modal_simple((: receive_move_verify :));
    }
    else if ( cmd == "E" )
    {
        send_post_as_email();
    }
    else
    {
        group_commands(cmd);
    }
}

varargs nomask void begin_reading(string arg)
{
    if(!sizeof(NEWS_D->get_groups()))
    {
        printf( //"%s has no newsgroups right now.\n"
                "%s目前没有任何新闻组。\n", mud_name());
        destruct();
        return;
    }
    this_body()->validate_groups();

    if( sizeof( arg ) && arg[0] != '-') 
    {
        modal_push( (: receive_grp_cmd :), (:grp_cmd_prompt :));
        read_group( arg );
        return;
    }
    add_new_groups();

    display_groups_with_new( arg );
}

