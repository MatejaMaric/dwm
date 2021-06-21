/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx     = 2;   /* border pixel of windows */
static const unsigned int gappx  = 3;   /* gaps between windows */
static unsigned int snap         = 32;  /* snap pixel */
static int showbar               = 1;   /* 0 means no bar */
static int topbar                = 0;   /* 0 means bottom bar */
static char font[]               = "monospace:size=10";
static char dmenufont[]          = "monospace:size=10";
static const char *fonts[]       = { font };
static char normbgcolor[]        = "#222222";
static char normbordercolor[]    = "#444444";
static char normfgcolor[]        = "#bbbbbb";
static char selfgcolor[]         = "#eeeeee";
static char selbordercolor[]     = "#005577";
static char selbgcolor[]         = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "a", "s", "d", "f", "u", "i", "o", "p" };

static const Rule rules[0];
//static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  //{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
  //{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
//};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", "-e", "tmux", NULL };
static const char *roficmd[]  = { "rofi", "-show", "run", NULL };
static const char *scrotcmd[] = { "scrot", "-ze", "mv $f ~/stuff/pictures/screenshots/", NULL };
static const char *volinc[] = { "bash", "-c", "~/.local/bin/sb_set.sh -i", NULL };
static const char *voldec[] = { "bash", "-c", "~/.local/bin/sb_set.sh -d", NULL };
static const char *voltoggle[] = { "bash", "-c", "~/.local/bin/sb_set.sh -t", NULL };
static const char *nextlayout[] = { "bash", "-c", "~/.local/bin/sb_set.sh -n", NULL };
static const char *unmountcmd[] = { "bash", "-c", "~/.local/bin/unmount_usb.sh", NULL };


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "font",               STRING,  &font },
    { "dmenufont",          STRING,  &dmenufont },
    { "normbgcolor",        STRING,  &normbgcolor },
    { "normbordercolor",    STRING,  &normbordercolor },
    { "normfgcolor",        STRING,  &normfgcolor },
    { "selbgcolor",         STRING,  &selbgcolor },
    { "selbordercolor",     STRING,  &selbordercolor },
    { "selfgcolor",         STRING,  &selfgcolor },
    { "borderpx",           INTEGER, &borderpx },
    { "snap",               INTEGER, &snap },
    { "showbar",            INTEGER, &showbar },
    { "topbar",             INTEGER, &topbar },
    { "nmaster",            INTEGER, &nmaster },
    { "resizehints",        INTEGER, &resizehints },
    { "mfact",              FLOAT,   &mfact },
};

static Key keys[] = {
  /* modifier                       key        function        argument */
  //{ MODKEY,                       XK_b,      togglebar,      {0} },
  //{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  //{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  //{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  //{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  //{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
  //{ MODKEY,                       XK_Tab,    view,           {0} },
  //{ MODKEY,                       XK_space,  setlayout,      {0} },
  //{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  //{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  //{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  //{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  //{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  //{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

  TAGKEYS( XK_a, 0)
  TAGKEYS( XK_s, 1)
  TAGKEYS( XK_d, 2)
  TAGKEYS( XK_f, 3)
  TAGKEYS( XK_u, 4)
  TAGKEYS( XK_i, 5)
  TAGKEYS( XK_o, 6)
  TAGKEYS( XK_p, 7)

  { MODKEY,                       XK_Return, spawn,           {.v = termcmd } },
  { MODKEY,                       XK_r,      spawn,           {.v = roficmd } },
  { MODKEY,                       XK_w,      killclient,      {0} },

  { MODKEY,                       XK_j,      focusstack,      {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,      {.i = -1 } },
  { MODKEY,                       XK_t,      togglefloating,  {0} },

  { MODKEY,                       XK_1,      setlayout,       {.v = &layouts[0]} },
  { MODKEY,                       XK_2,      setlayout,       {.v = &layouts[1]} },
  { MODKEY,                       XK_3,      setlayout,       {.v = &layouts[2]} },

  { MODKEY|ControlMask,           XK_q,      quit,            {0} },

  { MODKEY|ControlMask,           XK_c,      spawn,           { .v = scrotcmd   } },
  { MODKEY,                       XK_h,      spawn,           { .v = volinc     } },
  { MODKEY,                       XK_n,      spawn,           { .v = voldec     } },
  { MODKEY,                       XK_m,      spawn,           { .v = voltoggle  } },
  { MODKEY,                       XK_space,  spawn,           { .v = nextlayout } },
  { MODKEY,                       XK_e,      spawn,           { .v = unmountcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
  { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
  { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
  { ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
  { ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

