/* See LICENSE file for copyright and license details. */

#define TRUE 1
#define FALSE 0

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
//Changed the names to more funny names
static const char *tags[] = { "一", "二", "三", "四" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance   title     tags mask     isfloating   monitor scratch */
	{  "Gimp",              NULL,      NULL,     0,            TRUE,           -1, 0},
	{  "Firefox",           NULL,      NULL,     0,            FALSE,          -1, 0},
	{  "discord",           NULL,      NULL,     0,            FALSE,          -1, 0},
	{  "VirtualBox Machine",NULL,      NULL,     0,            TRUE,           -1, 0},
	{  "feh",               NULL,      NULL,     0,            TRUE,           -1, 0},
	{  "Steam",             NULL,      "Friends List", 0,      TRUE,           -1, 0},
	{  "Steam",             NULL,      "Steam - News",0,       TRUE,           -1, 0},
	{  "Steam",             NULL,      "Steam - Self Updater",0,TRUE,          -1, 0},
	{  "ProtonUp-Qt",       NULL,      NULL,     0,            TRUE,           -1, 0},	
	{  NULL,                NULL,      "FML early loading progress",0,  TRUE,  -1, 0},
	{  "Minecraft *",       NULL,      NULL,     0,            TRUE,           -1, 0},
	{  NULL,                "Zoom *",  NULL,     0,            TRUE,           -1, 0},
	{  NULL,                "zoom",    NULL,     0,            TRUE,           -1, 0},
	{  "seahorse",          NULL,      NULL,     0,            TRUE,           -1, 0},
	{  "float:*",           NULL,      NULL,     0,            TRUE,           -1, 0},
	{  "*-gtk",             NULL,      NULL,     0,            TRUE,           -1, 0},
	{  "gcr-prompter",      NULL,      NULL,     0,            TRUE,           -1, 0},
	{ NULL,                 NULL,"scratchpad",   0,            TRUE,           -1, 's'}
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define Altkey Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"rofi-run", NULL};//{ "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = {"alacritty -e tmux", NULL };
static const char *powercmd[] = {"rofi-power", NULL};
static const char scratchpadname[] = "scratchpad";
/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "alacritty", "--title", scratchpadname, NULL}; 

static Key keys[] = {

	/* modifier                     key        function        argument */
	//{ MODKEY,                       XK_m,      spawn,          {.v = dmenucmd } },
	//{ Altkey,			            XK_m,      spawn,          {.v = powercmd } },
	//{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,           togglebar,              {0} },
	{ MODKEY,                       XK_j,       focusstackvis,       {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstackvis,       {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,          incnmaster,       {.i = -1 } },
	{ MODKEY,                       XK_period,       setmfact,     {.f = -0.05} },
	{ MODKEY,                       XK_comma,        setmfact,     {.f = +0.05} },
	{ MODKEY|Altkey,                XK_Return,           zoom,              {0} },
	{ MODKEY,                       XK_Tab,              view,              {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,              {0} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // Sets it to be floating
	// { MODKEY,                       XK_p,      setlayout,      {.v = &layouts[2]} }, // Sets it to be monocel
	{ MODKEY|ControlMask,           XK_space,  setlayout,    {.v = &layouts[0]} }, // Set to tiling
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,              {0} },
	{ MODKEY,                       XK_0,                view,      {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                 tag,      {.ui = ~0 } },
	{ MODKEY,                       XK_l,            focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_h,            focusmon,       {.i = +1 } },
	{ MODKEY|Altkey,                XK_l,     focusmon_nomove,       {.i = -1 } },
	{ MODKEY|Altkey,                XK_h,     focusmon_nomove,       {.i = +1 } },
	{ MODKEY|Altkey|ShiftMask,      XK_h,                show,              {0} },
	//{ MODKEY|Altkey,				XK_s,	   showkeys,		{0} },
	{ MODKEY|Altkey,                XK_h,                hide,              {0} },
	{ MODKEY|ShiftMask,             XK_l,              tagmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,              tagmon,       {.i = +1 } },
	{ Altkey,                       XK_f,            togglefullscreen,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,                   quit,           {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          MODKEY,         Button1,        togglewin,      {0} },
	{ ClkWinTitle,          MODKEY,         Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
3	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
	// { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,			MODKEY|ShiftMask, Button3,		dragmfact,		{0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

