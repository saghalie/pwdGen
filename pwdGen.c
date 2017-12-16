
/*
 *  pwdGen.c
 *
 *  © Copyright 2016, WKS Software (KCM Hosting), All Rights Reserved.
 *  http://www.kcmhosting.com
 *
 */

#include <exec/types.h>
#include <intuition/intuition.h>
#include <workbench/startup.h>
#include <exec/memory.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

#include "pwdGen_rev.h"
#include "pwdColors.h"

/* Requesters */
#include "pwdMain.h"   /* Main window and gadget structures */
#include "pwdQuit.h"   /* Quit requester  */
#include "pwdAbout.h"  /* About Requester */

/* Menus */
#define myMenu	  0
#define MNU_About 0
#define MNU_Quit  1

VOID updateStrGad(struct Window *win, struct Gadget *gad, UBYTE *newstr);
CloseEveryThing();
OpenEveryThing();
OpenTopaz();
PickIT(USHORT MN);
GotIT(USHORT MI);
static char *genPWD( char NumLen );
ULONG TotalMemB();
void Show_FreeMem();

// int genPass( struct Window *win, struct Gadget *gad, int len );


static struct NewScreen MyScreen = {
	0,0,		     /* screen XY origin relative to View */
	640,200,	     /* screen width and height */
	4,		     /* screen depth (number of bitplanes) */
	DKGreen,1,	     /* detail and block pens */
	HIRES,		     /* display modes for this screen */
	CUSTOMSCREEN,	     /* screen type */
	NULL,		     /* pointer to default screen font */
	VSTRING,	     /* screen title */
	NULL,		     /* first in list of custom screen gadgets */
	NULL		     /* pointer to custom BitMap structure */
};

static struct NewWindow pw_mainNewWindowStructure1 = {
	157,31, 				       /* window XY origin relative to TopLeft of screen */
	323,122,				       /* window width and height */
	DKGreen,2,				       /* detail and block pens */
	MENUPICK+GADGETUP+CLOSEWINDOW+VANILLAKEY,      /* IDCMP flags */
	WINDOWDRAG+WINDOWCLOSE+ACTIVATE+NOCAREREFRESH, /* other window flags */
	&pw_mainPassword,			       /* first gadget in gadget list */
	NULL,					       /* custom CHECKMARK imagery */
	"Password Generator",                          /* window title */
	NULL,					       /* custom screen pointer */
	NULL,					       /* custom bitmap */
	5,5,					       /* minimum width and height */
	-1,-1,					       /* maximum width and height */
	CUSTOMSCREEN /* WBENCHSCREEN */ 											   /* destination screen type */
};

struct Window	    *Wind; /* Declare Window	*/
struct Screen	    *Scrn; /* Declare Screen	*/
struct IntuiMessage *msg;  /* Declare Message	*/

/* These I Open With DICE's 'autos.lib' (great stuff)!! */
/* They also close automatically as well */
extern struct Library	    *DiskfontBase;     /* Declare Fonts     */
extern struct IntuitionBase *IntuitionBase;    /* Declare Intuition */
extern struct GfxBase	    *GfxBase;	       /* Declare Graphics  */

#define FREE_X = 40
#define STATBAR_Y = 0

#define gfx_rp Wind->RPort

char TBuf[10];

/* Checks if started from Workbench or CLI */
typedef struct WBStartup *startworkbench;
startworkbench *StartWorkBench;

int wbmain(startworkbench *StartWorkBench)
{
   return(main(0, (char **)StartWorkBench));
}

main(int wbac, char **wbav)
{
  ULONG  MsgClass; /* Window and Menu Messages */
  USHORT MsgCode;  /* IDCMP Messages */
  APTR	 MsgGad;   /* Gadget Messages */

  /* Clear string workaround */
  char clear[];
  char *bclr = "        ";

  /* checking if started from workbench or cli */
  if(wbac == 0)
    StartWorkBench = (startworkbench *)wbav;

  OpenEveryThing();

  FOREVER			      /* Wait for a CloseWindow */
  {				      /* from You The User or a */
    if((msg = (struct IntuiMessage *) /* Menu Choice (of course)*/
       GetMsg(Wind->UserPort))==NULL)
       {
	  Wait(1<<Wind->UserPort->mp_SigBit);
	  continue;
       }

       MsgGad	= msg->IAddress; /* Gadget Messages */
       MsgClass = msg->Class;	 /* Menu and window messages */
       MsgCode	= msg->Code;	 /* Key presses */

       ReplyMsg(msg);

       switch(MsgClass)
       {
	   case MENUPICK :
	       PickIT(MsgCode);
	       break;

	   case CLOSEWINDOW :
	       reqQuit();    /* Close Requester */
	       break;

	   case VANILLAKEY :
	       switch(MsgCode)
	       {
		  case 'd':
		  case 'D':
		  case 'a':
		  case 'A':
		       reqAbout();
		       break;

		  case 'q':
		  case 'Q':
		       reqQuit();
		       break;
	       }
	       break;

	       case GADGETUP :
		    if(MsgGad == (APTR)&pw_mainQuit)
		      reqQuit();

		    if(MsgGad == (APTR)&QuitGadget1) /* YES */
		      CloseEveryThing();

		    if(MsgGad == (APTR)&QuitGadget2) /* NO */
		      continue;

		    if(MsgGad == (APTR)&pw_mainAbout)
		      reqAbout();

		    if(MsgGad == (APTR)&AboutGadget1) /* OK */
		      continue;

		    if(MsgGad == (APTR)&pw_mainGenerate4)
		    {
		       char *buf4;
		       char dest4[];

		       buf4 = genPWD(4);

		       strncpy(clear,bclr,8);
		       strncpy(dest4,buf4,4);

		       updateStrGad(Wind, &pw_mainPassword, clear);
		       updateStrGad(Wind, &pw_mainPassword, dest4);
		    } else
		    if(MsgGad == (APTR)&pw_mainGenerate6)
		    {
		       char *buf6;
		       char dest6[];

		       buf6 = genPWD(6);

		       strncpy(clear,bclr,8);
		       strncpy(dest6,buf6,6);

		       updateStrGad(Wind, &pw_mainPassword, clear);
		       updateStrGad(Wind, &pw_mainPassword, dest6);
		    } else
		    if(MsgGad == (APTR)&pw_mainGenerate8)
		    {
		       char *buf8;
		       char dest8[];

		       buf8 = genPWD(8);

		       strncpy(clear,bclr,8);
		       strncpy(dest8,buf8,8);

		       updateStrGad(Wind, &pw_mainPassword, clear);
		       updateStrGad(Wind, &pw_mainPassword, dest8);
		    }
		    break;
       }
   }
}

