#ifndef PWDMAIN_H
#define PWMAIN_H

/*
 *  pwdMain.h
 *
 *  © Copyright 2016, WKS Software (KCM Hosting), All Rights Reserved.
 *  http://www.kcmhosting.com
 *
 */

#include "pwdColors.h"
#include "pwdGen_rev.h"

/* Pallete */
USHORT MAP[16] = {
  0xbbb, 0x000, 0xfff, 0xf60, 0x090, 0x4f1, 0x00f, 0x2cd,
  0xc00, 0xa0f, 0x950, 0xfca, 0xfe0, 0xf0c, 0x888, 0x444
#define mapCount 16
};

struct TextAttr New = {
   (STRPTR)"topaz.font",16,FS_NORMAL,FPF_DISKFONT
};

static UBYTE UNDOBUFFER[20];

static SHORT pw_mainBorderVectors1[] = {
        0,0,
        94,0,
        94,12,
        0,12,
        0,0
};

static struct Border pw_mainBorder1 = {
        -1,-1,  /* XY origin relative to container TopLeft */
        Black,0,JAM2,   /* front pen, back pen and drawmode */
        5,      /* number of XY vectors */
        pw_mainBorderVectors1,  /* pointer to XY vectors */
        NULL    /* next border in list */
};

static struct IntuiText pw_mainIText1 = {
        DKGreen,0,JAM2, /* front and back text pens, drawmode and fill byte */
        6,2,    /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Generate 8",   /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct Gadget pw_mainGenerate8 = {
        NULL,   /* next gadget */
        116,92, /* origin XY of hit box relative to window TopLeft */
        93,11,  /* hit box width and height */
        NULL,   /* gadget flags */
        RELVERIFY,      /* activation flags */
        BOOLGADGET,     /* gadget type flags */
        (APTR)&pw_mainBorder1,  /* gadget border or image to be rendered */
        NULL,   /* alternate imagery for selection */
        &pw_mainIText1, /* first IntuiText structure */
        NULL,   /* gadget mutual-exclude long word */
        NULL,   /* SpecialInfo structure */
        NULL,  /* user-definable data */
        NULL    /* pointer to user-definable data */
};

static SHORT pw_mainBorderVectors2[] = {
        0,0,
        94,0,
        94,12,
        0,12,
        0,0
};
static struct Border pw_mainBorder2 = {
        -1,-1,  /* XY origin relative to container TopLeft */
        Black,0,JAM2,   /* front pen, back pen and drawmode */
        5,      /* number of XY vectors */
        pw_mainBorderVectors2,  /* pointer to XY vectors */
        NULL    /* next border in list */
};

static struct IntuiText pw_mainIText2 = {
        DKGreen,0,JAM2, /* front and back text pens, drawmode and fill byte */
        6,2,    /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Generate 6",   /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct Gadget pw_mainGenerate6 = {
        &pw_mainGenerate8,      /* next gadget */
        116,78, /* origin XY of hit box relative to window TopLeft */
        93,11,  /* hit box width and height */
        NULL,   /* gadget flags */
        RELVERIFY,      /* activation flags */
        BOOLGADGET,     /* gadget type flags */
        (APTR)&pw_mainBorder2,  /* gadget border or image to be rendered */
        NULL,   /* alternate imagery for selection */
        &pw_mainIText2, /* first IntuiText structure */
        NULL,   /* gadget mutual-exclude long word */
        NULL,   /* SpecialInfo structure */
        NULL,  /* user-definable data */
        NULL    /* pointer to user-definable data */
};

static SHORT pw_mainBorderVectors3[] = {
        0,0,
        67,0,
        67,11,
        0,11,
        0,0
};
static struct Border pw_mainBorder3 = {
        -1,-1,  /* XY origin relative to container TopLeft */
        Black,0,JAM1,   /* front pen, back pen and drawmode */
        5,      /* number of XY vectors */
        pw_mainBorderVectors3,  /* pointer to XY vectors */
        NULL    /* next border in list */
};

