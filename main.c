#include <stdlib.h>
#include <signal.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#include "logging.h"
#include "actors-registry.h"
#include "actors-network.h"
#include "actors-parser.h"

extern const ActorClass ActorClass_art_Sink_bin;
extern const ActorClass ActorClass_art_Sink_real;
extern const ActorClass ActorClass_art_Sink_txt;

extern const ActorClass ActorClass_art_Source_bin;
extern const ActorClass ActorClass_art_Source_real;
extern const ActorClass ActorClass_art_Source_txt;

#ifdef CALVIN_DISPLAY_SUPPORT
extern const ActorClass ActorClass_art_Display_yuv;
#else
#warning Not adding support for display actor
#endif /* CALVIN_DISPLAY_SUPPORT */


static void
sig_handler(int signum)
{
  exit(0);
}

/* ------------------------------------------------------------------------- */

static void
usage(const char *bname)
{
  printf(GREEN "usage: %s [-i] [-v] [script1.cs script2.cs ... scriptN.cs]\n"
       "  Named scripts are executed in sequence. Other options:\n"
       "  -i        : start interactive interpreter\n"
       "  -s <port> : start command server at given port " RESET "\n",
       bname);
  exit(0);
}


int
main(int argc, char **argv)
{
  int interactive = 0;
  short port = 0;
  int opt;

  signal(1, &sig_handler);


  while ((opt = getopt(argc, argv, "p:s:i")) != -1) {
    switch (opt) {
      case 'i':
        interactive = 1;
        break;
      case 's': /* FALLTHROUGH */
      case 'p':
        port = atoi(optarg);
        break;
      default: /* '?' */
        usage(basename(argv[0]));
    }
  }


  registryInit();
  initActorNetwork();

  /* Built-in system actors */

  registryAddClass(&ActorClass_art_Sink_bin);
  registryAddClass(&ActorClass_art_Sink_real);
  registryAddClass(&ActorClass_art_Sink_txt);

  registryAddClass(&ActorClass_art_Source_bin);
  registryAddClass(&ActorClass_art_Source_real);
  registryAddClass(&ActorClass_art_Source_txt);

#ifdef CALVIN_DISPLAY_SUPPORT
  registryAddClass(&ActorClass_art_Display_yuv);
#endif /* CALVIN_DISPLAY_SUPPORT */

  if (port != 0) {
    spawnServer(port);
    /* Wait for it */
    select(0, NULL, NULL, NULL, NULL);
  } else if (interactive) {
    parseInteractively();
  } else {
    /* execute each named file in non-interactive mode */
    while (optind < argc) {
      parseFile(argv[optind++]);
    }
  }

  return 0;
}

