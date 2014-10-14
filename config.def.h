/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal-*-11-120-72-72-c-60-iso8859-1";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

#define tag_code (1 << 8)
#define tag_build (2 << 8)
#define tag_skype (3 << 8)
#define tag_web (4 << 8)

/* tagging */
static Tag tags[] = {
  { "Coding", 0.51f }, /* Coding */
  { "Build", 0.51f }, /* Build */
  { "Skype", 0.81f }, /* Skype */
  { "Web", 0.51f } /* Web */
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask   iscentered     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,          False,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       tag_web,    False,       False,       -1 },
	{ "luakit",   NULL,       NULL,       tag_web,    False,       False,       -1 },
	{ "Surf",     "surf",     NULL,       tag_web,    False,       False,       -1 },
	{ "Wine",     NULL,       NULL,       0,          True,            True,        -1 },
	{ "MPlayer",  NULL,       NULL,       0,          True,            True,        -1 },
	/* Skype windows */
	{ "Skype",    NULL,       "Skype™ 2.2 (Beta)",      tag_skype, False,       False,       -1 },
	{ "Skype",    NULL,       "Conference Call -",      tag_skype, True,       True,        -1 },
	{ "Skype",    NULL,       "Chat",          tag_skype, False,       False,       -1 },
	/* { "Skype",    NULL,       "- Skype",        tag_skype, False,       False,       -1 }, */
	/* Alsamixer window */
	{ "URxvt",    "urxvt",    "alsamixer", 0, False,           True,        -1 },
	{ "st-256color", "st-256color", "alsamixer", 0, False,     True,        -1 },
    /* Pulse audio controls */
    { "Pavucontrol", "pavucontrol", NULL, 0, False, True, -1 },
    /* Top task dispatcher */
	{ "URxvt",    "urxvt",    "top",       0, False,           True,        -1 },
	{ "st-256color", "st-256color", "top", 0, False,     True,        -1 },
    /* Youtube launch video script */
	{ "URxvt",    "urxvt",    "ytw.sh",       0, False,           True,        -1 },
	{ "st-256color", "st-256color", "ytw.sh", 0, False,     True,        -1 },
    /* Synergy_s window */
	{ "URxvt",          "urxvt",            "synergy_s", 0, False,           True,        -1 },
	{ "st-256color",    "st-256color",      "synergy_s", 0, False,           True,        -1 },
    /* Xine windows */
    { "xine",     NULL,       NULL,       0, False,            True,        -1 },
    /* Vnc viewer windows */
    { "Vncviewer", "vncviewer", "QEMU ", 0, False, True, -1 },
    { "Vncviewer", "vncviewer", "VNC authentication", 0, False, True, -1 },
    { "Vncviewer", "vncviewer", "TigerVNC Viewer", 0, False, True, -1 }
};

/* layout(s) */
//static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAG_MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress, TAG_MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress, TAG_MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress, TAG_MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress, TAG_MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd_user[]  = { "st", "-f", font, NULL };
static const char *termcmd_urxvt[] = { "urxvt_user", NULL };
static const char *termcmd_konsole[] = { "konsole", NULL };
static const char *konqueror_cmd[] = { "konqueror", "--profile", "filemanagement", NULL };
static const char *konqueror_web_cmd[] = { "konqueror", "--profile", "webbrowsing", NULL };
static const char *lock_command[] = { "/usr/bin/xscreensaver-command", "-lock", NULL };
static const char *alsamixer_cmd[] = { "urxvt_user", "-e", "\'alsamixer --view=all\'", NULL };

static Key keys[] = {
	/* type      modifier                     key        function        argument */
	{ KeyPress, MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ KeyPress, MODKEY,                       XK_Return, spawn,          {.v = termcmd_urxvt } },
	{ KeyPress, MODKEY|ShiftMask,             XK_t,      spawn,          {.v = termcmd_user} },
	{ KeyPress, MODKEY|ControlMask,           XK_t,      spawn,          {.v = termcmd_konsole} },
	{ KeyPress, ControlMask|ShiftMask,        XK_w,      spawn,          {.v = alsamixer_cmd } },
	{ KeyPress, Mod4Mask|ShiftMask,           XK_w,      spawn,          {.v = konqueror_web_cmd } },
	{ KeyPress, Mod4Mask|ShiftMask,           XK_e,      spawn,          {.v = konqueror_cmd } },
	{ KeyPress, MODKEY,                       XK_b,      togglebar,      {0} },
	{ KeyPress, MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ KeyPress, MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ KeyPress, MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ KeyPress, MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ KeyPress, MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ KeyPress, MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ KeyPress, MODKEY|ShiftMask,                       XK_Return, zoom,           {0} },
	{ KeyPress, MODKEY,                       XK_Tab,    view,           {0} },
	{ KeyPress, MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ KeyPress, MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ KeyPress, MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ KeyPress, MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ KeyPress, MODKEY,                       XK_space,  setlayout,      {0} },
	{ KeyPress, MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ KeyPress, MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ KeyPress, MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ KeyPress, MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ KeyPress, MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ KeyPress, MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ KeyPress, MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                                  XK_1,                      0)
	TAGKEYS(                                  XK_2,                      1)
	TAGKEYS(                                  XK_3,                      2)
	TAGKEYS(                                  XK_4,                      3)
	TAGKEYS(                                  XK_5,                      4)
	{ KeyPress, MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	{ KeyPress, MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ KeyPress, MODKEY|ControlMask,           XK_l,      spawn,          {.v = lock_command } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd_user } },
	{ ClkClientWin,         TAG_MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         TAG_MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         TAG_MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            TAG_MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            TAG_MODKEY,         Button3,        toggletag,      {0} },
};

