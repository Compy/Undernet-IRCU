#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20100610

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 23 "./ircd_parser.y"

#include "config.h"
#include "s_conf.h"
#include "class.h"
#include "client.h"
#include "crule.h"
#include "ircd_features.h"
#include "fileio.h"
#include "gline.h"
#include "hash.h"
#include "ircd.h"
#include "ircd_alloc.h"
#include "ircd_chattr.h"
#include "ircd_log.h"
#include "ircd_reply.h"
#include "ircd_snprintf.h"
#include "ircd_string.h"
#include "list.h"
#include "listener.h"
#include "match.h"
#include "motd.h"
#include "numeric.h"
#include "numnicks.h"
#include "opercmds.h"
#include "parse.h"
#include "res.h"
#include "s_auth.h"
#include "s_bsd.h"
#include "s_conf.h"
#include "s_debug.h"
#include "s_misc.h"
#include "send.h"
#include "struct.h"
#include "sys.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_STRINGS 80 /* Maximum number of feature params. */
#define USE_IPV4 (1 << 16)
#define USE_IPV6 (1 << 17)

  extern struct LocalConf   localConf;
  extern struct DenyConf*   denyConfList;
  extern struct CRuleConf*  cruleConfList;
  extern struct ServerConf* serverConfList;
  extern struct s_map*      GlobalServiceMapList;
  extern struct qline*      GlobalQuarantineList;

  int yylex(void);
  /* Now all the globals we need :/... */
  int tping, tconn, maxlinks, sendq, port, invert, stringno, flags;
  char *name, *pass, *host, *ip, *username, *origin, *hub_limit;
  struct SLink *hosts;
  char *stringlist[MAX_STRINGS];
  struct ListenerFlags listen_flags;
  struct ConnectionClass *c_class;
  struct DenyConf *dconf;
  struct ServerConf *sconf;
  struct s_map *smap;
  struct Privs privs;
  struct Privs privs_dirty;

static void parse_error(char *pattern,...) {
  static char error_buffer[1024];
  va_list vl;
  va_start(vl,pattern);
  ircd_vsnprintf(NULL, error_buffer, sizeof(error_buffer), pattern, vl);
  va_end(vl);
  yyerror(error_buffer);
}

static void free_slist(struct SLink **link) {
  struct SLink *next;
  while (*link != NULL) {
    next = (*link)->next;
    MyFree((*link)->value.cp);
    free_link(*link);
    *link = next;
  }
}

#line 194 "./ircd_parser.y"
typedef union{
 char *text;
 int num;
} YYSTYPE;
#line 108 "y.tab.c"
/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

extern int YYPARSE_DECL();
extern int YYLEX_DECL();

