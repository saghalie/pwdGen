#ifndef PWDMAIN_H
#define PWDMAIN_H

/*
 *  pwdMain.h
 *
 *  (c) Copyright 2016, WKS Software (KCM Hosting), All Rights Reserved.
 *  http://www.kcmhosting.com
 *
 */

#include "pwdColors.h"
#include "pwdGen_rev.h"

/* Palette */
#define mapCount 16
USHORT MAP[mapCount] = {
  0xbbb, 0x000, 0xfff, 0xf60, 0x090, 0x4f1, 0x00f, 0x2cd,
  0xc00, 0xa0f, 0x950, 0xfca, 0xfe0, 0xf0c, 0x888, 0x444
};

struct TextAttr New = {
   (STRPTR)"topaz.font",16,FS_NORMAL,FPF_DISKFONT
};

static UBYTE UNDOBUFFER[20];
static UBYTE pw_LengthUndoBuffer[4];

static SHORT pw_mainButtonVectors[] = {
        0,0,
        67,0,
        67,11,
        0,11,
        0,0
};

static struct Border pw_mainSmallButtonBorder = {
        -1,-1,
        Black,0,JAM1,
        5,
        pw_mainButtonVectors,
        NULL
};

static SHORT pw_mainWideButtonVectors[] = {
        0,0,
        94,0,
        94,12,
        0,12,
        0,0
};

static struct Border pw_mainWideButtonBorder = {
        -1,-1,
        Black,0,JAM2,
        5,
        pw_mainWideButtonVectors,
        NULL
};

static SHORT pw_mainToggleVectors[] = {
        0,0,
        68,0,
        68,12,
        0,12,
        0,0
};

static struct Border pw_mainToggleBorder = {
        -1,-1,
        Black,0,JAM2,
        5,
        pw_mainToggleVectors,
        NULL
};

static struct IntuiText pw_mainQuitText = {
        DKGreen,0,JAM2,
        15,1,
        NULL,
        "Quit",
        NULL
};

static struct Gadget pw_mainQuit = {
        NULL,
        244,144,
        66,10,
        NULL,
        RELVERIFY,
        BOOLGADGET,
        (APTR)&pw_mainSmallButtonBorder,
        NULL,
        &pw_mainQuitText,
        NULL,
        NULL,
        NULL,
        NULL
};

static struct IntuiText pw_mainAboutText = {
        DKGreen,0,JAM2,
        15,1,
        NULL,
        "About",
        NULL
};

static struct Gadget pw_mainAbout = {
        &pw_mainQuit,
        18,144,
        66,10,
        NULL,
        RELVERIFY,
        BOOLGADGET,
        (APTR)&pw_mainSmallButtonBorder,
        NULL,
        &pw_mainAboutText,
        NULL,
        NULL,
        NULL,
        NULL
};

static struct IntuiText pw_mainGenerateText = {
        DKGreen,0,JAM2,
        18,2,
        NULL,
        "Generate",
        NULL
};

static struct Gadget pw_mainGenerate = {
        &pw_mainAbout,
        116,122,
        93,11,
        NULL,
        RELVERIFY,
        BOOLGADGET,
        (APTR)&pw_mainWideButtonBorder,
        NULL,
        &pw_mainGenerateText,
        NULL,
        NULL,
        NULL,
        NULL
};

static struct IntuiText pw_mainSpecialText = {
        DKGreen,0,JAM2,
        8,2,
        NULL,
        "Special",
        NULL
};

static struct Gadget pw_mainUseSpecial = {
        &pw_mainGenerate,
        240,90,
        67,11,
        SELECTED,
        RELVERIFY+TOGGLESELECT,
        BOOLGADGET,
        (APTR)&pw_mainToggleBorder,
        NULL,
        &pw_mainSpecialText,
        NULL,
        NULL,
        NULL,
        NULL
};

static struct IntuiText pw_mainNumbersText = {
        DKGreen,0,JAM2,
        6,2,
        NULL,
        "Numbers",
        NULL
};

static struct Gadget pw_mainUseNumbers = {
        &pw_mainUseSpecial,
        166,90,
        67,11,
        SELECTED,
        RELVERIFY+TOGGLESELECT,
        BOOLGADGET,
        (APTR)&pw_mainToggleBorder,
        NULL,
        &pw_mainNumbersText,
        NULL,
        NULL,
        NULL,
        NULL
};

static struct IntuiText pw_mainUpperText = {
        DKGreen,0,JAM2,
        8,2,
        NULL,
        "Upper",
        NULL
};

static struct Gadget pw_mainUseUpper = {
        &pw_mainUseNumbers,
        92,90,
        67,11,
        SELECTED,
        RELVERIFY+TOGGLESELECT,
        BOOLGADGET,
        (APTR)&pw_mainToggleBorder,
        NULL,
        &pw_mainUpperText,
        NULL,
        NULL,
        NULL,
        NULL
};

