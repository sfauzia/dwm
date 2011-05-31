/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Skinny 6";
static const char normbordercolor[] = "#e0e0e0";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#2d9ac9";
static const char selbgcolor[]      = "#ffffff";
static const char selfgcolor[]      = "#222222";
static unsigned int borderpx        = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static unsigned int snap            = 32;       /* snap pixel */
static Bool showbar                 = True;     /* False means no bar */
static Bool topbar                  = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "TERM", "IMG", "VID", "WEB", "NOTES" };	

static const Rule rules[] = {
	/* class      	instance    title       tags mask     isfloating   monitor */
	{ "Cellwriter", NULL,       NULL,       ~0,           True,        -1 },
	{ "URxvt",      NULL,       NULL,       1 << 0,       False,       -1 },
	{ "sxiv",       NULL,       NULL,       1 << 1,       False,       -1 },
	{ "MPlayer",   	NULL,       NULL,       1 << 2,       True,        -1 },
	{ "surf",       NULL,       NULL,       1 << 3,       False,       -1 },
	{ "Skype",   	NULL,       NULL,       1 << 3,       True,        -1 },
	{ "Lss",   	    NULL,       NULL,       1 << 4,       False,       -1 },
	{ "MuPDF",   	NULL,       NULL,       1 << 4,       False,       -1 },
	{ "Xournal",   	NULL,       NULL,       1 << 4,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55;  /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     	arrange function */
	{ "[]=",        tile },    /* first entry is default */
	{ "><>",        NULL },    /* no layout function means floating behavior */
	{ "[M]",        monocle },
    { "TTT",        bstack },
    { "===",        bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]    = { "dmenu_run", "-fn", "Skinny-6", "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]     = { "urxvt", NULL };
static const char *rotatecmd[]   = { "rotate", NULL };
static const char *upscrollcmd[] = { "xte", "mouseclick 4", NULL };
static const char *dnscrollcmd[] = { "xte", "mouseclick 5", NULL };
static const char *printcmd[]    = { "scrot", NULL };
static const char *notecmd[]     = { "xournal", NULL };
static const char *webcmd[]      = { "surf", "http://home.archlinux.ca", NULL };
static const char *raisevolcmd[] = { "amixer", "-q", "sset", "Master", "5+", NULL };
static const char *lowervolcmd[] = { "amixer", "-q", "sset", "Master", "5-", NULL };
static const char *mutevolcmd[]  = { "amixer", "-q", "sset", "Master", "toggle", NULL };

#include "focusmaster.c"
#include "push.c" 
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        					function        argument */
	{ MODKEY,                       XK_p,      					spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,					spawn,          {.v = termcmd } },
	{ ControlMask,                  XF86XK_RotateWindows,		spawn,          {.v = notecmd } },
	{ 0,                       		XF86XK_RotateWindows,      	spawn,          {.v = rotatecmd } },
	{ 0,                       		XF86XK_ScrollUp, 			spawn,          {.v = upscrollcmd } },
	{ ControlMask,                  XF86XK_ScrollUp, 			spawn,          {.v = webcmd } },
	{ 0,                       		XF86XK_ScrollDown,      	spawn,          {.v = dnscrollcmd } },
	{ ControlMask,                  XF86XK_ScrollDown,			spawn,          {.v = termcmd } },
	{ 0,                       		XK_Print,      				spawn,          {.v = printcmd } },
	{ 0,                 			XF86XK_AudioRaiseVolume,   	spawn,          {.v = raisevolcmd } },
	{ 0,                       		XF86XK_AudioLowerVolume,   	spawn,          {.v = lowervolcmd } },
	{ 0,                 			XF86XK_AudioMute,      		spawn,          {.v = mutevolcmd } },
	{ MODKEY,                       XK_b,      					togglebar,      {0} },
	{ MODKEY,                       XK_j,      					focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      					focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_m,      					focusmaster,    {0} }, 
	{ MODKEY,                       XK_h,      					setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      					setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_j,      					pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      					pushup,         {0} },
/*	{ MODKEY,        				XK_p,      					clientspertag,  {.v="^2"} },
	{ MODKEY,        				XK_q,      					clientspertag,  {.v="^3"} }, */
	{ MODKEY,                       XK_Return, 					zoom,           {0} },
	{ MODKEY,                       XK_Tab,    					view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      					killclient,     {0} },
	{ MODKEY,                       XK_t,      					setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_u,      					setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      					setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      					setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_r,      					setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  					setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  					togglefloating, {0} },
	{ MODKEY,                       XK_0,      					view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      					tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  					focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 					focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  					tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 					tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      					0)
	TAGKEYS(                        XK_2,                      					1)
	TAGKEYS(                        XK_3,                      					2)
	TAGKEYS(                        XK_4,                      					3)
	TAGKEYS(                        XK_5,                      					4)
	{ MODKEY|ShiftMask,             XK_q,      					quit,           {0} },
};

#include "tilemovemouse.c"
/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
/*	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, */
	{ ClkClientWin,         MODKEY,         Button1,        tilemovemouse,  {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

