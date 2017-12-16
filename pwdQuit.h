#ifndef PWDQUIT_H
#define PWDQUIT_H

/*
 *  pwdQuit.h
 *
 *  (c)Copyright 2016, WKS Software (KCM Hosting), All Rights Reserved.
 *  http://www.kcmhosting.com
 *
 */

#include <intuition/intuition.h>
#include "pwdColors.h"

#define BTN_ReqYES 0
#define BTN_ReqNO  1

static SHORT QuitBorderVectors[] = {
	0,0,
	50,0,
	50,12,
	0,12,
	0,0
};

static struct Border QuitBorder = {
	-1,-1,		    /* XY origin relative to container TopLeft */
	Yellow,Black,JAM2,  /* front pen, back pen and drawmode */
	5,		    /* number of XY vectors */
	QuitBorderVectors,  /* pointer to XY vectors */
	NULL		    /* next border in list */
};

static struct IntuiText QuitIText1 = {
	Green,Black,JAM2, /* front and back text pens, drawmode and fill byte */
	18,2,		  /* XY origin relative to container TopLeft */
	NULL,		  /* font pointer or NULL for default */
	"NO",             /* pointer to text */
	NULL		  /* next IntuiText structure */
};

static struct Gadget QuitGadget2 = {
	NULL,	/* next gadget */
	98,61,	/* origin XY of hit box relative to window TopLeft */
	49,10,	/* hit box width and height */
	NULL,	/* gadget flags */
	RELVERIFY+ENDGADGET,	  /* activation flags */
	BOOLGADGET+REQGADGET,	/* gadget type flags */
	(APTR)&QuitBorder,    /* gadget border or image to be rendered */
	NULL,	/* alternate imagery for selection */
	&QuitIText1,   /* first IntuiText structure */
	NULL,	/* gadget mutual-exclude long word */
	NULL,	/* SpecialInfo structure */
	NULL,	/* user-definable data */
	NULL	/* pointer to user-definable data */
};

static struct Border QuitBorder2 = {
	-1,-1,		    /* XY origin relative to container TopLeft */
	Yellow,Black,JAM2,  /* front pen, back pen and drawmode */
	5,		    /* number of XY vectors */
	QuitBorderVectors,  /* pointer to XY vectors */
	NULL		    /* next border in list */
};

static struct IntuiText QuitIText2 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	12,2,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"YES",  /* pointer to text */
	NULL	/* next IntuiText structure */
};

static struct Gadget QuitGadget1 = {
	&QuitGadget2,  /* next gadget */
	15,61,	/* origin XY of hit box relative to window TopLeft */
	49,10,	/* hit box width and height */
	NULL,	/* gadget flags */
	RELVERIFY+GADGIMMEDIATE,      /* activation flags */
	BOOLGADGET+REQGADGET,	/* gadget type flags */
	(APTR)&QuitBorder2,    /* gadget border or image to be rendered */
	NULL,	/* alternate imagery for selection */
	&QuitIText2,   /* first IntuiText structure */
	NULL,	/* gadget mutual-exclude long word */
	NULL,	/* SpecialInfo structure */
	BTN_ReqYES,	/* user-definable data */
	NULL	/* pointer to user-definable data */
};

#define QuitGadgetList1 QuitGadget1

static struct IntuiText QuitIText7 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	45,46,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"to quit?",     /* pointer to text */
	NULL	/* next IntuiText structure */
};

static struct IntuiText QuitIText6 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	44,36,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"you want",     /* pointer to text */
	&QuitIText7    /* next IntuiText structure */
};

static struct IntuiText QuitIText5 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	26,26,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"Are you sure", /* pointer to text */
	&QuitIText6    /* next IntuiText structure */
};

static struct IntuiText QuitIText4 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	8,17,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"******************",   /* pointer to text */
	&QuitIText5    /* next IntuiText structure */
};

static struct IntuiText QuitIText3 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	9,6,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"Password Generator",   /* pointer to text */
	&QuitIText4    /* next IntuiText structure */
};

#define QuitIntuiTextList1 QuitIText3

static struct Requester QuitRequester = {
	NULL,	/* previous requester (filled in by Intuition) */
	90,15, /* requester XY origin relative to TopLeft of window */
	160,80, /* requester width and height */
	0,0,	/* relative to these mouse offsets if POINTREL is set */
	&QuitGadgetList1,      /* gadget list */
	NULL,	/* box's border */
	&QuitIntuiTextList1,   /* requester text */
	NULL,	/* requester flags */
	1,	/* back-plane fill pen */
	NULL,	/* leave these alone */
	NULL,	/* custom bitmap if PREDRAWN is set */
	NULL	/* leave this alone */
};

extern struct Window *Wind;

reqQuit()
{
   Request(&QuitRequester, Wind );
}

#endif