static struct IntuiText pw_mainIText3 = {
        DKGreen,0,JAM2, /* front and back text pens, drawmode and fill byte */
        15,1,   /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Quit", /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct Gadget pw_mainQuit = {
        &pw_mainGenerate6,      /* next gadget */
        244,106,        /* origin XY of hit box relative to window TopLeft */
        66,10,  /* hit box width and height */
        NULL,   /* gadget flags */
        RELVERIFY,      /* activation flags */
        BOOLGADGET,     /* gadget type flags */
        (APTR)&pw_mainBorder3,  /* gadget border or image to be rendered */
        NULL,   /* alternate imagery for selection */
        &pw_mainIText3, /* first IntuiText structure */
        NULL,   /* gadget mutual-exclude long word */
        NULL,   /* SpecialInfo structure */
        NULL,       /* user-definable data */
        NULL    /* pointer to user-definable data */
};

static SHORT pw_mainBorderVectors4[] = {
        0,0,
        67,0,
        67,11,
        0,11,
        0,0
};
static struct Border pw_mainBorder4 = {
        -1,-1,  /* XY origin relative to container TopLeft */
        Black,0,JAM1,   /* front pen, back pen and drawmode */
        5,      /* number of XY vectors */
        pw_mainBorderVectors4,  /* pointer to XY vectors */
        NULL    /* next border in list */
};

