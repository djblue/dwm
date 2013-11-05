/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>  // for the media keys

/* appearance */
#define NUMCOLORS         5             // need at least 3
static const char colors[NUMCOLORS][ColLast][8] = {
   // border   foreground  background
   { "#cccccc", "#000000", "#cccccc" },  // 0 = normal
   { "#0066ff", "#ffffff", "#0066ff" },  // 1 = selected
   { "#0066ff", "#0066ff", "#ff0000" },  // 2 = urgent/warning
   { "#005566", "#006600", "#00ff00" },  // 3 = hello
   { "#000000", "#ffffff", "#000000" },  // 4 = coolieo
   // add more here
};
static const char font[]            = "inconsolata-medium-14";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]  = { "uxterm", NULL };
static const char *volup[]    = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *voldown[]  = { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *volmute[]  = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *play[]     = { "mpc", "toggle", NULL };
static const char *next[]     = { "mpc", "next",   NULL };
static const char *prev[]     = { "mpc", "prev",   NULL };
static const char *stop[]     = { "mpc", "stop",   NULL };


static Key keys[] = {
    /* modifier           key                       function        argument */
    { MODKEY,             XK_p,                     spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,   XK_Return,                spawn,          {.v = termcmd } },
    { MODKEY,             XK_b,                     togglebar,      {0} },
    { MODKEY,             XK_j,                     focusstack,     {.i = +1 } },
    { MODKEY,             XK_k,                     focusstack,     {.i = -1 } },
    { MODKEY,             XK_i,                     incnmaster,     {.i = +1 } },
    { MODKEY,             XK_d,                     incnmaster,     {.i = -1 } },
    { MODKEY,             XK_h,                     setmfact,       {.f = -0.05} },
    { MODKEY,             XK_l,                     setmfact,       {.f = +0.05} },
    { MODKEY,             XK_Return,                zoom,           {0} },
    { 0,                  XF86XK_AudioRaiseVolume,  spawn,          {.v = volup } },
    { 0,                  XF86XK_AudioLowerVolume,  spawn,          {.v = voldown } },
    { 0,                  XF86XK_AudioMute,         spawn,          {.v = volmute } },
    { 0,                  XF86XK_AudioPlay,         spawn,          {.v = play } },
    { 0,                  XF86XK_AudioNext,         spawn,          {.v = next } },
    { 0,                  XF86XK_AudioPrev,         spawn,          {.v = prev } },
    { 0,                  XF86XK_AudioStop,         spawn,          {.v = stop } },
    { MODKEY,             XK_Tab,                   view,           {0} },
    { MODKEY|ShiftMask,   XK_c,                     killclient,     {0} },
    { MODKEY,             XK_t,                     setlayout,      {.v = &layouts[0]} },
    { MODKEY,             XK_f,                     setlayout,      {.v = &layouts[1]} },
    { MODKEY,             XK_m,                     setlayout,      {.v = &layouts[2]} },
    { MODKEY,             XK_space,                 setlayout,      {0} },
    { MODKEY|ShiftMask,   XK_space,                 togglefloating, {0} },
    { MODKEY,             XK_0,                     view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,   XK_0,                     tag,            {.ui = ~0 } },
    { MODKEY,             XK_comma,                 focusmon,       {.i = -1 } },
    { MODKEY,             XK_period,                focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,   XK_comma,                 tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,   XK_period,                tagmon,         {.i = +1 } },
    TAGKEYS(              XK_1,                     0)
    TAGKEYS(              XK_2,                     1)
    TAGKEYS(              XK_3,                     2)
    TAGKEYS(              XK_4,                     3)
    TAGKEYS(              XK_5,                     4)
    TAGKEYS(              XK_6,                     5)
    TAGKEYS(              XK_7,                     6)
    TAGKEYS(              XK_8,                     7)
    TAGKEYS(              XK_9,                     8)
    { MODKEY|ShiftMask,   XK_q,                     quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

