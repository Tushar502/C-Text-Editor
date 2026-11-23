#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<unistd.h>

int savefile(char *filename,char **text,int total_lines);
void openfile(char *filename,char ***text,int *total_lines,int *rows,int cols);
int main(int argc,char *argv[])
{
char **text;
int x=0,y=0,ch,position,total_lines=1;
int screen_rows,screen_cols,top_line=0;


if(argc!=4)
{
  printf("please give complete argumn=emts");
  return 1;
}

char *filename=argv[1];
char new_filename[256];
char saved_filename[256];
int rows=atoi(argv[2]);
int cols=atoi(argv[3]);
text=malloc(rows*sizeof(char*));
for(int i=0;i<rows;i++)
{
  text[i]=malloc(cols*sizeof(char));
  text[i][0]='\0';
}
initscr();
getmaxyx(stdscr,screen_rows,screen_cols);
keypad(stdscr,TRUE);
noecho();
cbreak();

while(1)
{
//curs_set(0);
erase();
for(int i=0;i<screen_rows-1;i++)
{
  int file_line=top_line+i;
  if(file_line<total_lines)
  {
    mvprintw(i,0,"%s",text[file_line]);
  }
}

position=0;
for(int i=0;i<y;i++)
{
  position=position+strlen(text[i])+1;
}
position=position+x;


attron(A_BOLD);
mvprintw(screen_rows-1,52,"Rows:%d  Column:%d Position:%d Total_line=%d",y+1,x+1,position,total_lines);
attroff(A_BOLD);
int screen_y=y-top_line;
move(screen_y,x);
refresh();
//curs_set(1);

ch=getch();
if(ch==27)
{
  break;
}
else if(ch=='\n')
{
   if(total_lines>=rows)
   {
     int old_rows=rows;
     int new_rows=rows*2;

     char **temp;
     temp=realloc(text,new_rows*sizeof(char*));
     if(temp==NULL)
     {
        continue;
     }
       text=temp;
       rows=new_rows;

   for(int i=old_rows;i<rows;i++)
   {
     text[i]=malloc(cols*sizeof(char));
     if(text[i]==NULL)
     {
       continue;
     }
     text[i][0]='\0';
   }
}
   for(int i=total_lines;i>y+1;i--)
{
  strcpy(text[i],text[i-1]);
}
strcpy(text[y+1],&text[y][x]);
text[y][x]='\0';
y++;
x=0;
total_lines++;
if(y-top_line>=screen_rows-1)
{
	top_line++;
}
}
else if(ch==KEY_BACKSPACE || ch==127)
{
  if(x>0)
  {
     x--;
     int len=strlen(text[y]);
    for(int i=x;i<len;i++)
    {
      text[y][i]=text[y][i+1];
    }
  }
  else if(y>0)
  {
    int prev_len=strlen(text[y-1]);

   int len1=strlen(text[y-1]);
   int len2=strlen(text[y]);
     if(len1+len2+1<=cols)
     {
       strcat(text[y-1],text[y]);

        for(int i=y;i<total_lines-1;i++)
        {
          strcpy(text[i],text[i+1]);
        }
        text[total_lines-1][0]='\0';
        y--;
        x=prev_len;
        total_lines--;

	if(y<top_line)
	{
		top_line=y;
	}
	int visible_rows=screen_rows-1;

	if(total_lines<=visible_rows)
	{
		top_line=0;
	}
	else if(top_line>total_lines-visible_rows)
	{
		top_line=total_lines-visible_rows;
	}
    }
 }
}
else if(ch==KEY_LEFT)
{
  if(x>0)
  {
    x--;
  }
  else if(y>0)
  {
    y--;
  x=strlen(text[y]);
  }
}
else if(ch==KEY_RIGHT)
{
    if(x<strlen(text[y]))
    {
      x++;
   }
  else if(y<total_lines-1)
   {
     y++;
     x=0;

     if(y-top_line>=screen_rows-1)
     {
		top_line++;
     }

  }
}
else if(ch==KEY_UP)
{
  if(y>0)
 {
    y--;
    if(y<top_line)
    {
      top_line--;
    }
    if(x>strlen(text[y]))
    {
      x=strlen(text[y]);
    }
 }
}
else if(ch==KEY_DOWN)
{
  if(y<total_lines-1)
  {
    y++;
    if(y-top_line>=screen_rows-1)
    {
      top_line++;
    }
    if(x>strlen(text[y]))
    {
      x=strlen(text[y]);
    }
  }
}
else if(ch>=32 && ch<=126)
{
   int len=strlen(text[y]);
   for(int i=len;i>=x;i--)
   {
     text[y][i+1]=text[y][i];
   }
   text[y][x]=ch;
  x++;
}
else if(ch==KEY_DC)
{
  int len=strlen(text[y]);
  if(x<len)
  {
    for(int i=x;i<len;i++)
    {
      text[y][i]=text[y][i+1];
    }
 }
}
else if(ch==KEY_HOME)
{
  x=0;
}
else if(ch==KEY_END)
{
  x=strlen(text[y]);
}
else if(ch==KEY_F(2))
{
  savefile(filename,text,total_lines);
}
else if(ch==KEY_F(4))
{
	echo();
	mvprintw(screen_rows-1,0,"Save As:");
	clrtoeol();
	getnstr(new_filename,sizeof(new_filename)-1);
	noecho();

	if(new_filename[0]!='\0')
	{
		if(access(new_filename,F_OK)==0)
		{
			mvprintw(screen_rows-1,0,"File already exixts Want to overwrite(Y/N)?");
			clrtoeol();
			refresh();
			int confirm=getch();

			if(confirm!='y' && confirm!='Y')
			{
				continue;
			}
		}

		if(savefile(new_filename,text,total_lines))
		{
			strcpy(saved_filename,new_filename);
			filename=saved_filename;
		}
	}
}
else if(ch==KEY_F(3))
{
  openfile(filename,&text,&total_lines,&rows,cols);
 // printf("filename = %s\n", filename);
  if(y>=total_lines)
     y=total_lines-1;
     x=0;
}
}
endwin();
return 0;
}
int savefile(char *filename,char **text,int total_lines)
{
   beep();
   FILE *fp;
   fp=fopen(filename,"w");
   if(fp==NULL)
   {
    printf("file does not exits");
    return 0;
  }
  for(int i=0;i<total_lines;i++)
  {
    fprintf(fp,"%s\n",text[i]);
  }
  fclose(fp);
  return 1;
}
void openfile(char *filename,char ***text,int *total_lines,int *rows,int cols)
{
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
	    mvprintw(0,0,"file does not exists");
	    refresh();
	    getch();
	    return ;
	}
	fseek(fp,0,SEEK_END);
	long size=ftell(fp);
	rewind(fp);

    char *data;
    data=malloc(size+1);

    if(data==NULL)
    {
       fclose(fp);
       return ;
    }

    fread(data,1,size,fp);
    data[size]='\0';
    fclose(fp);

    *text=malloc((size+1)*sizeof(char*));
    if(*text==NULL)
    {
        free(data);
        return ;
    }

    (*text)[0]=&data[0];
    int line=1;

    for(int i=0;i<size;i++)
    {
       if(data[i]=='\n')
       {
          data[i]='\0';

          if(i+1<size)
          {
             (*text)[line]=&data[i+1];
             line++;
          }
      }

  }
  *total_lines=line;

 /*for(int i=0;i<*total_lines;i++)
  {
     mvprintw(i,0,"%s",text[i]);
  }
  refresh();
  getch();*/
}