/* Routine to get the password in the string gadget. */
/* Not working - not sure why though. */

/*
int genPass( struct Window *win, struct Gadget *gad, int len )
{
    char *buf;
    char dest[];

    char clear[];
    char *bclr = "        ";

    buf = genPWD(len);

    strncpy(clear,bclr,8);
    strncpy(dest,buf,len);

    updateStrGad(win,gad,clear);
    updateStrGad(win,gad,dest);
}
*/

/* Close this and clean up the mess! */
CloseEveryThing()
{
    ClearMenuStrip(Wind);

    if (Wind) {
       CloseWindow(Wind);
       Wind = NULL;
    }

    if (Scrn) {
       CloseScreen(Scrn);
       Scrn = NULL;
    }
    exit(0);
}

/* Start the program running */
OpenEveryThing()
{
  if(!(Scrn = (struct Screen *)
       OpenScreen(&MyScreen)))
       {
	  printf("ERROR: The Screen Won't Open!\n");
	  exit(1);
       }

       /* Assign the screen to the window and load up the palette. */
       pw_mainNewWindowStructure1.Screen = Scrn;
       LoadRGB4(&Scrn->ViewPort,MAP,mapCount);

  if(!(Wind = (struct Window *) 		     /* Open the Window     */
       OpenWindow(&pw_mainNewWindowStructure1)))     /* exit if not opened  */
       {					     /* and leave a message */
	  printf("ERROR: The Window Won't Open!\n");
	  exit(1);
       }

   SetMenuStrip(Wind,&pw_mainMenuList1);	       /* Ready The Menus!	  */
   PrintIText(Wind->RPort,&pw_mainIntuiTextList1,0,0); /* Print The Title Text	 */
}

OpenTopaz()
{
    if(!(OpenDiskFont(&New)))
    {
	printf("Unable to open the font!\n");
	exit(1);
    }
}

PickIT(USHORT MN)
{
  switch(MENUNUM(MN))
  {
	case myMenu : GotIT(ITEMNUM(MN));
	break;
  }
}

GotIT(USHORT MI)
{
  switch(MI)
  {
    case MNU_About :
	reqAbout();
	break;

    case MNU_Quit :
	reqQuit();
	break;
  }
}

/* Adding the alphabet, numbers and characters to the buffer. */
static char RandomPinCode[] = "0123456789" \
			      "abcdefghijklmnopqrstuvwxyz" \
			      "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
			      "!@#$%^&*" \
			      "9876543210";

/* routine to get the random password */
static char *genPWD( char NumLen )
{
    char i = 0, j = 0, *p = NULL;
    char NumberLength = strlen( RandomPinCode );

    clock_t clk = clock();
    time_t tm = clock();

    unsigned int seed = time(&tm)^clk*16;

    p = (char *)malloc( 512 );

    if(p == NULL)
	return NULL;

    srand( seed * time(&tm)^clk*15 );

    memset( (char *)p, NumLen, 0 );

    /* The number of password characters that you supply (e.g. NumLen) */
    for(i=0;i<NumLen;i++) {
	  j = rand()%NumberLength;
       p[i] = RandomPinCode[j];
    }

    return p;
    free(p);
}

/*
** Routine to update the value in the string gadget's buffer, then
** activate the gadget.
**
** This is the routine that was released by Commodore.
**
*/
VOID updateStrGad(struct Window *win, struct Gadget *gad, UBYTE *newstr)
{
    /* first, remove the gadget from the window.  this must be done before
    ** modifying any part of the gadget!!!
    */
    RemoveGList(win,gad,1);

    /* For fun, change the value in the buffer, as well as the cursor and
    ** initial display position.
    */
    strcpy(((struct StringInfo *)(gad->SpecialInfo))->Buffer, newstr);
    ((struct StringInfo *)(gad->SpecialInfo))->BufferPos = 0;
    ((struct StringInfo *)(gad->SpecialInfo))->DispPos	 = 0;

    /* Add the gadget back, placing it at the end of the list (~0)
    ** and refresh its imagery.
    */
    AddGList(win,gad,~0,1,NULL);
    RefreshGList(gad,win,NULL,1);

    /* Activate the string gadget */
    ActivateGadget(gad,win,NULL);
}

ULONG TotalMemB()
{
   ULONG tmem;
   tmem = AvailMem((ULONG)MEMF_PUBLIC);
   return;
}

void Show_FreeMem()
{
   ltoa(TotalMemB(), TBuf , 0);
   Text(gfx_rp, "          "  , 10);
   Text(gfx_rp, TBuf	      , strlen(TBuf));
}


