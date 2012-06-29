/*
 * IRC - Internet Relay Chat, ircd/m_version.c
 * Copyright (C) 1990 Jarkko Oikarinen and
 *                    University of Oulu, Computing Center
 *
 * See file AUTHORS in IRC package for additional names of
 * the programmers.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id$
 */

/*
 * m_functions execute protocol messages on this server:
 *
 *    cptr    is always NON-NULL, pointing to a *LOCAL* client
 *            structure (with an open socket connected!). This
 *            identifies the physical socket where the message
 *            originated (or which caused the m_function to be
 *            executed--some m_functions may call others...).
 *
 *    sptr    is the source of the message, defined by the
 *            prefix part of the message if present. If not
 *            or prefix not found, then sptr==cptr.
 *
 *            (!IsServer(cptr)) => (cptr == sptr), because
 *            prefixes are taken *only* from servers...
 *
 *            (IsServer(cptr))
 *                    (sptr == cptr) => the message didn't
 *                    have the prefix.
 *
 *                    (sptr != cptr && IsServer(sptr) means
 *                    the prefix specified servername. (?)
 *
 *                    (sptr != cptr && !IsServer(sptr) means
 *                    that message originated from a remote
 *                    user (not local).
 *
 *            combining
 *
 *            (!IsServer(sptr)) means that, sptr can safely
 *            taken as defining the target structure of the
 *            message in this server.
 *
 *    *Always* true (if 'parse' and others are working correct):
 *
 *    1)      sptr->from == cptr  (note: cptr->from == cptr)
 *
 *    2)      MyConnect(sptr) <=> sptr == cptr (e.g. sptr
 *            *cannot* be a local connection, unless it's
 *            actually cptr!). [MyConnect(x) should probably
 *            be defined as (x == x->from) --msa ]
 *
 *    parc    number of variable parameter strings (if zero,
 *            parv is allowed to be NULL)
 *
 *    parv    a NULL terminated list of parameter pointers,
 *
 *                    parv[0], sender (prefix string), if not present
 *                            this points to an empty string.
 *                    parv[1]...parv[parc-1]
 *                            pointers to additional parameters
 *                    parv[parc] == NULL, *always*
 *
 *            note:   it is guaranteed that parv[0]..parv[parc-1] are all
 *                    non-NULL pointers.
 */
#include "config.h"

#include "client.h"
#include "hash.h"
#include "ircd.h"
#include "ircd_features.h"
#include "ircd_log.h"
#include "ircd_reply.h"
#include "ircd_snprintf.h"
#include "ircd_string.h"
#include "match.h"
#include "msg.h"
#include "numeric.h"
#include "numnicks.h"
#include "s_debug.h"
#include "s_user.h"
#include "send.h"
#include "supported.h"
#include "version.h"

/* #include <assert.h> -- Now using assert in ircd_log.h */

/*
 * m_version - generic message handler
 *
 *   parv[0] = sender prefix
 *   parv[1] = servername
 */
int m_version(struct Client* cptr, struct Client* sptr, int parc, char* parv[])
{
  if (parc > 1 && match(parv[1], cli_name(&me)))
    return send_reply(sptr, ERR_NOPRIVILEGES);

  send_reply(sptr, RPL_VERSION, version, debugmode, cli_name(&me),
             debug_serveropts());
  send_supported(sptr);
  return 0;
}

/*
 * mo_version - oper message handler
 *
 *   parv[0] = sender prefix
 *   parv[1] = servername
 */
int mo_version(struct Client* cptr, struct Client* sptr, int parc, char* parv[])
{
  struct Client *acptr;

  if (MyConnect(sptr) && parc > 1)
  {
    if (!(acptr = find_match_server(parv[1])))
    {
      send_reply(sptr, ERR_NOSUCHSERVER, parv[1]);
      return 0;
    }
    parv[1] = cli_name(acptr);
  }

  if (hunt_server_cmd(sptr, CMD_VERSION, cptr, feature_int(FEAT_HIS_REMOTE),
                                                           ":%C", 1,
                                                           parc, parv)
                      == HUNTED_ISME)
  {
    send_reply(sptr, RPL_VERSION, version, debugmode, cli_name(&me),
	       debug_serveropts());
    send_supported(sptr);
  }

  return 0;
}

/*
 * ms_version - server message handler
 *
 *   parv[0] = sender prefix
 *   parv[1] = servername
 */
int ms_version(struct Client* cptr, struct Client* sptr, int parc, char* parv[])
{
  struct Client *acptr;

  if (MyConnect(sptr) && parc > 1)
  {
    if (!(acptr = find_match_server(parv[1])))
    {
      send_reply(sptr, ERR_NOSUCHSERVER, parv[1]);
      return 0;
    }
    parv[1] = cli_name(acptr);
  }

  if (hunt_server_cmd(sptr, CMD_VERSION, cptr, 0, ":%C", 1, parc, parv) ==
      HUNTED_ISME)
  {
    send_reply(sptr, RPL_VERSION, version, debugmode, cli_name(&me),
	       debug_serveropts());
  }

  return 0;
}
