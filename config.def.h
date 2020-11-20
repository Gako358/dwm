/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;  /* vert inner gap between windows */
static const unsigned int gappoh         = 10;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 30;  /* vert outer gap between windows and screen edge */
static const int smartgaps               = 0;   /* 1 means no outer gap when there is only one window */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int bar_height              = 0;   /* 0 means derive from font, >= 1 explicit height */
static const int vertpad                 = 10;  /* vertical padding of bar */
static const int sidepad                 = 10;  /* horizontal padding of bar */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char statussep              = ';'; /* separator between status bars */
static const char *fonts[]               = {"DejaVuSansMono Nerd Font:pixelsize=14:antialias=true:autohint=true"};
static const char dmenufont[]            = "monospace:size=14";

static char norm_black[]                 = "#181819";
static char norm_red[]                   = "#fc5d7c";
static char norm_green[]                 = "#9ed072";
static char norm_yellow[]                = "#e7c664";
static char norm_blue[]                  = "#76cce0";
static char norm_magenta[]               = "#b39df3";
static char norm_cyan[]                  = "#f39660";
static char norm_white[]                 = "#e2e2e3";

static char norm_bar[]                   = "#f5dac5"; //Bar color for transparancy

static char *colors[][ColCount] = {
        /*                       fg                bg                border                float */
    [SchemeNorm]         = { norm_black,        norm_bar,       norm_black,     norm_black  },
    [SchemeSel]          = { norm_white,        norm_red,       norm_black,     norm_black  },
    [SchemeTitleNorm]    = { norm_bar,          norm_bar,       norm_black,     norm_black  },
    [SchemeTitleSel]     = { norm_bar,          norm_bar,       norm_black,     norm_black  },
    [SchemeTagsNorm]     = { norm_black,        norm_bar,       norm_black,     norm_black  },
    [SchemeTagsSel]      = { norm_black,        norm_bar,       norm_black,     norm_black  },
    /* [SchemeHid]          = { hidfgcolor,       hidbgcolor,       hidbordercolor,       hidfloatcolor  }, */
    /* [SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor  }, */                         
};

static char *statuscolors[][ColCount] = {
        /*                       fg                bg                border                float */
    { norm_black,       norm_bar,       norm_bar,       norm_bar         },
    { norm_black,       norm_black,     norm_black,     norm_bar         },
    { norm_black,       norm_red,       norm_red,       norm_red         },
    { norm_black,       norm_blue,      norm_blue,      norm_blue        },
    { norm_black,       norm_cyan,      norm_cyan,      norm_cyan        },
    { norm_black,       norm_green,     norm_green,     norm_green       },
    { norm_black,       norm_yellow,    norm_yellow,    norm_yellow      },
    { norm_black,       norm_magenta,   norm_magenta,   norm_magenta     },                                 
};

const char *spcmd1[] = {"st", "-n", "spterm",   "-g", "150x46", NULL };
const char *spcmd2[] = {"st", "-n", "mutterm",  "-g", "170x55", NULL };
const char *spcmd3[] = {"st", "-n", "ncmterm",  "-g", "120x55", NULL };
const char *spcmd4[] = {"st", "-n", "bashterm", "-g", "170x55", NULL };
const char *spcmd5[] = {"st", "-n", "weeterm",  "-g", "150x46", NULL };
static Sp scratchpads[] = {
   /* name          cmd  */
   {"spterm",      spcmd1},
   {"mutterm",     spcmd2},
   {"ncmterm",     spcmd3},
   {"bashterm",    spcmd4},
   {"weeterm",     spcmd5},
};

