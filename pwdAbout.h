#ifndef PWDABOUT_H
#define PWDABOUT_H

/*
 * pwdAbout.h
 *
 * © Copyright 2016, WKS Software, All Rights Reserved.
 *
 */

#include <intuition/intuition.h>
#include "pwdColors.h"

static SHORT AboutBorderVectors1[] = {
	0,0,
	86,0,
	86,15,
	0,15,
	0,0
};
static struct Border AboutBorder1 = {
	-1,-1,	/* XY origin relative to container TopLeft */
	Yellow,Black,JAM1,	 /* front pen, back pen and drawmode */
	5,	/* number of XY vectors */
	AboutBorderVectors1,	/* pointer to XY vectors */
	NULL	/* next border in list */
};

static struct IntuiText AboutIText1 = {
	Yellow,Black,JAM2,	 /* front and back text pens, drawmode and fill byte */
	15,3,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"Dismiss",   /* pointer to text */
	NULL	/* next IntuiText structure */
};

static struct Gadget AboutGadget1 = {
	NULL,	/* next gadget */
	37,60,	/* origin XY of hit box relative to window TopLeft */
	85,14,	/* hit box width and height */
	NULL,	/* gadget flags */
	RELVERIFY+ENDGADGET,	/* activation flags */
	BOOLGADGET+REQGADGET,	/* gadget type flags */
	(APTR)&AboutBorder1,	/* gadget border or image to be rendered */
	NULL,	/* alternate imagery for selection */
	&AboutIText1,	/* first IntuiText structure */
	NULL,	/* gadget mutual-exclude long word */
	NULL,	/* SpecialInfo structure */
	BTN_ReqYES,	/* user-definable data */
	NULL	/* pointer to user-definable data */
};

#define AboutGadgetList1 AboutGadget1

static struct IntuiText AboutIText6 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	20,44,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"Copyright 2016",       /* pointer to text */
	NULL	/* next IntuiText structure */
};

static struct IntuiText AboutIText5 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	29,35,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"WKS Software", /* pointer to text */
	&AboutIText6	/* next IntuiText structure */
};

static struct IntuiText AboutIText4 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	39,25,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"Written by",   /* pointer to text */
	&AboutIText5	/* next IntuiText structure */
};

static struct IntuiText AboutIText3 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	8,17,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"******************",   /* pointer to text */
	&AboutIText4	/* next IntuiText structure */
};

static struct IntuiText AboutIText2 = {
	Green,Black,JAM2,	/* front and back text pens, drawmode and fill byte */
	9,6,	/* XY origin relative to container TopLeft */
	NULL,	/* font pointer or NULL for default */
	"Password Generator",   /* pointer to text */
	&AboutIText3	/* next IntuiText structure */
};

#define AboutIntuiTextList1 AboutIText2

static struct Requester AboutRequester = {
	NULL,	/* previous requester (filled in by Intuition) */
	90,15, /* requester XY origin relative to TopLeft of window */
	160,80, /* requester width and height */
	0,0,	/* relative to these mouse offsets if POINTREL is set */
	&AboutGadgetList1,	/* gadget list */
	NULL,	/* box's border */
	&AboutIntuiTextList1,	/* requester text */
	NULL,	/* requester flags */
	1,	/* back-plane fill pen */
	NULL,	/* leave these alone */
	NULL,	/* custom bitmap if PREDRAWN is set */
	NULL	/* leave this alone */
};

extern struct Window *Wind;

reqAbout()
{
   Request(&AboutRequester, Wind );
}

#endif