static struct IntuiText pw_mainLowerText = {
        DKGreen,0,JAM2,
        8,2,
        NULL,
        "Lower",
        NULL
};

static struct Gadget pw_mainUseLower = {
        &pw_mainUseUpper,
        18,90,
        67,11,
        SELECTED,
        RELVERIFY+TOGGLESELECT,
        BOOLGADGET,
        (APTR)&pw_mainToggleBorder,
        NULL,
        &pw_mainLowerText,
        NULL,
        NULL,
        NULL,
        NULL
};

static UBYTE pw_LengthBuff[4] = "8";

static struct StringInfo pw_mainLengthSInfo = {
        pw_LengthBuff,
        pw_LengthUndoBuffer,
        0,
        4,
        0,
        0,0,0,0,0,
        0,
        0,
        NULL
};

static SHORT pw_mainLengthBorderVectors[] = {
        0,0,
        31,0,
        31,10,
        0,10,
        0,0
};

static struct Border pw_mainLengthBorder = {
        -1,-1,
        Black,0,JAM2,
        5,
        pw_mainLengthBorderVectors,
        NULL
};

static struct Gadget pw_mainLength = {
        &pw_mainUseLower,
        98,66,
        30,9,
        NULL,
        RELVERIFY+STRINGCENTER,
        STRGADGET,
        (APTR)&pw_mainLengthBorder,
        NULL,
        NULL,
        NULL,
        (APTR)&pw_mainLengthSInfo,
        NULL,
        NULL
};

static UBYTE pw_SIBuff[20];

static struct StringInfo pw_mainPasswordSInfo = {
        pw_SIBuff,
        UNDOBUFFER,
        0,
        20,
        0,
        0,0,0,0,0,
        0,
        0,
        NULL
};

static SHORT pw_mainPasswordBorderVectors[] = {
        0,0,
        183,0,
        183,9,
        0,9,
        0,0
};

static struct Border pw_mainPasswordBorder = {
        -1,-1,
        Black,0,JAM2,
        5,
        pw_mainPasswordBorderVectors,
        NULL
};

static struct Gadget pw_mainPassword = {
        &pw_mainLength,
        73,48,
        182,8,
        NULL,
        RELVERIFY+STRINGCENTER,
        STRGADGET,
        (APTR)&pw_mainPasswordBorder,
        NULL,
        NULL,
        NULL,
        (APTR)&pw_mainPasswordSInfo,
        NULL,
        NULL
};

#define pw_mainGadgetList1 pw_mainPassword

static struct IntuiText pw_mainMenuQuitText = {
        DKGreen,White,JAM2,
        0,0,
        NULL,
        "Quit",
        NULL
};

static struct MenuItem pw_mainMenuItem3 = {
        NULL,
        0,16,
        104,8,
        ITEMTEXT+COMMSEQ+ITEMENABLED+HIGHCOMP,
        0,
        (APTR)&pw_mainMenuQuitText,
        NULL,
        'Q',
        NULL,
        MENUNULL
};

static struct IntuiText pw_mainMenuAboutText = {
        DKGreen,White,JAM2,
        0,0,
        NULL,
        "About",
        NULL
};

static struct MenuItem pw_mainMenuItem1 = {
        &pw_mainMenuItem3,
        0,0,
        104,8,
        ITEMTEXT+COMMSEQ+ITEMENABLED+HIGHCOMP,
        0,
        (APTR)&pw_mainMenuAboutText,
        NULL,
        'A',
        NULL,
        MENUNULL
};

static struct Menu pw_mainMenu1 = {
        NULL,
        0,0,
        63,0,
        MENUENABLED,
        "Project",
        &pw_mainMenuItem1
};

#define pw_mainMenuList1 pw_mainMenu1

static struct IntuiText pw_mainITextOptions = {
        Lavender,0,JAM2,
        132,80,
        NULL,
        "Character Sets:",
        NULL
};

static struct IntuiText pw_mainITextLength = {
        Lavender,0,JAM2,
        38,68,
        NULL,
        "Length:",
        &pw_mainITextOptions
};

static struct IntuiText pw_mainITextPassword = {
        Lavender,0,JAM2,
        122,38,
        NULL,
        "Password:",
        &pw_mainITextLength
};

static struct IntuiText pw_mainITextCopyright = {
        DKGreen,0,JAM2,
        47,28,
        NULL,
        "Copyright 2016, WKS Software",
        &pw_mainITextPassword
};

static struct IntuiText pw_mainITextTitle = {
        DKGreen,0,JAM2,
        59,17,
        NULL,
        PRGNAME" "VERSREV,
        &pw_mainITextCopyright
};

#define pw_mainIntuiTextList1 pw_mainITextTitle

#endif