static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        = { "", "", "", "", "", "", "", "", "" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/* There are two options when it comes to per-client rules:
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Pcmanfm",        .isfloating = 1,    .iscentered = 1)
	RULE(.class = "Gimp",           .isfloating = 1,    .iscentered = 1)
	RULE(.class = "Brave",          .tags = 1 << 0,     .monitor = 0)
	RULE(.class = "discord",        .tags = 1 << 2,     .monitor = 2,   .switchtag = 1)
	RULE(.class = "lyx",            .tags = 1 << 4,     .monitor = 1,   .switchtag = 1)
	RULE(.class = "Virt-manager",   .tags = 1 << 6,     .monitor = 2,   .switchtag = 1)
	RULE(.class = "Steam",          .tags = 1 << 5,     .monitor = 1,   .isfloating = 1,    .iscentered = 1,   .switchtag = 1)
	RULE(.class = "Lutris",          .tags = 1 << 5,    .monitor = 1,   .isfloating = 1,    .iscentered = 1,   .switchtag = 1)

    // Games
	RULE(.class = "Battle.net.exe", .tags = 1 << 7,     .monitor = 1,   .isfloating = 1,    .iscentered = 1)
	RULE(.class = "explorer.exe",   .tags = 1 << 7,     .monitor = 1,   .isfloating = 1,    .iscentered = 1)
	RULE(.class = "Star Citizen",   .tags = 1 << 7,     .monitor = 1,   .isfloating = 1,    .iscentered = 1)
    
    // Scratchpads
	RULE(.instance = "spterm",      .tags = SPTAG(0), .isfloating = 1)
	RULE(.instance = "mutterm",     .tags = SPTAG(1), .isfloating = 1)
	RULE(.instance = "ncmterm",     .tags = SPTAG(2), .isfloating = 1)
	RULE(.instance = "bashterm",    .tags = SPTAG(3), .isfloating = 1)
	RULE(.instance = "weeterm",     .tags = SPTAG(4), .isfloating = 1)
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor  bar    alignment         widthfunc                drawfunc                clickfunc                name */
    // Powerline tags
	{ 'A',      0,     BAR_ALIGN_LEFT,   width_pwrl_tags,         draw_pwrl_tags,         click_pwrl_tags,         "powerline_tags" },
    // Bar tags
	{ -1,       0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
    // Bar systray
	{ 'A',      0,     BAR_ALIGN_RIGHT,  width_systray,           draw_systray,           click_systray,           "systray" },
    // Layout symbol
	{ -1,       0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
    // Powerline status
	{ 'A',      0,     BAR_ALIGN_RIGHT,  width_pwrl_status,       draw_pwrl_status,       click_pwrl_status,       "powerline_status" },
    // Win title
	{ -1,       0,     BAR_ALIGN_NONE,   width_wintitle,          draw_wintitle,          click_wintitle,          "wintitle" },
    // Powerline on extrabar
	{ 'A',      1,     BAR_ALIGN_RIGHT,  width_pwrl_status_es,    draw_pwrl_status_es,    click_pwrl_status,       "powerline_status" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", norm_white,
	"-nf", norm_black,
	"-sb", norm_green,
	"-sf", norm_white,
	NULL
};
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_w,          spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_b,          togglebar,              {0} },

    // Apps
    { MODKEY,                       XK_s,          spawn,                  SHCMD("pcmanfm")             },
    { MODKEY|Mod1Mask,              XK_Return,     spawn,                  SHCMD("st -e bash")          },
    { MODKEY|Mod1Mask,              XK_s,          spawn,                  SHCMD("surf")                },
    { MODKEY|Mod1Mask|ShiftMask,    XK_s,          spawn,                  SHCMD("tabbed -c surf -e")   },

    // Terminal
    { MODKEY|ShiftMask,             XK_Return,     spawn,                  SHCMD("st -e vifm")          },
    { MODKEY,                       XK_p,          spawn,                  SHCMD("st -e powerkit --config")  },

    // Language
    { MODKEY|ControlMask|ShiftMask, XK_u,          spawn,                  SHCMD("setxkbmap -layout us")  },
    { MODKEY|ControlMask|ShiftMask, XK_n,          spawn,                  SHCMD("setxkbmap -layout no")  },

    // Opacity
    { MODKEY,                       XK_a,          spawn,                  SHCMD("picom-trans -c -10")  },
    { MODKEY|ShiftMask,             XK_a,          spawn,                  SHCMD("picom-trans -c 100")  },

    // Volume
    { MODKEY,                       XK_bracketright,        spawn,         SHCMD("amixer -q sset Master 3%+")  },
    { MODKEY,                       XK_bracketleft,         spawn,         SHCMD("amixer -q sset Master 3%-")  },

    // Suspend and lock
    { MODKEY|Mod1Mask|ShiftMask,    XK_s,          spawn,                  SHCMD("systemctl suspend && slock")  },
    { MODKEY|Mod1Mask|ShiftMask,    XK_l,          spawn,                  SHCMD("slock")  },

    // Poweroff
    { MODKEY|Mod1Mask|ShiftMask,    XK_p,          spawn,                  SHCMD("systemctl poweroff")  },

    // Vanity
	{ MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },

	{ MODKEY,                       XK_Tab,        view,                   {0} },
    { MODKEY|ShiftMask,             XK_Return,     zoom,                   {0} },
	{ MODKEY,                       XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_q,          quit,                   {1} },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_m,          setlayout,              {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
    
    // Scratchpads
	{ MODKEY,                       XK_grave,      togglescratch,          {.ui = 0 } }, // Default Scratch
	{ MODKEY,                       XK_m,          togglescratch,          {.ui = 1 } }, // Mutt
	{ MODKEY,                       XK_n,          togglescratch,          {.ui = 2 } }, // NCMPCPP
	{ MODKEY,                       XK_b,          togglescratch,          {.ui = 3 } }, // Bashtop
	{ MODKEY,                       XK_c,          togglescratch,          {.ui = 4 } }, // Weechat
	{ MODKEY|ControlMask,           XK_grave,      setscratch,             {.ui = 0 } },
	{ MODKEY|ShiftMask,             XK_grave,      removescratch,          {.ui = 0 } },
	{ MODKEY,                       XK_x,          fullscreen,             {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,           {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~SPTAGMASK } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~SPTAGMASK } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },

    // MPDCONTROL
	{ MODKEY,                       XK_F1,         mpdchange,              {.i = -1} },
	{ MODKEY,                       XK_F2,         mpdchange,              {.i = +1} },
	{ MODKEY,                       XK_Escape,     mpdcontrol,             {0} },

    // Tags
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};

/* button definitions */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};