static struct IntuiText pw_mainIText4 = {
        DKGreen,0,JAM2, /* front and back text pens, drawmode and fill byte */
        15,1,   /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "About",        /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct Gadget pw_mainAbout = {
        &pw_mainQuit,   /* next gadget */
        18,106, /* origin XY of hit box relative to window TopLeft */
        66,10,  /* hit box width and height */
        NULL,   /* gadget flags */
        RELVERIFY,      /* activation flags */
        BOOLGADGET,     /* gadget type flags */
        (APTR)&pw_mainBorder4,  /* gadget border or image to be rendered */
        NULL,   /* alternate imagery for selection */
        &pw_mainIText4, /* first IntuiText structure */
        NULL,   /* gadget mutual-exclude long word */
        NULL,   /* SpecialInfo structure */
        NULL,      /* user-definable data */
        NULL    /* pointer to user-definable data */
};

static SHORT pw_mainBorderVectors5[] = {
        0,0,
        94,0,
        94,12,
        0,12,
        0,0
};
static struct Border pw_mainBorder5 = {
        -1,-1,  /* XY origin relative to container TopLeft */
        Black,0,JAM2,   /* front pen, back pen and drawmode */
        5,      /* number of XY vectors */
        pw_mainBorderVectors5,  /* pointer to XY vectors */
        NULL    /* next border in list */
};

static struct IntuiText pw_mainIText5 = {
        DKGreen,0,JAM2, /* front and back text pens, drawmode and fill byte */
        6,2,    /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Generate 4",   /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct Gadget pw_mainGenerate4 = {
        &pw_mainAbout,  /* next gadget */
        116,64, /* origin XY of hit box relative to window TopLeft */
        93,11,  /* hit box width and height */
        NULL,   /* gadget flags */
        RELVERIFY,      /* activation flags */
        BOOLGADGET,     /* gadget type flags */
        (APTR)&pw_mainBorder5,  /* gadget border or image to be rendered */
        NULL,   /* alternate imagery for selection */
        &pw_mainIText5, /* first IntuiText structure */
        NULL,   /* gadget mutual-exclude long word */
        NULL,   /* SpecialInfo structure */
        NULL,  /* user-definable data */
        NULL    /* pointer to user-definable data */
};

static UBYTE pw_SIBuff[20];

static struct StringInfo pw_mainpw_mainPasswordSInfo = {
        pw_SIBuff,   /* buffer where text will be edited */
        UNDOBUFFER,  /* optional undo buffer */
        0,      /* character position in buffer */
        20,     /* maximum number of characters to allow */
        0,      /* first displayed character buffer position */
        0,0,0,0,0,      /* Intuition initialized and maintained variables */
        0,      /* Rastport of gadget */
        0,      /* initial value for integer gadgets */
        NULL    /* alternate keymap (fill in if you set the flag) */
};

static SHORT pw_mainBorderVectors6[] = {
        0,0,
        183,0,
        183,9,
        0,9,
        0,0
};
static struct Border pw_mainBorder6 = {
        -1,-1,  /* XY origin relative to container TopLeft */
        Black,0,JAM2,   /* front pen, back pen and drawmode */
        5,      /* number of XY vectors */
        pw_mainBorderVectors6,  /* pointer to XY vectors */
        NULL    /* next border in list */
};

static struct Gadget pw_mainPassword = {
        &pw_mainGenerate4,      /* next gadget */
        73,53,  /* origin XY of hit box relative to window TopLeft */
        182,8,  /* hit box width and height */
        NULL,   /* gadget flags */
        RELVERIFY+STRINGCENTER, /* activation flags */
        STRGADGET,      /* gadget type flags */
        (APTR)&pw_mainBorder6,  /* gadget border or image to be rendered */
        NULL,   /* alternate imagery for selection */
        NULL,   /* first IntuiText structure */
        NULL,   /* gadget mutual-exclude long word */
        (APTR)&pw_mainpw_mainPasswordSInfo,     /* SpecialInfo structure */
        NULL,   /* user-definable data */
        NULL    /* pointer to user-definable data */
};

#define pw_mainGadgetList1 pw_mainPassword

static struct IntuiText pw_mainIText6 = {
        DKGreen,White,JAM2,     /* front and back text pens, drawmode and fill byte */
        0,0,    /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Quit", /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct MenuItem pw_mainMenuItem3 = {
        NULL,   /* next MenuItem structure */
        0,16,   /* XY of Item hitbox relative to TopLeft of parent hitbox */
        104,8,  /* hit box width and height */
        ITEMTEXT+COMMSEQ+ITEMENABLED+HIGHCOMP,  /* Item flags */
        0,      /* each bit mutually-excludes a same-level Item */
        (APTR)&pw_mainIText6,   /* Item render  (IntuiText or Image or NULL) */
        NULL,   /* Select render */
        'Q',    /* alternate command-key */
        NULL,   /* SubItem list */
        MENUNULL        /* filled in by Intuition for drag selections */
};

static struct IntuiText pw_mainIText11 = {
        DKGreen,White,JAM2,     /* front and back text pens, drawmode and fill byte */
        0,0,    /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "About",        /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct MenuItem pw_mainMenuItem1 = {
        &pw_mainMenuItem3,      /* next MenuItem structure */
        0,0,    /* XY of Item hitbox relative to TopLeft of parent hitbox */
        104,8,  /* hit box width and height */
        ITEMTEXT+COMMSEQ+ITEMENABLED+HIGHCOMP,  /* Item flags */
        0,      /* each bit mutually-excludes a same-level Item */
        (APTR)&pw_mainIText11,  /* Item render  (IntuiText or Image or NULL) */
        NULL,   /* Select render */
        'A',    /* alternate command-key */
        NULL,   /* SubItem list */
        MENUNULL        /* filled in by Intuition for drag selections */
};

static struct Menu pw_mainMenu1 = {
        NULL,   /* next Menu structure */
        0,0,    /* XY origin of Menu hit box relative to screen TopLeft */
        63,0,   /* Menu hit box width and height */
        MENUENABLED,    /* Menu flags */
        "Project",      /* text of Menu name */
        &pw_mainMenuItem1       /* MenuItem linked list pointer */
};

#define pw_mainMenuList1 pw_mainMenu1

static struct IntuiText pw_mainIText14 = {
        Lavender,0,JAM2, /* front and back text pens, drawmode and fill byte */
        122,42, /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Password:",    /* pointer to text */
        NULL    /* next IntuiText structure */
};

static struct IntuiText pw_mainIText13 = {
        DKGreen,0,JAM2, /* front and back text pens, drawmode and fill byte */
        47,28,  /* XY origin relative to container TopLeft */
        NULL,   /* font pointer or NULL for default */
        "Copyright 2016, WKS Software", /* pointer to text */
        &pw_mainIText14 /* next IntuiText structure */
};

static struct IntuiText pw_mainIText12 = {
        DKGreen,0,JAM2,    /* front and back text pens, drawmode and fill byte */
        59,17,             /* XY origin relative to container TopLeft */
        NULL,              /* font pointer or NULL for default */
        PRGNAME" "VERSREV, /* pointer to text */
        &pw_mainIText13    /* next IntuiText structure */
};

#define pw_mainIntuiTextList1 pw_mainIText12

#endif
