#include<FL/Fl_Widget.H>
#include<FL/Fl_Wizard.H>
#include<FL/Fl_Group.H>
#include<FL/fl_ask.H>
#include<FL/Fl_Button.H>
#include<Fl/Fl_Box.H>
#include<FL/Fl_Round_Button.H>
#include<FL/Fl_Window.H>
#include<FL/Fl.H>

Fl_Window *win1 = 0;
Fl_Window *win2 = 0;
char *playing;

class button {
 public:
 int count;
 Fl_Button *bArr[10];
 char *player1;
 char *player2;
 int gameWon();
 int noSpace();
 void setLabel(int);
 void construct(int x,int y);
 friend void btnCallBack(Fl_Widget* w,void* v);
 friend void nextpage();
 button(){count=0;player1=(char*)"X";player2=(char*)"O";}
};

void btnCallBack(Fl_Widget* w,void* v)
{
  button *B = (button*)v;
  if(w->label()!="X" && w->label() != "O")
      { B->count++;w->label(playing); w->labelsize(30); }
  else return;
  if(B->gameWon())
  {
    fl_message("'%s' Won the game..Congrats..!!",playing);
    for(int i=1;i<10;i++)B->bArr[i]->label("");B->count=0;
    win1->show();
    win2->hide();
    return;
  }
  else if(B->count ==9)
  {    fl_message("The Game is a tie");
       for(int i=1;i<10;i++)B->bArr[i]->label("");
       B->count=0;win1->show(); win2->hide(); return;
  }
  else
  {
       if(playing == B->player1)playing=B->player2;
       else playing=B->player1;
  }
}

int button::gameWon()
{
  char *ip = playing;
  return( (bArr[1]->label() == ip) && (bArr[4]->label() == ip) && (bArr[7]->label() == ip) ||
	  (bArr[1]->label() == ip) && (bArr[5]->label() == ip) && (bArr[9]->label() == ip) ||
	  (bArr[1]->label() == ip) && (bArr[2]->label() == ip) && (bArr[3]->label() == ip) ||
	  (bArr[4]->label() == ip) && (bArr[5]->label() == ip) && (bArr[6]->label() == ip)  ||
	  (bArr[7]->label() == ip) && (bArr[8]->label() == ip) && (bArr[9]->label() == ip)  ||
	  (bArr[7]->label() == ip) && (bArr[5]->label() == ip) && (bArr[3]->label() == ip)  ||
	  (bArr[2]->label() == ip) && (bArr[5]->label() == ip) && (bArr[8]->label() == ip)  ||
	  (bArr[3]->label() == ip) && (bArr[6]->label() == ip) && (bArr[9]->label() == ip)
        );
}

int button::noSpace()
{
  for(int i=1;i<10;i++){
   if(bArr[i]->label() != player1 || bArr[i]->label() != player2)
	return 0;
   }
   return 1;
}
void button::construct(int x,int y)
{
	int loop=0;
	int X=x;int Y=y;
	int W=90;int H=90;
	for(int i=0;i<3;i++)
        {
		for(int j=0;j<3;j++)
		{
	       	        bArr[++loop]=new Fl_Button(X,Y,W,H,0);
			//setLabel(loop);
			bArr[loop]->callback(btnCallBack,this);
			X+=90;
		}
		X=20;Y+=90;
        }
}

void button::setLabel(int loop)
{
   switch(loop){
   case 1:bArr[1]->label("1");break;
   case 2:bArr[2]->label("2");break;
   case 3:bArr[3]->label("3");break;
   case 4:bArr[4]->label("4");break;
   case 5:bArr[5]->label("5");break;
   case 6:bArr[6]->label("6");break;
   case 7:bArr[7]->label("7");break;
   case 8:bArr[8]->label("8");break;
   case 9:bArr[9]->label("9");break;
  }
}


void nextpage(Fl_Widget* w,void* v)
{
   playing = (char *)w->label();
   win1->hide();win2->show();
}

void close(Fl_Widget* w,void* v)
{
   exit(0);
}

int main()
{
  win1 = new Fl_Window(500,250,310,310,"Select An Option");
  Fl_Box *Dbox = new Fl_Box(60,60,200,60,"Select an option\n to start the game");
  Dbox->labelsize(25);
  Fl_Button *choice1 = new Fl_Button(100,130,100,30,"X");
  Fl_Button *choice2 = new Fl_Button(100,170,100,30,"O");
  Fl_Button *exit = new Fl_Button(70,210,160,60,"Exit");
  exit->labelsize(20);choice1->labelsize(20);choice2->labelsize(20);
  exit->labelfont(FL_ITALIC+FL_HELVETICA);choice1->labelfont(FL_ITALIC);choice2->labelfont(FL_ITALIC);
  exit->callback(close);
  choice1->callback(nextpage);choice2->callback(nextpage);
  win1->end();
  win1->show();

  win2 = new Fl_Window(500,250,310,310,"Play Game");
  button B;
  B.construct(20,20);
  win2->end();
  win2->hide();
  return Fl::run();
  //return 0;
}