#define QSTRING 257
#define NUMBER 258
#define GENERAL 259
#define ADMIN 260
#define LOCATION 261
#define CONTACT 262
#define CONNECT 263
#define CLASS 264
#define CHANNEL 265
#define PINGFREQ 266
#define CONNECTFREQ 267
#define MAXLINKS 268
#define MAXHOPS 269
#define SENDQ 270
#define NAME 271
#define HOST 272
#define IP 273
#define USERNAME 274
#define PASS 275
#define LOCAL 276
#define SECONDS 277
#define MINUTES 278
#define HOURS 279
#define DAYS 280
#define WEEKS 281
#define MONTHS 282
#define YEARS 283
#define DECADES 284
#define BYTES 285
#define KBYTES 286
#define MBYTES 287
#define GBYTES 288
#define TBYTES 289
#define SERVER 290
#define PORT 291
#define MASK 292
#define HUB 293
#define LEAF 294
#define UWORLD 295
#define YES 296
#define NO 297
#define OPER 298
#define VHOST 299
#define HIDDEN 300
#define MOTD 301
#define JUPE 302
#define NICK 303
#define NUMERIC 304
#define DESCRIPTION 305
#define CLIENT 306
#define KILL 307
#define CRULE 308
#define REAL 309
#define REASON 310
#define TFILE 311
#define RULE 312
#define ALL 313
#define FEATURES 314
#define QUARANTINE 315
#define PSEUDO 316
#define PREPEND 317
#define USERMODE 318
#define IAUTH 319
#define TIMEOUT 320
#define FAST 321
#define AUTOCONNECT 322
#define PROGRAM 323
#define TOK_IPV4 324
#define TOK_IPV6 325
#define DNS 326
#define TPRIV_CHAN_LIMIT 327
#define TPRIV_MODE_LCHAN 328
#define TPRIV_DEOP_LCHAN 329
#define TPRIV_WALK_LCHAN 330
#define TPRIV_LOCAL_KILL 331
#define TPRIV_REHASH 332
#define TPRIV_RESTART 333
#define TPRIV_DIE 334
#define TPRIV_GLINE 335
#define TPRIV_LOCAL_GLINE 336
#define TPRIV_LOCAL_JUPE 337
#define TPRIV_LOCAL_BADCHAN 338
#define TPRIV_LOCAL_OPMODE 339
#define TPRIV_OPMODE 340
#define TPRIV_SET 341
#define TPRIV_WHOX 342
#define TPRIV_BADCHAN 343
#define TPRIV_SEE_CHAN 344
#define TPRIV_SHOW_INVIS 345
#define TPRIV_SHOW_ALL_INVIS 346
#define TPRIV_PROPAGATE 347
#define TPRIV_UNLIMIT_QUERY 348
#define TPRIV_DISPLAY 349
#define TPRIV_SEE_OPERS 350
#define TPRIV_WIDE_GLINE 351
#define TPRIV_FORCE_OPMODE 352
#define TPRIV_FORCE_LOCAL_OPMODE 353
#define TPRIV_APASS_OPMODE 354
#define TPRIV_LIST_CHAN 355
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,   10,   10,   10,   10,   10,   10,   10,   10,
   10,   10,   10,   10,   10,   10,   10,   10,   10,    2,
    2,    4,    4,    5,    3,    3,    3,    3,    3,    3,
    3,    3,    1,    1,    1,    1,    1,    1,    6,    6,
    6,    6,    6,    6,   18,   27,   27,   28,   29,   30,
   12,   31,   31,   32,   32,   32,   32,   32,   32,   33,
   34,   36,   35,   37,   38,   39,   11,   40,   40,   41,
   41,   42,   43,   44,   13,   45,   45,   46,   46,   46,
   46,   46,   46,   46,   47,   48,   49,   50,   51,   52,
   54,   14,   55,   55,   56,   56,   56,   56,   56,   56,
   56,   56,   56,   56,   56,   57,   58,   59,   60,   61,
   62,   63,   64,   65,   66,   67,   67,   15,   68,   68,
   69,   70,   16,   71,   71,   72,   72,   72,   72,   72,
   73,   74,   75,   76,   53,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    7,    7,    9,
    9,    9,    9,    9,   17,   77,   77,   78,   78,   78,
   78,   78,   78,   79,   80,   81,   82,   83,   83,   84,
   84,   85,   19,   86,   86,   87,   87,   87,   87,   87,
   87,   87,   88,   89,   90,   91,   92,   93,   94,   95,
   20,   96,   96,   97,   97,   97,   97,   97,   98,  100,
   99,  102,  101,  103,   21,  104,  104,  105,  105,  105,
  106,  107,  108,  108,   22,  109,  109,  110,  110,  111,
  112,   23,  113,  113,  115,  114,  116,  116,  117,   24,
  118,  118,  119,  121,   25,  120,  120,  122,  122,  122,
  122,  123,  124,  125,  126,   26,  127,  127,  128,  130,
  129,
};
static const short yylen[] = {                            2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    2,    1,
    1,    2,    1,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    2,    2,    2,    1,    3,
    3,    3,    3,    3,    5,    2,    1,    1,    4,    0,
    6,    2,    1,    1,    1,    1,    1,    1,    1,    4,
    4,    4,    4,    6,    5,    0,    6,    2,    1,    1,
    1,    4,    4,    0,    6,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    4,    4,    4,    4,    4,    4,
    0,    6,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    4,    4,    4,    4,    4,
    4,    2,    2,    4,    4,    4,    4,    5,    2,    1,
    1,    4,    5,    1,    2,    1,    1,    1,    1,    1,
    4,    4,    4,    4,    4,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    0,
    1,    1,    2,    2,    5,    2,    1,    1,    1,    1,
    1,    1,    1,    5,    5,    6,    4,    4,    4,    4,
    4,    0,    6,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    4,    4,    4,    4,    4,    4,    4,    0,
    6,    2,    1,    1,    1,    1,    1,    1,    4,    4,
    4,    4,    4,    0,    6,    2,    1,    1,    1,    1,
    4,    4,    4,    4,    5,    2,    1,    1,    1,    4,
    4,    5,    2,    1,    0,    5,    2,    1,    1,    5,
    2,    1,    4,    0,    7,    2,    1,    1,    1,    1,
    1,    4,    4,    4,    2,    5,    2,    1,    1,    0,
    5,
};
static const short yydefred[] = {                         0,
    0,   50,   66,   91,   74,    0,    0,    0,    0,    0,
  192,  210,  224,    0,    0,    0,    0,    0,    2,    3,
    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    1,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  178,  179,  180,  181,  182,  183,
    0,    0,    0,  121,    0,    0,    0,    0,  164,  147,
  140,  136,  137,  138,  139,  141,  142,  143,  144,  145,
  146,  148,  154,  149,  150,  151,  152,  153,  155,  156,
  157,  158,  159,  160,  161,  162,  165,  166,  167,  163,
    0,  130,    0,  124,  126,  127,  128,  129,    0,    0,
    0,    0,  238,  239,    0,    0,    0,   48,    0,    0,
    0,  245,    0,  244,    0,    0,  252,  254,    0,    0,
    0,  269,    0,    0,    0,    0,    0,    0,    0,   54,
   55,   56,   57,   58,   59,    0,    0,    0,   69,   70,
   71,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   95,   96,   97,   98,   99,  100,  101,
  102,  103,  104,  105,    0,    0,    0,    0,    0,    0,
    0,    0,   78,   79,   80,   81,   82,   83,   84,    0,
    0,    0,    0,    0,    0,  176,    0,    0,  119,    0,
    0,    0,    0,    0,    0,  125,    0,    0,    0,  236,
    0,    0,   46,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  196,  197,  198,  199,  200,  201,  202,    0,
    0,    0,    0,    0,    0,    0,  214,  215,  216,  217,
  218,    0,    0,    0,    0,    0,  228,  229,  230,    0,
    0,  243,    0,    0,  251,    0,  270,    0,  267,    0,
    0,    0,    0,    0,    0,    0,   52,    0,    0,    0,
   68,    0,    0,    0,    0,    0,    0,  113,    0,  112,
    0,    0,    0,   93,    0,    0,    0,    0,    0,    0,
    0,   76,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  175,    0,  118,    0,    0,    0,    0,  168,  169,
    0,  123,    0,    0,  235,    0,   45,    0,    0,    0,
    0,    0,    0,    0,    0,  194,    0,    0,    0,    0,
    0,    0,  212,    0,    0,    0,    0,  226,    0,  242,
    0,  250,    0,    0,    0,    0,    0,    0,  258,  259,
  260,  261,    0,  266,    0,    0,    0,    0,    0,    0,
   51,    0,    0,   67,    0,   39,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   92,    0,    0,   23,
    0,    0,    0,    0,    0,    0,    0,   75,  188,  189,
  173,  174,    0,  187,    0,  190,  191,  122,  134,  131,
  133,  132,  135,  240,  241,   49,    0,    0,    0,    0,
    0,    0,    0,  193,    0,    0,    0,    0,    0,  211,
    0,    0,    0,    0,  225,  249,    0,  248,  253,    0,
    0,    0,  265,    0,  256,    0,   61,   63,   60,   62,
    0,    0,   72,   73,  108,    0,    0,    0,    0,    0,
  115,  106,  109,  107,  110,  114,  111,  116,  117,   86,
   22,    0,   25,   26,   27,   28,   29,   30,   31,   32,
   24,   87,   88,   89,   34,   35,   36,   37,   38,   85,
   90,  184,    0,  185,  206,  208,  203,  204,  205,  207,
  209,  219,  220,  221,  222,  223,  231,  232,  233,  234,
  246,  247,    0,    0,    0,  255,  271,   65,    0,   44,
    0,    0,   42,   43,  186,  262,  264,  263,   64,
};
static const short yydgoto[] = {                         18,
  394,  388,  481,  389,  390,  391,  321,  111,  307,   19,
   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
   30,   31,   32,   33,   34,   35,  126,  127,  128,   37,
  148,  149,  150,  151,  152,  153,  154,  155,   38,  158,
  159,  160,  161,   40,  191,  192,  193,  194,  195,  196,
  197,  198,  112,   39,  172,  173,  174,  175,  176,  177,
  178,  179,  180,  181,  182,  183,  184,   72,   73,   74,
  113,  114,  115,  116,  117,  118,   63,   64,   65,   66,
   67,   68,   69,   70,   46,  231,  232,  233,  234,  235,
  236,  237,  238,  239,   47,  245,  246,  247,  248,  249,
  250,  251,   48,  255,  256,  257,  258,  259,  121,  122,
  123,  124,  133,  134,  260,  437,  438,  136,  137,  357,
  266,  358,  359,  360,  361,  362,  140,  141,  142,  363,
};
static const short yysindex[] = {                      -216,
  -47,    0,    0,    0,    0,  -89,  -70,  -53,  -40,  -36,
    0,    0,    0,  -21,  -19, -162,  -16, -216,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -12,    3,   15,   22,
 -136, -158,   13, -262, -157,   26,   27,   38,  -87,  -84,
   45, -148,    0, -263, -201, -163,  103,  116,  118,  119,
  120,  121,   51, -136,    0,    0,    0,    0,    0,    0,
  123,   64, -158,    0,  129,  130,  131,  132,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  133,    0, -124,    0,    0,    0,    0,    0,  134,  135,
   72, -262,    0,    0,  137,   74, -157,    0, -154, -245,
 -274,    0, -118,    0,  139, -104,    0,    0,  140,  108,
 -148,    0,  173,  174,  217,  218, -240,  155, -263,    0,
    0,    0,    0,    0,    0,  220,  221, -119,    0,    0,
    0,  222,  225,  226,  229,  230,  231,  -31,  234,  233,
  235,  170, -163,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  236,  237,  238,  239,  240,  241,
  178,  103,    0,    0,    0,    0,    0,    0,    0, -251,
 -244,   47, -244, -203,  246,    0,   49,  248,    0,   52,
   53,   54,   55, -200,  249,    0,   56,   57,  257,    0,
   60,  259,    0,  258,  260,  261,  262,  263,  264,  265,
  202, -154,    0,    0,    0,    0,    0,    0,    0,  267,
  268,  269,  270,  271,  208, -245,    0,    0,    0,    0,
    0,  273,  274,  275,  212, -274,    0,    0,    0,  277,
  280,    0,  125,  313,    0, -248,    0,  316,    0,  126,
  127,  122,  128,  315,  317,  318,    0,  136,  138,  322,
    0,  141,  -26,  142,  143,  144,  145,    0,  147,    0,
  149, -181,  327,    0,  -26,  -26,  -26,  -26,  150,  151,
  328,    0,  329,  330,   65,   67,  153,  333,  152,  335,
  337,    0,  338,    0,  343,  353,  354,  355,    0,    0,
  356,    0,  357,  358,    0,  359,    0,  162,  -26,  163,
  165,  166,  167,  -26,  366,    0,  169,  171,  172,  203,
  204,  368,    0,  205,  206, -174,  400,    0,  207,    0,
  406,    0,  405,  407,  408,  411,  342, -248,    0,    0,
    0,    0,  207,    0,  412,  413,  414,  415,  219, -244,
    0,  416,  418,    0,  419,    0,  -26,    9,  420,  421,
  422,  423,  424,  425,  426,  427,    0,  428,  -26,    0,
  -10,  429,   29,  430,  -23,  431,  432,    0,    0,    0,
    0,    0,  433,    0,  -56,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  434,   82,  435,  436,
  437,  438,  115,    0,  439,  440,  441,  442,  443,    0,
  444,  445,  446,  447,    0,    0,   18,    0,    0,  250,
  251,  252,    0,  451,    0,   19,    0,    0,    0,    0,
  452,  255,    0,    0,    0,  124,  -26,  -26,  -26,  -26,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -10,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  454,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  455,  456,  457,    0,    0,    0,  458,    0,
   42,   42,    0,    0,    0,    0,    0,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  393,    0,    0,    0,    0,    0,    0,
    0,    0,  394,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  395,    0,    0,    0,    0,  396,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  108,    0,    0,    0,    0,    0,    0,    0,  397,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  398,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  399,    0,    0,    0,    0,    0,    0,    0,    0,
  272,    0,  276,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  401,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  402,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  403,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -125, -123,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  404,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  276,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  466,    0,
  472,    0,    0,    0,  473,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -41,  -28,    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  242,    0,    0,  146, -272,    0,    0, -198,  516,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  409,    0,    0,    0,
  388,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  381,    0,    0,    0,  348,    0,    0,    0,    0,    0,
    0,    0,  -48,    0,  369,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  468,    0,    0,
    0,  448,    0,    0,    0,    0,  479,    0,    0,    0,
    0,    0,    0,    0,    0,  312,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  299,    0,    0,    0,    0,
    0,    0,    0,  290,    0,    0,    0,    0,  449,    0,
    0,    0,    0,  417,    0,  184, -379,    0,  450,  190,
    0,    0,    0,    0,    0,    0,  410,    0,    0,    0,
};
#define YYTABLESIZE 586
static const short yytable[] = {                         40,
  215,   40,  494,   40,  309,  280,  261,  143,  199,  119,
  378,   36,   41,  377,   41,  252,   41,   40,  459,  457,
  264,  458,  353,  460,  393,  395,  240,  288,  241,  289,
   41,  459,  457,   41,  458,  144,  460,  253,  254,    1,
  145,  146,    2,    3,  303,  304,    4,    5,  120,  274,
  459,  457,   42,  458,  354,  460,  418,  512,  275,  156,
  157,  423,  147,  242,  243,  244,  512,  461,  355,   43,
  459,  457,  356,  458,    6,  460,  511,  517,    7,  305,
  306,    8,   44,  459,    9,   10,   45,  483,  460,   11,
   12,   13,  310,  311,   51,  319,  320,   14,   15,   16,
  162,   49,   17,   50,  456,  163,   52,  164,  165,  224,
   54,  166,   71,  225,  385,  386,  472,  226,  227,  228,
  229,  433,  434,  459,  457,   55,  458,  167,  460,  168,
  169,  171,  171,  172,  172,  170,  230,   56,  132,   75,
  496,  156,  157,  199,   57,  125,   76,   77,  129,  130,
   78,   79,  135,   58,   59,   60,  459,  457,  171,  458,
  131,  460,   61,   62,  520,  459,  457,  138,  458,  132,
  460,  452,  135,  501,  139,  205,  200,   80,  201,  202,
  203,  204,   81,  207,  521,  522,  523,  524,  208,  210,
  211,  212,  213,  214,  217,  218,  219,  221,  222,  263,
  267,  493,   82,   83,   84,   85,   86,   87,   88,   89,
   90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
  100,  101,  102,  103,  104,  105,  106,  107,  108,  109,
  110,  376,  268,  270,  271,   40,   40,   40,   40,   40,
   40,   40,   40,   40,   40,   40,   40,   40,   41,   41,
   41,   41,   41,   41,   41,   41,   41,   41,   41,   41,
   41,  485,  486,  487,  488,  489,  473,  474,  475,  476,
  477,  478,  479,  480,  436,  436,   75,  272,  273,  276,
  278,  279,  282,   76,   77,  283,  284,   78,   79,  285,
  286,  287,  290,  291,  293,  292,  295,  296,  297,  298,
  299,  300,  301,  308,  312,  313,  314,  322,  315,  316,
  317,  318,  323,  324,   80,  325,  326,  327,  328,   81,
  329,  330,  331,  332,  333,  334,  335,  337,  338,  339,
  340,  341,  342,  344,  345,  346,  347,  349,  350,   82,
   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,
   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,
  103,  104,  105,  106,  107,  108,  109,  110,  185,  186,
  187,  352,  188,  189,  364,  369,  371,  370,   79,  367,
  374,  351,  365,  366,  368,  387,  398,  399,  400,  401,
  402,  404,  372,  406,  373,  407,  408,  375,  379,  380,
  381,  409,  382,  383,   80,  384,  396,  397,  405,   81,
  403,  410,  411,  412,  413,  414,  415,  416,  417,  419,
  190,  420,  421,  422,  424,  425,  430,  426,  427,   82,
   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,
   93,   94,   95,   96,   97,   98,   99,  100,  101,  102,
  103,  104,  105,  106,  107,  108,  109,  110,  435,  428,
  429,  431,  432,  436,  439,  440,  444,  441,  442,  443,
  447,  448,  449,  450,  453,  451,  454,  455,  462,  463,
  464,  465,  466,  467,  468,  469,  470,  482,  484,  490,
  491,  492,  495,  497,  498,  499,  500,  502,  503,  504,
  505,  506,  507,  508,  509,  510,  513,  514,  515,  516,
  518,  519,  525,  526,  527,  528,  529,  177,  120,  237,
   47,   53,   94,   77,   21,  195,  213,  227,  257,  170,
   20,   33,  170,   53,  471,  223,  277,  392,  281,  302,
  209,  294,  206,  336,  343,  348,  446,  445,    0,  262,
  269,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  216,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  220,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  265,
};
static const short yycheck[] = {                         41,
  125,   43,   59,   45,  203,  125,  125,  271,   57,  272,
  283,   59,   41,   40,   43,  290,   45,   59,   42,   43,
  125,   45,  271,   47,  297,  298,  272,   59,  274,   61,
   59,   42,   43,  123,   45,  299,   47,  312,  313,  256,
  304,  305,  259,  260,  296,  297,  263,  264,  311,  290,
   42,   43,  123,   45,  303,   47,  329,  437,  299,  261,
  262,  334,  326,  309,  310,  311,  446,   59,  317,  123,
   42,   43,  321,   45,  291,   47,   59,   59,  295,  324,
  325,  298,  123,   42,  301,  302,  123,   59,   47,  306,
  307,  308,  296,  297,  257,  296,  297,  314,  315,  316,
  264,  123,  319,  123,  377,  269,  123,  271,  272,  264,
  123,  275,  271,  268,  296,  297,  389,  272,  273,  274,
  275,  296,  297,   42,   43,  123,   45,  291,   47,  293,
  294,  257,  258,  257,  258,  299,  291,  123,  257,  264,
   59,  261,  262,  192,  123,  303,  271,  272,  123,  123,
  275,  276,  257,  290,  291,  292,   42,   43,  322,   45,
  123,   47,  299,  300,   41,   42,   43,  123,   45,  257,
   47,  370,  257,   59,  323,  125,   61,  302,   61,   61,
   61,   61,  307,   61,  457,  458,  459,  460,  125,   61,
   61,   61,   61,   61,   61,   61,  125,   61,  125,   61,
   61,  258,  327,  328,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,  346,  347,  348,  349,  350,  351,  352,  353,  354,
  355,  258,  125,   61,   61,  277,  278,  279,  280,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  277,  278,
  279,  280,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  285,  286,  287,  288,  289,  277,  278,  279,  280,
  281,  282,  283,  284,  257,  257,  264,   61,   61,  125,
   61,   61,   61,  271,  272,   61,   61,  275,  276,   61,
   61,   61,   59,   61,  125,   61,   61,   61,   61,   61,
   61,   61,  125,  257,   59,  257,   59,   59,  257,  257,
  257,  257,  257,  257,  302,   59,  257,   59,   61,  307,
   61,   61,   61,   61,   61,   61,  125,   61,   61,   61,
   61,   61,  125,   61,   61,   61,  125,   61,   59,  327,
  328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
  348,  349,  350,  351,  352,  353,  354,  355,  266,  267,
  268,   59,  270,  271,   59,   61,   59,   61,  276,  258,
   59,  257,  257,  257,  257,   59,   59,   59,   59,  325,
  324,   59,  257,   59,  257,   59,   59,  257,  257,  257,
  257,   59,  258,  257,  302,  257,  257,  257,  257,  307,
  258,   59,   59,   59,   59,   59,   59,   59,  257,  257,
  318,  257,  257,  257,   59,  257,   59,  257,  257,  327,
  328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
  348,  349,  350,  351,  352,  353,  354,  355,   59,  257,
  257,  257,  257,  257,   59,   61,  125,   61,   61,   59,
   59,   59,   59,   59,   59,  257,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,   59,  257,  257,  257,   59,
   59,  257,   59,   59,   59,   59,   59,  125,  125,  125,
  125,  125,  125,  125,   59,  125,  125,  125,  125,  258,
   59,   59,  257,   18,  389,  127,  149,  296,  158,  192,
   73,  173,   64,  232,  246,  256,  363,  358,   -1,  133,
  141,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  113,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  122,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  136,
};
#define YYFINAL 18
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 355
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,"';'",
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"QSTRING","NUMBER","GENERAL","ADMIN","LOCATION","CONTACT","CONNECT",
"CLASS","CHANNEL","PINGFREQ","CONNECTFREQ","MAXLINKS","MAXHOPS","SENDQ","NAME",
"HOST","IP","USERNAME","PASS","LOCAL","SECONDS","MINUTES","HOURS","DAYS",
"WEEKS","MONTHS","YEARS","DECADES","BYTES","KBYTES","MBYTES","GBYTES","TBYTES",
"SERVER","PORT","MASK","HUB","LEAF","UWORLD","YES","NO","OPER","VHOST","HIDDEN",
"MOTD","JUPE","NICK","NUMERIC","DESCRIPTION","CLIENT","KILL","CRULE","REAL",
"REASON","TFILE","RULE","ALL","FEATURES","QUARANTINE","PSEUDO","PREPEND",
"USERMODE","IAUTH","TIMEOUT","FAST","AUTOCONNECT","PROGRAM","TOK_IPV4",
"TOK_IPV6","DNS","TPRIV_CHAN_LIMIT","TPRIV_MODE_LCHAN","TPRIV_DEOP_LCHAN",
"TPRIV_WALK_LCHAN","TPRIV_LOCAL_KILL","TPRIV_REHASH","TPRIV_RESTART",
"TPRIV_DIE","TPRIV_GLINE","TPRIV_LOCAL_GLINE","TPRIV_LOCAL_JUPE",
"TPRIV_LOCAL_BADCHAN","TPRIV_LOCAL_OPMODE","TPRIV_OPMODE","TPRIV_SET",
"TPRIV_WHOX","TPRIV_BADCHAN","TPRIV_SEE_CHAN","TPRIV_SHOW_INVIS",
"TPRIV_SHOW_ALL_INVIS","TPRIV_PROPAGATE","TPRIV_UNLIMIT_QUERY","TPRIV_DISPLAY",
"TPRIV_SEE_OPERS","TPRIV_WIDE_GLINE","TPRIV_FORCE_OPMODE",
"TPRIV_FORCE_LOCAL_OPMODE","TPRIV_APASS_OPMODE","TPRIV_LIST_CHAN",
};
static const char *yyrule[] = {
"$accept : blocks",
"blocks : blocks block",
"blocks : block",
"block : adminblock",
"block : generalblock",
"block : classblock",
"block : connectblock",
"block : uworldblock",
"block : operblock",
"block : portblock",
"block : jupeblock",
"block : clientblock",
"block : killblock",
"block : cruleblock",
"block : motdblock",
"block : featuresblock",
"block : quarantineblock",
"block : pseudoblock",
"block : iauthblock",
"block : error ';'",
"timespec : expr",
"timespec : factoredtimes",
"factoredtimes : factoredtimes factoredtime",
"factoredtimes : factoredtime",
"factoredtime : expr timefactor",
"timefactor : SECONDS",
"timefactor : MINUTES",
"timefactor : HOURS",
"timefactor : DAYS",
"timefactor : WEEKS",
"timefactor : MONTHS",
"timefactor : YEARS",
"timefactor : DECADES",
"sizespec : expr",
"sizespec : expr BYTES",
"sizespec : expr KBYTES",
"sizespec : expr MBYTES",
"sizespec : expr GBYTES",
"sizespec : expr TBYTES",
"expr : NUMBER",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : '(' expr ')'",
"jupeblock : JUPE '{' jupeitems '}' ';'",
"jupeitems : jupeitem jupeitems",
"jupeitems : jupeitem",
"jupeitem : jupenick",
"jupenick : NICK '=' QSTRING ';'",
"$$1 :",
"generalblock : GENERAL $$1 '{' generalitems '}' ';'",
"generalitems : generalitem generalitems",
"generalitems : generalitem",
"generalitem : generalnumeric",
"generalitem : generalname",
"generalitem : generalvhost",
"generalitem : generaldesc",
"generalitem : generaldnsvhost",
"generalitem : generaldnsserver",
"generalnumeric : NUMERIC '=' NUMBER ';'",
"generalname : NAME '=' QSTRING ';'",
"generaldesc : DESCRIPTION '=' QSTRING ';'",
"generalvhost : VHOST '=' QSTRING ';'",
"generaldnsvhost : DNS VHOST '=' address_family QSTRING ';'",
"generaldnsserver : DNS SERVER '=' QSTRING ';'",
"$$2 :",
"adminblock : ADMIN $$2 '{' adminitems '}' ';'",
"adminitems : adminitems adminitem",
"adminitems : adminitem",
"adminitem : adminlocation",
"adminitem : admincontact",
"adminlocation : LOCATION '=' QSTRING ';'",
"admincontact : CONTACT '=' QSTRING ';'",
"$$3 :",
"classblock : CLASS $$3 '{' classitems '}' ';'",
"classitems : classitem classitems",
"classitems : classitem",
"classitem : classname",
"classitem : classpingfreq",
"classitem : classconnfreq",
"classitem : classmaxlinks",
"classitem : classsendq",
"classitem : classusermode",
"classitem : priv",
"classname : NAME '=' QSTRING ';'",
"classpingfreq : PINGFREQ '=' timespec ';'",
"classconnfreq : CONNECTFREQ '=' timespec ';'",
"classmaxlinks : MAXLINKS '=' expr ';'",
"classsendq : SENDQ '=' sizespec ';'",
"classusermode : USERMODE '=' QSTRING ';'",
"$$4 :",
"connectblock : CONNECT $$4 '{' connectitems '}' ';'",
"connectitems : connectitem connectitems",
"connectitems : connectitem",
"connectitem : connectname",
"connectitem : connectpass",
"connectitem : connectclass",
"connectitem : connecthost",
"connectitem : connectport",
"connectitem : connectvhost",
"connectitem : connectleaf",
"connectitem : connecthub",
"connectitem : connecthublimit",
"connectitem : connectmaxhops",
"connectitem : connectauto",
"connectname : NAME '=' QSTRING ';'",
"connectpass : PASS '=' QSTRING ';'",
"connectclass : CLASS '=' QSTRING ';'",
"connecthost : HOST '=' QSTRING ';'",
"connectport : PORT '=' NUMBER ';'",
"connectvhost : VHOST '=' QSTRING ';'",
"connectleaf : LEAF ';'",
"connecthub : HUB ';'",
"connecthublimit : HUB '=' QSTRING ';'",
"connectmaxhops : MAXHOPS '=' expr ';'",
"connectauto : AUTOCONNECT '=' YES ';'",
"connectauto : AUTOCONNECT '=' NO ';'",
"uworldblock : UWORLD '{' uworlditems '}' ';'",
"uworlditems : uworlditem uworlditems",
"uworlditems : uworlditem",
"uworlditem : uworldname",
"uworldname : NAME '=' QSTRING ';'",
"operblock : OPER '{' operitems '}' ';'",
"operitems : operitem",
"operitems : operitems operitem",
"operitem : opername",
"operitem : operpass",
"operitem : operhost",
"operitem : operclass",
"operitem : priv",
"opername : NAME '=' QSTRING ';'",
"operpass : PASS '=' QSTRING ';'",
"operhost : HOST '=' QSTRING ';'",
"operclass : CLASS '=' QSTRING ';'",
"priv : privtype '=' yesorno ';'",
"privtype : TPRIV_CHAN_LIMIT",
"privtype : TPRIV_MODE_LCHAN",
"privtype : TPRIV_DEOP_LCHAN",
"privtype : TPRIV_WALK_LCHAN",
"privtype : KILL",
"privtype : TPRIV_LOCAL_KILL",
"privtype : TPRIV_REHASH",
"privtype : TPRIV_RESTART",
"privtype : TPRIV_DIE",
"privtype : TPRIV_GLINE",
"privtype : TPRIV_LOCAL_GLINE",
"privtype : JUPE",
"privtype : TPRIV_LOCAL_JUPE",
"privtype : TPRIV_LOCAL_OPMODE",
"privtype : TPRIV_OPMODE",
"privtype : TPRIV_SET",
"privtype : TPRIV_WHOX",
"privtype : TPRIV_BADCHAN",
"privtype : TPRIV_LOCAL_BADCHAN",
"privtype : TPRIV_SEE_CHAN",
"privtype : TPRIV_SHOW_INVIS",
"privtype : TPRIV_SHOW_ALL_INVIS",
"privtype : TPRIV_PROPAGATE",
"privtype : TPRIV_UNLIMIT_QUERY",
"privtype : TPRIV_DISPLAY",
"privtype : TPRIV_SEE_OPERS",
"privtype : TPRIV_WIDE_GLINE",
"privtype : TPRIV_LIST_CHAN",
"privtype : LOCAL",
"privtype : TPRIV_FORCE_OPMODE",
"privtype : TPRIV_FORCE_LOCAL_OPMODE",
"privtype : TPRIV_APASS_OPMODE",
"yesorno : YES",
"yesorno : NO",
"address_family :",
"address_family : TOK_IPV4",
"address_family : TOK_IPV6",
"address_family : TOK_IPV4 TOK_IPV6",
"address_family : TOK_IPV6 TOK_IPV4",
"portblock : PORT '{' portitems '}' ';'",
"portitems : portitem portitems",
"portitems : portitem",
"portitem : portnumber",
"portitem : portvhost",
"portitem : portvhostnumber",
"portitem : portmask",
"portitem : portserver",
"portitem : porthidden",
"portnumber : PORT '=' address_family NUMBER ';'",
"portvhost : VHOST '=' address_family QSTRING ';'",
"portvhostnumber : VHOST '=' address_family QSTRING NUMBER ';'",
"portmask : MASK '=' QSTRING ';'",
"portserver : SERVER '=' YES ';'",
"portserver : SERVER '=' NO ';'",
"porthidden : HIDDEN '=' YES ';'",
"porthidden : HIDDEN '=' NO ';'",
"$$5 :",
"clientblock : CLIENT $$5 '{' clientitems '}' ';'",
"clientitems : clientitem clientitems",
"clientitems : clientitem",
"clientitem : clienthost",
"clientitem : clientip",
"clientitem : clientusername",
"clientitem : clientclass",
"clientitem : clientpass",
"clientitem : clientmaxlinks",
"clientitem : clientport",
"clienthost : HOST '=' QSTRING ';'",
"clientip : IP '=' QSTRING ';'",
"clientusername : USERNAME '=' QSTRING ';'",
"clientclass : CLASS '=' QSTRING ';'",
"clientpass : PASS '=' QSTRING ';'",
"clientmaxlinks : MAXLINKS '=' expr ';'",
"clientport : PORT '=' expr ';'",
"$$6 :",
"killblock : KILL $$6 '{' killitems '}' ';'",
"killitems : killitem killitems",
"killitems : killitem",
"killitem : killuhost",
"killitem : killreal",
"killitem : killusername",
"killitem : killreasonfile",
"killitem : killreason",
"killuhost : HOST '=' QSTRING ';'",
"killusername : USERNAME '=' QSTRING ';'",
"killreal : REAL '=' QSTRING ';'",
"killreason : REASON '=' QSTRING ';'",
"killreasonfile : TFILE '=' QSTRING ';'",
"$$7 :",
"cruleblock : CRULE $$7 '{' cruleitems '}' ';'",
"cruleitems : cruleitem cruleitems",
"cruleitems : cruleitem",
"cruleitem : cruleserver",
"cruleitem : crulerule",
"cruleitem : cruleall",
"cruleserver : SERVER '=' QSTRING ';'",
"crulerule : RULE '=' QSTRING ';'",
"cruleall : ALL '=' YES ';'",
"cruleall : ALL '=' NO ';'",
"motdblock : MOTD '{' motditems '}' ';'",
"motditems : motditem motditems",
"motditems : motditem",
"motditem : motdhost",
"motditem : motdfile",
"motdhost : HOST '=' QSTRING ';'",
"motdfile : TFILE '=' QSTRING ';'",
"featuresblock : FEATURES '{' featureitems '}' ';'",
"featureitems : featureitems featureitem",
"featureitems : featureitem",
"$$8 :",
"featureitem : QSTRING $$8 '=' stringlist ';'",
"stringlist : stringlist extrastring",
"stringlist : extrastring",
"extrastring : QSTRING",
"quarantineblock : QUARANTINE '{' quarantineitems '}' ';'",
"quarantineitems : quarantineitems quarantineitem",
"quarantineitems : quarantineitem",
"quarantineitem : QSTRING '=' QSTRING ';'",
"$$9 :",
"pseudoblock : PSEUDO QSTRING '{' $$9 pseudoitems '}' ';'",
"pseudoitems : pseudoitem pseudoitems",
"pseudoitems : pseudoitem",
"pseudoitem : pseudoname",
"pseudoitem : pseudoprepend",
"pseudoitem : pseudonick",
"pseudoitem : pseudoflags",
"pseudoname : NAME '=' QSTRING ';'",
"pseudoprepend : PREPEND '=' QSTRING ';'",
"pseudonick : NICK '=' QSTRING ';'",
"pseudoflags : FAST ';'",
"iauthblock : IAUTH '{' iauthitems '}' ';'",
"iauthitems : iauthitem iauthitems",
"iauthitems : iauthitem",
"iauthitem : iauthprogram",
"$$10 :",
"iauthprogram : PROGRAM '=' $$10 stringlist ';'",

};
#endif
/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (data->s_base != 0)
          ? (short *)realloc(data->s_base, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (data->l_base != 0)
          ? (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 22:
#line 212 "./ircd_parser.y"
	{
  yyval.num = yystack.l_mark[-1].num + yystack.l_mark[0].num;
}
break;
case 24:
#line 217 "./ircd_parser.y"
	{
  yyval.num = yystack.l_mark[-1].num * yystack.l_mark[0].num;
}
break;
case 25:
#line 221 "./ircd_parser.y"
	{ yyval.num = 1; }
break;
case 26:
#line 222 "./ircd_parser.y"
	{ yyval.num = 60; }
break;
case 27:
#line 223 "./ircd_parser.y"
	{ yyval.num = 60 * 60; }
break;
case 28:
#line 224 "./ircd_parser.y"
	{ yyval.num = 60 * 60 * 24; }
break;
case 29:
#line 225 "./ircd_parser.y"
	{ yyval.num = 60 * 60 * 24 * 7; }
break;
case 30:
#line 226 "./ircd_parser.y"
	{ yyval.num = 60 * 60 * 24 * 7 * 4; }
break;
case 31:
#line 227 "./ircd_parser.y"
	{ yyval.num = 60 * 60 * 24 * 365; }
break;
case 32:
#line 228 "./ircd_parser.y"
	{ yyval.num = 60 * 60 * 24 * 365 * 10; }
break;
case 33:
#line 231 "./ircd_parser.y"
	{
			yyval.num = yystack.l_mark[0].num;
		}
break;
case 34:
#line 234 "./ircd_parser.y"
	{ 
			yyval.num = yystack.l_mark[-1].num;
		}
break;
case 35:
#line 237 "./ircd_parser.y"
	{
			yyval.num = yystack.l_mark[-1].num * 1024;
		}
break;
case 36:
#line 240 "./ircd_parser.y"
	{
			yyval.num = yystack.l_mark[-1].num * 1024 * 1024;
		}
break;
case 37:
#line 243 "./ircd_parser.y"
	{
			yyval.num = yystack.l_mark[-1].num * 1024 * 1024 * 1024;
		}
break;
case 38:
#line 246 "./ircd_parser.y"
	{
			yyval.num = yystack.l_mark[-1].num * 1024 * 1024 * 1024;
		}
break;
case 39:
#line 253 "./ircd_parser.y"
	{ 
			yyval.num = yystack.l_mark[0].num;
		}
break;
case 40:
#line 256 "./ircd_parser.y"
	{ 
			yyval.num = yystack.l_mark[-2].num + yystack.l_mark[0].num;
		}
break;
case 41:
#line 259 "./ircd_parser.y"
	{ 
			yyval.num = yystack.l_mark[-2].num - yystack.l_mark[0].num;
		}
break;
case 42:
#line 262 "./ircd_parser.y"
	{ 
			yyval.num = yystack.l_mark[-2].num * yystack.l_mark[0].num;
		}
break;
case 43:
#line 265 "./ircd_parser.y"
	{ 
			yyval.num = yystack.l_mark[-2].num / yystack.l_mark[0].num;
		}
break;
case 44:
#line 272 "./ircd_parser.y"
	{
			yyval.num = yystack.l_mark[-1].num;
		}
break;
case 49:
#line 281 "./ircd_parser.y"
	{
  addNickJupes(yystack.l_mark[-1].text);
  MyFree(yystack.l_mark[-1].text);
}
break;
case 50:
#line 287 "./ircd_parser.y"
	{
    /* Zero out the vhost addresses, in case they were removed. */
    memset(&VirtualHost_v4.addr, 0, sizeof(VirtualHost_v4.addr));
    memset(&VirtualHost_v6.addr, 0, sizeof(VirtualHost_v6.addr));
}
break;
case 51:
#line 291 "./ircd_parser.y"
	{
  if (localConf.name == NULL)
    parse_error("Your General block must contain a name.");
  if (localConf.numeric == 0)
    parse_error("Your General block must contain a numeric (between 1 and 4095).");
}
break;
case 60:
#line 302 "./ircd_parser.y"
	{
  if (localConf.numeric == 0)
    localConf.numeric = yystack.l_mark[-1].num;
  else if (localConf.numeric != yystack.l_mark[-1].num)
    parse_error("Redefinition of server numeric %i (%i)", yystack.l_mark[-1].num,
    		localConf.numeric);
}
break;
case 61:
#line 311 "./ircd_parser.y"
	{
  if (localConf.name == NULL)
    localConf.name = yystack.l_mark[-1].text;
  else {
    if (strcmp(localConf.name, yystack.l_mark[-1].text))
      parse_error("Redefinition of server name %s (%s)", yystack.l_mark[-1].text,
                  localConf.name);
    MyFree(yystack.l_mark[-1].text);
  }
}
break;
case 62:
#line 323 "./ircd_parser.y"
	{
  MyFree(localConf.description);
  localConf.description = yystack.l_mark[-1].text;
  ircd_strncpy(cli_info(&me), yystack.l_mark[-1].text, REALLEN);
}
break;
case 63:
#line 330 "./ircd_parser.y"
	{
  struct irc_in_addr addr;
  char *vhost = yystack.l_mark[-1].text;

  if (!strcmp(vhost, "*")) {
    /* This traditionally meant bind to all interfaces and connect
     * from the default. */
  } else if (!ircd_aton(&addr, vhost))
    parse_error("Invalid virtual host '%s'.", vhost);
  else if (irc_in_addr_is_ipv4(&addr))
    memcpy(&VirtualHost_v4.addr, &addr, sizeof(addr));
  else
    memcpy(&VirtualHost_v6.addr, &addr, sizeof(addr));
  MyFree(vhost);
}
break;
case 64:
#line 347 "./ircd_parser.y"
	{
  struct irc_in_addr addr;
  int families = yystack.l_mark[-2].num;
  char *vhost = yystack.l_mark[-1].text;

  if (!strcmp(vhost, "*")) {
    /* Let the operating system assign the default. */
  } else if (!ircd_aton(&addr, vhost))
    parse_error("Invalid DNS virtual host '%s'.", vhost);
  else
  {
    if ((families & USE_IPV4)
        || (!families && irc_in_addr_is_ipv4(&addr)))
      memcpy(&VirtualHost_dns_v4.addr, &addr, sizeof(addr));
    if ((families & USE_IPV6)
        || (!families && !irc_in_addr_is_ipv4(&addr)))
      memcpy(&VirtualHost_dns_v6.addr, &addr, sizeof(addr));
  }
  MyFree(vhost);
}
break;
case 65:
#line 369 "./ircd_parser.y"
	{
  char *server = yystack.l_mark[-1].text;

  add_nameserver(server);
  MyFree(server);
}
break;
case 66:
#line 377 "./ircd_parser.y"
	{
  MyFree(localConf.location1);
  MyFree(localConf.location2);
  MyFree(localConf.contact);
  localConf.location1 = localConf.location2 = localConf.contact = NULL;
}
break;
case 67:
#line 384 "./ircd_parser.y"
	{
  if (localConf.location1 == NULL)
    DupString(localConf.location1, "");
  if (localConf.location2 == NULL)
    DupString(localConf.location2, "");
  if (localConf.contact == NULL)
    DupString(localConf.contact, "");
}
break;
case 72:
#line 395 "./ircd_parser.y"
	{
  if (localConf.location1 == NULL)
    localConf.location1 = yystack.l_mark[-1].text;
  else if (localConf.location2 == NULL)
    localConf.location2 = yystack.l_mark[-1].text;
  else /* Otherwise just drop it. -A1kmm */
    MyFree(yystack.l_mark[-1].text);
}
break;
case 73:
#line 404 "./ircd_parser.y"
	{
 MyFree(localConf.contact);
 localConf.contact = yystack.l_mark[-1].text;
}
break;
case 74:
#line 409 "./ircd_parser.y"
	{
  tping = 90;
}
break;
case 75:
#line 412 "./ircd_parser.y"
	{
  if (name != NULL)
  {
    struct ConnectionClass *c_class;
    add_class(name, tping, tconn, maxlinks, sendq);
    c_class = find_class(name);
    MyFree(c_class->default_umode);
    c_class->default_umode = pass;
    memcpy(&c_class->privs, &privs, sizeof(c_class->privs));
    memcpy(&c_class->privs_dirty, &privs_dirty, sizeof(c_class->privs_dirty));
  }
  else {
   parse_error("Missing name in class block");
  }
  name = NULL;
  pass = NULL;
  tconn = 0;
  maxlinks = 0;
  sendq = 0;
  memset(&privs, 0, sizeof(privs));
  memset(&privs_dirty, 0, sizeof(privs_dirty));
}
break;
case 85:
#line 438 "./ircd_parser.y"
	{
  MyFree(name);
  name = yystack.l_mark[-1].text;
}
break;
case 86:
#line 443 "./ircd_parser.y"
	{
  tping = yystack.l_mark[-1].num;
}
break;
case 87:
#line 447 "./ircd_parser.y"
	{
  tconn = yystack.l_mark[-1].num;
}
break;
case 88:
#line 451 "./ircd_parser.y"
	{
  maxlinks = yystack.l_mark[-1].num;
}
break;
case 89:
#line 455 "./ircd_parser.y"
	{
  sendq = yystack.l_mark[-1].num;
}
break;
case 90:
#line 459 "./ircd_parser.y"
	{
  MyFree(pass);
  pass = yystack.l_mark[-1].text;
}
break;
case 91:
#line 465 "./ircd_parser.y"
	{
 flags = CONF_AUTOCONNECT;
}
break;
case 92:
#line 468 "./ircd_parser.y"
	{
 struct ConfItem *aconf = NULL;
 if (name == NULL)
  parse_error("Missing name in connect block");
 else if (pass == NULL)
  parse_error("Missing password in connect block");
 else if (strlen(pass) > PASSWDLEN)
  parse_error("Password too long in connect block");
 else if (host == NULL)
  parse_error("Missing host in connect block");
 else if (strchr(host, '*') || strchr(host, '?'))
  parse_error("Invalid host '%s' in connect block", host);
 else if (c_class == NULL)
  parse_error("Missing or non-existent class in connect block");
 else {
   aconf = make_conf(CONF_SERVER);
   aconf->name = name;
   aconf->origin_name = origin;
   aconf->passwd = pass;
   aconf->conn_class = c_class;
   aconf->address.port = port;
   aconf->host = host;
   /* If the user specified a hub allowance, but not maximum links,
    * allow an effectively unlimited number of hops.
    */
   aconf->maximum = (hub_limit != NULL && maxlinks == 0) ? 65535 : maxlinks;
   aconf->hub_limit = hub_limit;
   aconf->flags = flags;
   lookup_confhost(aconf);
 }
 if (!aconf) {
   MyFree(name);
   MyFree(pass);
   MyFree(host);
   MyFree(origin);
   MyFree(hub_limit);
 }
 name = pass = host = origin = hub_limit = NULL;
 c_class = NULL;
 port = flags = maxlinks = 0;
}
break;
case 106:
#line 514 "./ircd_parser.y"
	{
 MyFree(name);
 name = yystack.l_mark[-1].text;
}
break;
case 107:
#line 519 "./ircd_parser.y"
	{
 MyFree(pass);
 pass = yystack.l_mark[-1].text;
}
break;
case 108:
#line 524 "./ircd_parser.y"
	{
 c_class = find_class(yystack.l_mark[-1].text);
 if (!c_class)
  parse_error("No such connection class '%s' for Connect block", yystack.l_mark[-1].text);
 MyFree(yystack.l_mark[-1].text);
}
break;
case 109:
#line 531 "./ircd_parser.y"
	{
 MyFree(host);
 host = yystack.l_mark[-1].text;
}
break;
case 110:
#line 536 "./ircd_parser.y"
	{
 port = yystack.l_mark[-1].num;
}
break;
case 111:
#line 540 "./ircd_parser.y"
	{
 MyFree(origin);
 origin = yystack.l_mark[-1].text;
}
break;
case 112:
#line 545 "./ircd_parser.y"
	{
 maxlinks = 0;
}
break;
case 113:
#line 549 "./ircd_parser.y"
	{
 MyFree(hub_limit);
 DupString(hub_limit, "*");
}
break;
case 114:
#line 554 "./ircd_parser.y"
	{
 MyFree(hub_limit);
 hub_limit = yystack.l_mark[-1].text;
}
break;
case 115:
#line 559 "./ircd_parser.y"
	{
  maxlinks = yystack.l_mark[-1].num;
}
break;
case 116:
#line 562 "./ircd_parser.y"
	{ flags |= CONF_AUTOCONNECT; }
break;
case 117:
#line 563 "./ircd_parser.y"
	{ flags &= ~CONF_AUTOCONNECT; }
break;
case 122:
#line 569 "./ircd_parser.y"
	{
  make_conf(CONF_UWORLD)->host = yystack.l_mark[-1].text;
}
break;
case 123:
#line 574 "./ircd_parser.y"
	{
  struct ConfItem *aconf = NULL;
  struct SLink *link;

  if (name == NULL)
    parse_error("Missing name in operator block");
  else if (pass == NULL)
    parse_error("Missing password in operator block");
  /* Do not check password length because it may be crypted. */
  else if (hosts == NULL)
    parse_error("Missing host(s) in operator block");
  else if (c_class == NULL)
    parse_error("Invalid or missing class in operator block");
  else if (!FlagHas(&privs_dirty, PRIV_PROPAGATE)
           && !FlagHas(&c_class->privs_dirty, PRIV_PROPAGATE))
    parse_error("Operator block for %s and class %s have no LOCAL setting", name, c_class->cc_name);
  else for (link = hosts; link != NULL; link = link->next) {
    aconf = make_conf(CONF_OPERATOR);
    DupString(aconf->name, name);
    DupString(aconf->passwd, pass);
    conf_parse_userhost(aconf, link->value.cp);
    aconf->conn_class = c_class;
    memcpy(&aconf->privs, &privs, sizeof(aconf->privs));
    memcpy(&aconf->privs_dirty, &privs_dirty, sizeof(aconf->privs_dirty));
  }
  MyFree(name);
  MyFree(pass);
  free_slist(&hosts);
  name = pass = NULL;
  c_class = NULL;
  memset(&privs, 0, sizeof(privs));
  memset(&privs_dirty, 0, sizeof(privs_dirty));
}
break;
case 131:
#line 610 "./ircd_parser.y"
	{
  MyFree(name);
  name = yystack.l_mark[-1].text;
}
break;
case 132:
#line 615 "./ircd_parser.y"
	{
  MyFree(pass);
  pass = yystack.l_mark[-1].text;
}
break;
case 133:
#line 620 "./ircd_parser.y"
	{
 struct SLink *link;
 link = make_link();
 if (!strchr(yystack.l_mark[-1].text, '@'))
 {
   int uh_len;
   link->value.cp = (char*) MyMalloc((uh_len = strlen(yystack.l_mark[-1].text)+3));
   ircd_snprintf(0, link->value.cp, uh_len, "*@%s", yystack.l_mark[-1].text);
 }
 else
   DupString(link->value.cp, yystack.l_mark[-1].text);
 MyFree(yystack.l_mark[-1].text);
 link->next = hosts;
 hosts = link;
}
break;
case 134:
#line 636 "./ircd_parser.y"
	{
 c_class = find_class(yystack.l_mark[-1].text);
 if (!c_class)
  parse_error("No such connection class '%s' for Operator block", yystack.l_mark[-1].text);
 MyFree(yystack.l_mark[-1].text);
}
break;
case 135:
#line 644 "./ircd_parser.y"
	{
  FlagSet(&privs_dirty, yystack.l_mark[-3].num);
  if ((yystack.l_mark[-1].num == 1) ^ invert)
    FlagSet(&privs, yystack.l_mark[-3].num);
  else
    FlagClr(&privs, yystack.l_mark[-3].num);
  invert = 0;
}
break;
case 136:
#line 653 "./ircd_parser.y"
	{ yyval.num = PRIV_CHAN_LIMIT; }
break;
case 137:
#line 654 "./ircd_parser.y"
	{ yyval.num = PRIV_MODE_LCHAN; }
break;
case 138:
#line 655 "./ircd_parser.y"
	{ yyval.num = PRIV_DEOP_LCHAN; }
break;
case 139:
#line 656 "./ircd_parser.y"
	{ yyval.num = PRIV_WALK_LCHAN; }
break;
case 140:
#line 657 "./ircd_parser.y"
	{ yyval.num = PRIV_KILL; }
break;
case 141:
#line 658 "./ircd_parser.y"
	{ yyval.num = PRIV_LOCAL_KILL; }
break;
case 142:
#line 659 "./ircd_parser.y"
	{ yyval.num = PRIV_REHASH; }
break;
case 143:
#line 660 "./ircd_parser.y"
	{ yyval.num = PRIV_RESTART; }
break;
case 144:
#line 661 "./ircd_parser.y"
	{ yyval.num = PRIV_DIE; }
break;
case 145:
#line 662 "./ircd_parser.y"
	{ yyval.num = PRIV_GLINE; }
break;
case 146:
#line 663 "./ircd_parser.y"
	{ yyval.num = PRIV_LOCAL_GLINE; }
break;
case 147:
#line 664 "./ircd_parser.y"
	{ yyval.num = PRIV_JUPE; }
break;
case 148:
#line 665 "./ircd_parser.y"
	{ yyval.num = PRIV_LOCAL_JUPE; }
break;
case 149:
#line 666 "./ircd_parser.y"
	{ yyval.num = PRIV_LOCAL_OPMODE; }
break;
case 150:
#line 667 "./ircd_parser.y"
	{ yyval.num = PRIV_OPMODE; }
break;
case 151:
#line 668 "./ircd_parser.y"
	{ yyval.num = PRIV_SET; }
break;
case 152:
#line 669 "./ircd_parser.y"
	{ yyval.num = PRIV_WHOX; }
break;
case 153:
#line 670 "./ircd_parser.y"
	{ yyval.num = PRIV_BADCHAN; }
break;
case 154:
#line 671 "./ircd_parser.y"
	{ yyval.num = PRIV_LOCAL_BADCHAN; }
break;
case 155:
#line 672 "./ircd_parser.y"
	{ yyval.num = PRIV_SEE_CHAN; }
break;
case 156:
#line 673 "./ircd_parser.y"
	{ yyval.num = PRIV_SHOW_INVIS; }
break;
case 157:
#line 674 "./ircd_parser.y"
	{ yyval.num = PRIV_SHOW_ALL_INVIS; }
break;
case 158:
#line 675 "./ircd_parser.y"
	{ yyval.num = PRIV_PROPAGATE; }
break;
case 159:
#line 676 "./ircd_parser.y"
	{ yyval.num = PRIV_UNLIMIT_QUERY; }
break;
case 160:
#line 677 "./ircd_parser.y"
	{ yyval.num = PRIV_DISPLAY; }
break;
case 161:
#line 678 "./ircd_parser.y"
	{ yyval.num = PRIV_SEE_OPERS; }
break;
case 162:
#line 679 "./ircd_parser.y"
	{ yyval.num = PRIV_WIDE_GLINE; }
break;
case 163:
#line 680 "./ircd_parser.y"
	{ yyval.num = PRIV_LIST_CHAN; }
break;
case 164:
#line 681 "./ircd_parser.y"
	{ yyval.num = PRIV_PROPAGATE; invert = 1; }
break;
case 165:
#line 682 "./ircd_parser.y"
	{ yyval.num = PRIV_FORCE_OPMODE; }
break;
case 166:
#line 683 "./ircd_parser.y"
	{ yyval.num = PRIV_FORCE_LOCAL_OPMODE; }
break;
case 167:
#line 684 "./ircd_parser.y"
	{ yyval.num = PRIV_APASS_OPMODE; }
break;
case 168:
#line 686 "./ircd_parser.y"
	{ yyval.num = 1; }
break;
case 169:
#line 686 "./ircd_parser.y"
	{ yyval.num = 0; }
break;
case 170:
#line 692 "./ircd_parser.y"
	{ yyval.num = 0; }
break;
case 171:
#line 693 "./ircd_parser.y"
	{ yyval.num = USE_IPV4; }
break;
case 172:
#line 694 "./ircd_parser.y"
	{ yyval.num = USE_IPV6; }
break;
case 173:
#line 695 "./ircd_parser.y"
	{ yyval.num = USE_IPV4 | USE_IPV6; }
break;
case 174:
#line 696 "./ircd_parser.y"
	{ yyval.num = USE_IPV6 | USE_IPV4; }
break;
case 175:
#line 700 "./ircd_parser.y"
	{
  struct ListenerFlags flags_here;
  struct SLink *link;
  if (hosts == NULL) {
    struct SLink *link;
    link = make_link();
    DupString(link->value.cp, "*");
    link->flags = 0;
    link->next = hosts;
    hosts = link;
  }
  for (link = hosts; link != NULL; link = link->next) {
    memcpy(&flags_here, &listen_flags, sizeof(&flags_here));
    switch (link->flags & (USE_IPV4 | USE_IPV6)) {
    case USE_IPV4:
      FlagSet(&flags_here, LISTEN_IPV4);
      break;
    case USE_IPV6:
      FlagSet(&flags_here, LISTEN_IPV6);
      break;
    default: /* 0 or USE_IPV4|USE_IPV6 */
      FlagSet(&flags_here, LISTEN_IPV4);
      FlagSet(&flags_here, LISTEN_IPV6);
      break;
    }
    if (link->flags & 65535)
      port = link->flags & 65535;
    add_listener(port, link->value.cp, pass, &flags_here);
  }
  free_slist(&hosts);
  MyFree(pass);
  memset(&listen_flags, 0, sizeof(listen_flags));
  pass = NULL;
  port = 0;
}
break;
case 184:
#line 738 "./ircd_parser.y"
	{
  if (yystack.l_mark[-1].num < 1 || yystack.l_mark[-1].num > 65535) {
    parse_error("Port %d is out of range", port);
  } else {
    port = yystack.l_mark[-2].num | yystack.l_mark[-1].num;
    if (hosts && (0 == (hosts->flags & 65535)))
      hosts->flags = (hosts->flags & ~65535) | port;
  }
}
break;
case 185:
#line 749 "./ircd_parser.y"
	{
  struct SLink *link;
  link = make_link();
  link->value.cp = yystack.l_mark[-1].text;
  link->flags = yystack.l_mark[-2].num | port;
  link->next = hosts;
  hosts = link;
}
break;
case 186:
#line 759 "./ircd_parser.y"
	{
  if (yystack.l_mark[-1].num < 1 || yystack.l_mark[-1].num > 65535) {
    parse_error("Port %d is out of range", port);
  } else {
    struct SLink *link;
    link = make_link();
    link->value.cp = yystack.l_mark[-2].text;
    link->flags = yystack.l_mark[-3].num | yystack.l_mark[-1].num;
    link->next = hosts;
    hosts = link;
  }
}
break;
case 187:
#line 773 "./ircd_parser.y"
	{
  MyFree(pass);
  pass = yystack.l_mark[-1].text;
}
break;
case 188:
#line 779 "./ircd_parser.y"
	{
  FlagSet(&listen_flags, LISTEN_SERVER);
}
break;
case 189:
#line 782 "./ircd_parser.y"
	{
  FlagClr(&listen_flags, LISTEN_SERVER);
}
break;
case 190:
#line 787 "./ircd_parser.y"
	{
  FlagSet(&listen_flags, LISTEN_HIDDEN);
}
break;
case 191:
#line 790 "./ircd_parser.y"
	{
  FlagClr(&listen_flags, LISTEN_HIDDEN);
}
break;
case 192:
#line 795 "./ircd_parser.y"
	{
  maxlinks = 65535;
  port = 0;
}
break;
case 193:
#line 800 "./ircd_parser.y"
	{
  struct ConfItem *aconf = 0;
  struct irc_in_addr addr;
  unsigned char addrbits = 0;

  if (!c_class)
    parse_error("Invalid or missing class in Client block");
  else if (pass && strlen(pass) > PASSWDLEN)
    parse_error("Password too long in connect block");
  else if (ip && !ipmask_parse(ip, &addr, &addrbits))
    parse_error("Invalid IP address %s in Client block", ip);
  else {
    aconf = make_conf(CONF_CLIENT);
    aconf->username = username;
    aconf->host = host;
    if (ip)
      memcpy(&aconf->address.addr, &addr, sizeof(aconf->address.addr));
    else
      memset(&aconf->address.addr, 0, sizeof(aconf->address.addr));
    aconf->address.port = port;
    aconf->addrbits = addrbits;
    aconf->name = ip;
    aconf->conn_class = c_class;
    aconf->maximum = maxlinks;
    aconf->passwd = pass;
  }
  if (!aconf) {
    MyFree(username);
    MyFree(host);
    MyFree(ip);
    MyFree(pass);
  }
  host = NULL;
  username = NULL;
  c_class = NULL;
  maxlinks = 0;
  ip = NULL;
  pass = NULL;
  port = 0;
}
break;
case 203:
#line 843 "./ircd_parser.y"
	{
  char *sep = strchr(yystack.l_mark[-1].text, '@');
  MyFree(host);
  if (sep) {
    *sep++ = '\0';
    MyFree(username);
    DupString(host, sep);
    username = yystack.l_mark[-1].text;
  } else {
    host = yystack.l_mark[-1].text;
  }
}
break;
case 204:
#line 856 "./ircd_parser.y"
	{
  char *sep;
  sep = strchr(yystack.l_mark[-1].text, '@');
  MyFree(ip);
  if (sep) {
    *sep++ = '\0';
    MyFree(username);
    DupString(ip, sep);
    username = yystack.l_mark[-1].text;
  } else {
    ip = yystack.l_mark[-1].text;
  }
}
break;
case 205:
#line 870 "./ircd_parser.y"
	{
  MyFree(username);
  username = yystack.l_mark[-1].text;
}
break;
case 206:
#line 875 "./ircd_parser.y"
	{
  c_class = find_class(yystack.l_mark[-1].text);
  if (!c_class)
    parse_error("No such connection class '%s' for Client block", yystack.l_mark[-1].text);
  MyFree(yystack.l_mark[-1].text);
}
break;
case 207:
#line 882 "./ircd_parser.y"
	{
  MyFree(pass);
  pass = yystack.l_mark[-1].text;
}
break;
case 208:
#line 887 "./ircd_parser.y"
	{
  maxlinks = yystack.l_mark[-1].num;
}
break;
case 209:
#line 891 "./ircd_parser.y"
	{
  port = yystack.l_mark[-1].num;
}
break;
case 210:
#line 896 "./ircd_parser.y"
	{
  dconf = (struct DenyConf*) MyCalloc(1, sizeof(*dconf));
}
break;
case 211:
#line 899 "./ircd_parser.y"
	{
  if (dconf->usermask || dconf->hostmask ||dconf->realmask) {
    dconf->next = denyConfList;
    denyConfList = dconf;
  }
  else
  {
    MyFree(dconf->usermask);
    MyFree(dconf->hostmask);
    MyFree(dconf->realmask);
    MyFree(dconf->message);
    MyFree(dconf);
    parse_error("Kill block must match on at least one of username, host or realname");
  }
  dconf = NULL;
}
break;
case 219:
#line 918 "./ircd_parser.y"
	{
  char *h;
  MyFree(dconf->hostmask);
  MyFree(dconf->usermask);
  if ((h = strchr(yystack.l_mark[-1].text, '@')) == NULL)
  {
    DupString(dconf->usermask, "*");
    dconf->hostmask = yystack.l_mark[-1].text;
  }
  else
  {
    *h++ = '\0';
    DupString(dconf->hostmask, h);
    dconf->usermask = yystack.l_mark[-1].text;
  }
  ipmask_parse(dconf->hostmask, &dconf->address, &dconf->bits);
}
break;
case 220:
#line 937 "./ircd_parser.y"
	{
  MyFree(dconf->usermask);
  dconf->usermask = yystack.l_mark[-1].text;
}
break;
case 221:
#line 943 "./ircd_parser.y"
	{
 MyFree(dconf->realmask);
 dconf->realmask = yystack.l_mark[-1].text;
}
break;
case 222:
#line 949 "./ircd_parser.y"
	{
 dconf->flags &= ~DENY_FLAGS_FILE;
 MyFree(dconf->message);
 dconf->message = yystack.l_mark[-1].text;
}
break;
case 223:
#line 956 "./ircd_parser.y"
	{
 dconf->flags |= DENY_FLAGS_FILE;
 MyFree(dconf->message);
 dconf->message = yystack.l_mark[-1].text;
}
break;
case 224:
#line 963 "./ircd_parser.y"
	{
  tconn = CRULE_AUTO;
}
break;
case 225:
#line 966 "./ircd_parser.y"
	{
  struct CRuleNode *node = NULL;
  struct SLink *link;

  if (hosts == NULL)
    parse_error("Missing server(s) in crule block");
  else if (pass == NULL)
    parse_error("Missing rule in crule block");
  else if ((node = crule_parse(pass)) == NULL)
    parse_error("Invalid rule '%s' in crule block", pass);
  else for (link = hosts; link != NULL; link = link->next)
  {
    struct CRuleConf *p = (struct CRuleConf*) MyMalloc(sizeof(*p));
    if (node == NULL)
      node = crule_parse(pass);
    DupString(p->hostmask, link->value.cp);
    DupString(p->rule, pass);
    p->type = tconn;
    p->node = node;
    node = NULL;
    p->next = cruleConfList;
    cruleConfList = p;
  }
  free_slist(&hosts);
  MyFree(pass);
  pass = NULL;
  tconn = 0;
}
break;
case 231:
#line 999 "./ircd_parser.y"
	{
  struct SLink *link;
  link = make_link();
  link->value.cp = yystack.l_mark[-1].text;
  link->next = hosts;
  hosts = link;
}
break;
case 232:
#line 1008 "./ircd_parser.y"
	{
 MyFree(pass);
 pass = yystack.l_mark[-1].text;
}
break;
case 233:
#line 1014 "./ircd_parser.y"
	{
 tconn = CRULE_ALL;
}
break;
case 234:
#line 1017 "./ircd_parser.y"
	{
 tconn = CRULE_AUTO;
}
break;
case 235:
#line 1022 "./ircd_parser.y"
	{
  struct SLink *link;
  if (pass != NULL)
    for (link = hosts; link != NULL; link = link->next)
      motd_add(link->value.cp, pass);
  free_slist(&hosts);
  MyFree(pass);
  pass = NULL;
}
break;
case 240:
#line 1035 "./ircd_parser.y"
	{
  struct SLink *link;
  link = make_link();
  link->value.cp = yystack.l_mark[-1].text;
  link->next = hosts;
  hosts = link;
}
break;
case 241:
#line 1044 "./ircd_parser.y"
	{
  MyFree(pass);
  pass = yystack.l_mark[-1].text;
}
break;
case 245:
#line 1053 "./ircd_parser.y"
	{
  stringlist[0] = yystack.l_mark[0].text;
  stringno = 1;
}
break;
case 246:
#line 1056 "./ircd_parser.y"
	{
  unsigned int ii;
  feature_set(NULL, (const char * const *)stringlist, stringno);
  for (ii = 0; ii < stringno; ++ii)
    MyFree(stringlist[ii]);
}
break;
case 249:
#line 1065 "./ircd_parser.y"
	{
  if (stringno < MAX_STRINGS)
    stringlist[stringno++] = yystack.l_mark[0].text;
  else
    MyFree(yystack.l_mark[0].text);
}
break;
case 253:
#line 1075 "./ircd_parser.y"
	{
  struct qline *qconf = MyCalloc(1, sizeof(*qconf));
  qconf->chname = yystack.l_mark[-3].text;
  qconf->reason = yystack.l_mark[-1].text;
  qconf->next = GlobalQuarantineList;
  GlobalQuarantineList = qconf;
}
break;
case 254:
#line 1084 "./ircd_parser.y"
	{
  smap = MyCalloc(1, sizeof(struct s_map));
  smap->command = yystack.l_mark[-1].text;
}
break;
case 255:
#line 1089 "./ircd_parser.y"
	{
  int valid = 0;

  if (!smap->name)
    parse_error("Missing name in pseudo %s block", smap->command);
  else if (!smap->services)
    parse_error("Missing nick in pseudo %s block", smap->command);
  else if (!strIsAlpha(smap->command))
    parse_error("Pseudo command %s invalid: must all be letters", smap->command);
  else
    valid = 1;
  if (valid && register_mapping(smap))
  {
    smap->next = GlobalServiceMapList;
    GlobalServiceMapList = smap;
  }
  else
  {
    free_mapping(smap);
  }
  smap = NULL;
}
break;
case 262:
#line 1115 "./ircd_parser.y"
	{
  MyFree(smap->name);
  smap->name = yystack.l_mark[-1].text;
}
break;
case 263:
#line 1120 "./ircd_parser.y"
	{
  MyFree(smap->prepend);
  smap->prepend = yystack.l_mark[-1].text;
}
break;
case 264:
#line 1125 "./ircd_parser.y"
	{
  char *sep = strchr(yystack.l_mark[-1].text, '@');

  if (sep != NULL) {
    size_t slen = strlen(yystack.l_mark[-1].text);
    struct nick_host *nh = MyMalloc(sizeof(*nh) + slen);
    memcpy(nh->nick, yystack.l_mark[-1].text, slen + 1);
    nh->nicklen = sep - yystack.l_mark[-1].text;
    nh->next = smap->services;
    smap->services = nh;
  }
  MyFree(yystack.l_mark[-1].text);
}
break;
case 265:
#line 1139 "./ircd_parser.y"
	{
  smap->flags |= SMAP_FAST;
}
break;
case 266:
#line 1144 "./ircd_parser.y"
	{
  auth_spawn(stringno, stringlist);
  while (stringno > 0)
  {
    --stringno;
    MyFree(stringlist[stringno]);
  }
}
break;
case 270:
#line 1156 "./ircd_parser.y"
	{
  while (stringno > 0)
  {
    --stringno;
    MyFree(stringlist[stringno]);
  }
}
break;
#line 2383 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
