/* Serial interface for a pipe to a separate program
   Copyright (C) 1999, 2000, 2001, 2007, 2008, 2009, 2010
   Free Software Foundation, Inc.

   Contributed by Cygnus Solutions.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "defs.h"
#include "serial.h"
#include "ser-base.h"
#include "ser-unix.h"

#include "gdb_vfork.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include "gdb_string.h"

#include <signal.h>

static int pipe_open (struct serial *scb, const char *name);
static void pipe_close (struct serial *scb);

extern void _initialize_ser_pipe (void);

struct pipe_state
  {
    int pid;
  };

/* Open up a raw pipe */

static int
pipe_open (struct serial *scb, const char *name)
{
#if !HAVE_SOCKETPAIR
  return -1;
#else
  struct pipe_state *state;
  /* This chunk: */
  /* Copyright (c) 1988, 1993
   *      The Regents of the University of California.  All rights reserved.
   *
   * This code is derived from software written by Ken Arnold and
   * published in UNIX Review, Vol. 6, No. 8.
   */
  int pdes[2];
  int err_pdes[2];
  int pid;

  if (socketpair (AF_UNIX, SOCK_STREAM, 0, pdes) < 0)
    return -1;
  if (socketpair (AF_UNIX, SOCK_STREAM, 0, err_pdes) < 0)
    {
      close (pdes[0]);
      close (pdes[1]);
      return -1;
    }

  /* Create the child process to run the command in.  Note that the
     apparent call to vfork() below *might* actually be a call to
     fork() due to the fact that autoconf will ``#define vfork fork''
     on certain platforms.  */
  pid = vfork ();
  
  /* Error. */
  if (pid == -1)
    {
      close (pdes[0]);
      close (pdes[1]);
      close (err_pdes[0]);
      close (err_pdes[1]);
      return -1;
    }

  if (fcntl (err_pdes[0], F_SETFL, O_NONBLOCK) == -1)
    {
      close (err_pdes[0]);
      close (err_pdes[1]);
      err_pdes[0] = err_pdes[1] = -1;
    }

  /* Child. */
  if (pid == 0)
    {
      /* We don't want ^c to kill the connection.  */
#ifdef HAVE_SETSID
      pid_t sid = setsid ();
      if (sid == -1)
	signal (SIGINT, SIG_IGN);
#else
      signal (SIGINT, SIG_IGN);
#endif

      /* re-wire pdes[1] to stdin/stdout */
      close (pdes[0]);
      if (pdes[1] != STDOUT_FILENO)
	{
	  dup2 (pdes[1], STDOUT_FILENO);
	  close (pdes[1]);
	}
      dup2 (STDOUT_FILENO, STDIN_FILENO);

      if (err_pdes[0] != -1)
	{
	  close (err_pdes[0]);
	  dup2 (err_pdes[1], STDERR_FILENO);
	  close (err_pdes[1]);
	}
#if 0
      /* close any stray FD's - FIXME - how? */
      /* POSIX.2 B.3.2.2 "popen() shall ensure that any streams
         from previous popen() calls that remain open in the 
         parent process are closed in the new child process. */
      for (old = pidlist; old; old = old->next)
	close (fileno (old->fp));	/* don't allow a flush */
#endif
      execl ("/bin/sh", "sh", "-c", name, (char *) 0);
      _exit (127);
    }

  /* Parent. */
  close (pdes[1]);
  if (err_pdes[1] != -1)
    close (err_pdes[1]);
  /* :end chunk */
  state = XMALLOC (struct pipe_state);
  state->pid = pid;
  scb->fd = pdes[0];
  scb->error_fd = err_pdes[0];
  scb->state = state;

  /* If we don't do this, GDB simply exits when the remote side dies.  */
  signal (SIGPIPE, SIG_IGN);
  return 0;
#endif
}

static void
pipe_close (struct serial *scb)
{
  struct pipe_state *state = scb->state;

  if (state != NULL)
    {
      int pid = state->pid;
      close (scb->fd);
      scb->fd = -1;
      if (scb->error_fd != -1)
	close (scb->error_fd);
      scb->error_fd = -1;
      xfree (state);
      scb->state = NULL;
      kill (pid, SIGTERM);
      /* Might be useful to check that the child does die,
	 and while we're waiting for it to die print any remaining
	 stderr output.  */
    }
}

void
_initialize_ser_pipe (void)
{
  struct serial_ops *ops = XMALLOC (struct serial_ops);

  memset (ops, 0, sizeof (struct serial_ops));
  ops->name = "pipe";
  ops->next = 0;
  ops->open = pipe_open;
  ops->close = pipe_close;
  ops->readchar = ser_base_readchar;
  ops->write = ser_base_write;
  ops->flush_output = ser_base_flush_output;
  ops->flush_input = ser_base_flush_input;
  ops->send_break = ser_base_send_break;
  ops->go_raw = ser_base_raw;
  ops->get_tty_state = ser_base_get_tty_state;
  ops->copy_tty_state = ser_base_copy_tty_state;
  ops->set_tty_state = ser_base_set_tty_state;
  ops->print_tty_state = ser_base_print_tty_state;
  ops->noflush_set_tty_state = ser_base_noflush_set_tty_state;
  ops->setbaudrate = ser_base_setbaudrate;
  ops->setstopbits = ser_base_setstopbits;
  ops->drain_output = ser_base_drain_output;
  ops->async = ser_base_async;
  ops->read_prim = ser_unix_read_prim;
  ops->write_prim = ser_unix_write_prim;
  serial_add_interface (ops);
}
