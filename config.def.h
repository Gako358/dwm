/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx          = 1;        /* border pixel of windows */
static const unsigned int snap              = 32;       /* snap pixel */
static const int showbar                    = 1;        /* 0 means no bar */
static const int topbar                     = 1;        /* 0 means bottom bar */
/* vanity */
static const unsigned int gappih            = 19;       /* horiz inner gap between windows */
static const unsigned int gappiv            = 19;       /* vert inner gap between windows */
static const unsigned int gappoh            = 19;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov            = 19;       /* vert outer gap between windows and screen edge */
static const int smartgaps                  = 0;        /* 1 means no outer gap when there is only one window */
static const int user_bh                    = 25;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
/* static const double focusopacity         = 1.0; */
/* static const double unfocusopacity       = 0.85; */
static const char *fonts[]                  = {"DejaVuSansMono Nerd Font:pixelsize=14:antialias=true:autohint=true"};
static const char dmenufont[]               = "monospace:size=14";
/* colors */
static const char col_bg[]                  = "#282828";
static const char col_fg[]                  = "#ebdbb2";
static const char col_bar[]                 = "#f5dac5"; //This hold the color of the image, make the bar transparent
static const char col_red[]                 = "#fb4934";
static const char col_gray[]                = "#504945";
static const char col_dark[]                = "#3c3836";
static const char col_blue[]                = "#83a598";
static const char col_cyan[]                = "#8ec07c";
static const char col_green[]               = "#b8bb26";
static const char col_yellow[]              = "#fabd2f";
static const char col_purple[]              = "#d3869b";

static const char *colors[][3]      = {
	/*					            fg         bg       border   */
	[SchemeNorm]        =   { col_gray,     col_bar,    col_bg     },
	[SchemeSel]         =   { col_fg,       col_blue,   col_bg     },
	[SchemeTitle]       =   { col_bar,      col_bar,    col_bg     },
	[SchemeTitleSel]    =   { col_bar,      col_bar,    col_bg     },
};

static const char *statuscolors[][3] = {
    { col_bg,       col_bar,        col_bar     },
    { col_fg,       col_dark,       col_dark    },
    { col_gray,     col_red,        col_red     },
    { col_gray,     col_blue,       col_blue    },
    { col_gray,     col_green,      col_green   },
    { col_gray,     col_yellow,     col_yellow  },
    { col_gray,     col_purple,     col_purple  },
};

/* tagging */
/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; */
static const char *tags[] = { "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",           NULL,       NULL,       0,            1,             1,           -1 },
	{ "Pcmanfm",        NULL,       NULL,       0,            1,             1,           -1 },
	{ "Brave",	        NULL,       NULL,       1 << 0,       0,             0,            2 },
	{ "discord",        NULL,       NULL,       1 << 2,       0,             0,            1 },
	{ "lyx",            NULL,       NULL,       1 << 4,       0,             0,            0 },
	{ "Virt-manager",   NULL,       NULL,       1 << 6,       0,             0,            0 },
	{ "Steam",          NULL,       NULL,       1 << 6,       1,             1,            0 },
	{ "Lutris",         NULL,       NULL,       1 << 6,       1,             1,            0 },
	{ "battle.net.exe", NULL,       NULL,       1 << 6,       1,             1,            0 },
	{ "explorer.exe",   NULL,       NULL,       1 << 6,       1,             1,            0 },
	{ "Star Citizen",   NULL,       NULL,       1 << 6,       1,             1,            0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_fg, "-nf", col_bg, "-sb", col_red, "-sf", col_gray, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x37", NULL };
static const char *cmdprintscreen[]  = { "scrot", "-d3", "/home/merrinx/Pictures/Screenshots/%Y-%m-%d-%s_$wx$h.png", NULL  };

static Key keys[] = {
	/* modifier                     key                     function        argument */
	{ MODKEY,                       XK_w,                   spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,              spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,               togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_p,                   spawn,          {.v = cmdprintscreen } },
	{ MODKEY,                       XK_b,                   togglebar,      {0} },
	{ MODKEY,                       XK_j,                   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                   setmfact,       {.f = +0.05} },

    // Spawning Apps
	{ MODKEY,                       XK_s,                   spawn,          SHCMD("pcmanfm") },
	{ MODKEY|Mod1Mask,              XK_Return,              spawn,          SHCMD("st -e bash") },
	{ MODKEY|Mod1Mask,              XK_s,                   spawn, 		    SHCMD("surf") },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_s,                   spawn, 		    SHCMD("tabbed -c surf -e") },

    // Terminal Apps
	{ Mod1Mask,                     XK_d,                   spawn,          SHCMD("st -e bashtop") },
	{ Mod1Mask,                     XK_m,                   spawn,          SHCMD("st -e mutt") },
	{ Mod1Mask,                     XK_Return,              spawn,          SHCMD("st -e vifm") },
	{ Mod1Mask,                     XK_c,                   spawn,          SHCMD("st -e weechat") },
	{ Mod1Mask,                     XK_p,                   spawn, 		    SHCMD("st -e powerkit --config") },

    // Change language
	{ MODKEY|ControlMask|ShiftMask, XK_u,                   spawn,          SHCMD("setxkbmap -layout us") },
	{ MODKEY|ControlMask|ShiftMask, XK_n,                   spawn,          SHCMD("setxkbmap -layout no") },

    // Change Opacity
	{ MODKEY,                       XK_a,                   spawn,          SHCMD("picom-trans -c -10") },
	{ MODKEY|ShiftMask,             XK_a,                   spawn,          SHCMD("picom-trans -c 100") },

    // Volume
	{ MODKEY,                       XK_bracketright,        spawn,          SHCMD("amixer -q sset Master 3%+") },
	{ MODKEY,                       XK_bracketleft,         spawn,          SHCMD("amixer -q sset Master 3%-") },

    // Systemd and lock
	{ MODKEY|Mod1Mask|ShiftMask,    XK_s,                   spawn,          SHCMD("systemctl suspend && slock") },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,                   spawn,          SHCMD("slock") },

    // Shutdown PC
	{ MODKEY|Mod1Mask|ShiftMask,    XK_p,      spawn,          SHCMD("systemctl poweroff") },

    // Vanity
	{ MODKEY|ShiftMask,             XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask,              XK_0,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask|Mod1Mask,    XK_o,      incrovgaps,     {.i = -1 } },

    // Client
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_x,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // Tags
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

