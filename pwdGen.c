
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
#ifdef __MINGW32__
#define _TIMEVAL_DEFINED
#endif
#include <time.h>

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
int main(int wbac, char **wbav);
void CloseEveryThing(void);
void OpenEveryThing(void);
void OpenTopaz(void);
void PickIT(USHORT MN);
void GotIT(USHORT MI);
static char *genPWD(UBYTE NumLen, int useLower, int useUpper, int useNumbers, int useSpecial);
static void generateAndDisplayPassword(void);
static UBYTE getPasswordLength(void);
static int gadgetSelected(struct Gadget *gad);
static void appendChars(char *dest, UBYTE *destLen, char *source);
ULONG TotalMemB(void);
void Show_FreeMem(void);

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
	323,166,				       /* window width and height */
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

#define FREE_X 40
#define STATBAR_Y 0
#define MAX_PASSWORD_LENGTH 18
#define DEFAULT_PASSWORD_LENGTH 8

#define gfx_rp Wind->RPort

char TBuf[11];

/* Checks if started from Workbench or CLI */
typedef struct WBStartup *startworkbench;
startworkbench *StartWorkBench;

int wbmain(startworkbench *StartWorkBench)
{
   return(main(0, (char **)StartWorkBench));
}

int main(int wbac, char **wbav)
{
  ULONG  MsgClass; /* Window and Menu Messages */
  USHORT MsgCode;  /* IDCMP Messages */
  APTR	 MsgGad;   /* Gadget Messages */

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

		    if(MsgGad == (APTR)&pw_mainGenerate)
		    {
		       generateAndDisplayPassword();
		    }
		    break;
       }
   }

  return 0;
}


/* Close this and clean up the mess! */
void CloseEveryThing(void)
{
    if (Wind)
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
void OpenEveryThing(void)
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

void OpenTopaz(void)
{
    if(!(OpenDiskFont(&New)))
    {
	printf("Unable to open the font!\n");
	exit(1);
    }
}

void PickIT(USHORT MN)
{
  switch(MENUNUM(MN))
  {
	case myMenu : GotIT(ITEMNUM(MN));
	break;
  }
}

void GotIT(USHORT MI)
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

/* Character sets used to build the password pool. */
static char LowerChars[] = "abcdefghijklmnopqrstuvwxyz";
static char UpperChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char NumberChars[] = "0123456789";
static char SpecialChars[] = "!@#$%^&*";

static int gadgetSelected(struct Gadget *gad)
{
    if(gad == NULL)
	return 0;

    return((gad->Flags & SELECTED) != 0);
}

static UBYTE getPasswordLength(void)
{
    int length;
    struct StringInfo *lengthInfo;
    char normalizedLength[4];

    lengthInfo = (struct StringInfo *)pw_mainLength.SpecialInfo;
    length = atoi((char *)lengthInfo->Buffer);

    if(length < 1)
	length = DEFAULT_PASSWORD_LENGTH;

    if(length > MAX_PASSWORD_LENGTH)
	length = MAX_PASSWORD_LENGTH;

    sprintf(normalizedLength, "%d", length);
    updateStrGad(Wind, &pw_mainLength, (UBYTE *)normalizedLength);

    return((UBYTE)length);
}

static void appendChars(char *dest, UBYTE *destLen, char *source)
{
    UBYTE i;
    UBYTE sourceLen;

    sourceLen = (UBYTE)strlen(source);

    for(i=0;i<sourceLen;i++) {
	dest[*destLen] = source[i];
	(*destLen)++;
    }
}

static void generateAndDisplayPassword(void)
{
    char *password;
    UBYTE length;
    int useLower;
    int useUpper;
    int useNumbers;
    int useSpecial;

    length = getPasswordLength();
    useLower = gadgetSelected(&pw_mainUseLower);
    useUpper = gadgetSelected(&pw_mainUseUpper);
    useNumbers = gadgetSelected(&pw_mainUseNumbers);
    useSpecial = gadgetSelected(&pw_mainUseSpecial);

    password = genPWD(length, useLower, useUpper, useNumbers, useSpecial);
    if(password == NULL) {
	updateStrGad(Wind, &pw_mainPassword, (UBYTE *)"Select type");
	return;
    }

    updateStrGad(Wind, &pw_mainPassword, (UBYTE *)password);
}

/* routine to get the random password */
static char *genPWD(UBYTE NumLen, int useLower, int useUpper, int useNumbers, int useSpecial)
{
    UBYTE i;
    UBYTE j;
    UBYTE NumberLength;
    char RandomPinCode[96];
    static char password[MAX_PASSWORD_LENGTH + 1];
    static int seeded = 0;

    if(NumLen == 0 || NumLen > MAX_PASSWORD_LENGTH)
	return NULL;

    NumberLength = 0;
    memset(RandomPinCode, 0, sizeof(RandomPinCode));

    if(useLower)
	appendChars(RandomPinCode, &NumberLength, LowerChars);

    if(useUpper)
	appendChars(RandomPinCode, &NumberLength, UpperChars);

    if(useNumbers)
	appendChars(RandomPinCode, &NumberLength, NumberChars);

    if(useSpecial)
	appendChars(RandomPinCode, &NumberLength, SpecialChars);

    if(NumberLength == 0)
	return NULL;

    if(!seeded) {
	clock_t clk = clock();
	unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)clk;

	srand(seed);
	seeded = 1;
    }

    memset(password, 0, sizeof(password));

    /* The number of password characters that you supply (e.g. NumLen) */
    for(i=0;i<NumLen;i++) {
	  j = rand()%NumberLength;
       password[i] = RandomPinCode[j];
    }

    password[NumLen] = '\0';
    return password;
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
    struct StringInfo *stringInfo;

    if(win == NULL || gad == NULL || newstr == NULL || gad->SpecialInfo == NULL)
	return;

    stringInfo = (struct StringInfo *)gad->SpecialInfo;

    /* first, remove the gadget from the window.  this must be done before
    ** modifying any part of the gadget!!!
    */
    RemoveGList(win,gad,1);

    /* For fun, change the value in the buffer, as well as the cursor and
    ** initial display position.
    */
    strncpy(stringInfo->Buffer, (char *)newstr, stringInfo->MaxChars - 1);
    stringInfo->Buffer[stringInfo->MaxChars - 1] = '\0';
    stringInfo->BufferPos = 0;
    stringInfo->DispPos = 0;

    /* Add the gadget back, placing it at the end of the list (~0)
    ** and refresh its imagery.
    */
    AddGList(win,gad,~0,1,NULL);
    RefreshGList(gad,win,NULL,1);

    /* Activate the string gadget */
    ActivateGadget(gad,win,NULL);
}

ULONG TotalMemB(void)
{
   ULONG tmem;
   tmem = AvailMem((ULONG)MEMF_PUBLIC);
   return tmem;
}

void Show_FreeMem(void)
{
   sprintf(TBuf, "%lu", TotalMemB());
   Text(gfx_rp, "          "  , 10);
   Text(gfx_rp, TBuf	      , strlen(TBuf));
}
