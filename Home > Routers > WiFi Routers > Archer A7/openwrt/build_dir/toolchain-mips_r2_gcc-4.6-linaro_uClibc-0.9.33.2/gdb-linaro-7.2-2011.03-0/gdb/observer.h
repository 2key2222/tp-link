/* GDB Notifications to Observers.

   Copyright (C) 2004, 2005, 2007, 2008, 2009, 2010
   Free Software Foundation, Inc.

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   --

   This file was generated using observer.sh and observer.texi.  */

#ifndef OBSERVER_H
#define OBSERVER_H

struct observer;
struct bpstats;
struct so_list;
struct objfile;
struct thread_info;

/* normal_stop notifications.  */

typedef void (observer_normal_stop_ftype) (struct bpstats *bs, int print_frame);

extern struct observer *observer_attach_normal_stop (observer_normal_stop_ftype *f);
extern void observer_detach_normal_stop (struct observer *observer);
extern void observer_notify_normal_stop (struct bpstats *bs, int print_frame);

/* target_changed notifications.  */

typedef void (observer_target_changed_ftype) (struct target_ops *target);

extern struct observer *observer_attach_target_changed (observer_target_changed_ftype *f);
extern void observer_detach_target_changed (struct observer *observer);
extern void observer_notify_target_changed (struct target_ops *target);

/* executable_changed notifications.  */

typedef void (observer_executable_changed_ftype) (void);

extern struct observer *observer_attach_executable_changed (observer_executable_changed_ftype *f);
extern void observer_detach_executable_changed (struct observer *observer);
extern void observer_notify_executable_changed (void);

/* inferior_created notifications.  */

typedef void (observer_inferior_created_ftype) (struct target_ops *objfile, int from_tty);

extern struct observer *observer_attach_inferior_created (observer_inferior_created_ftype *f);
extern void observer_detach_inferior_created (struct observer *observer);
extern void observer_notify_inferior_created (struct target_ops *objfile, int from_tty);

/* solib_loaded notifications.  */

typedef void (observer_solib_loaded_ftype) (struct so_list *solib);

extern struct observer *observer_attach_solib_loaded (observer_solib_loaded_ftype *f);
extern void observer_detach_solib_loaded (struct observer *observer);
extern void observer_notify_solib_loaded (struct so_list *solib);

/* solib_unloaded notifications.  */

typedef void (observer_solib_unloaded_ftype) (struct so_list *solib);

extern struct observer *observer_attach_solib_unloaded (observer_solib_unloaded_ftype *f);
extern void observer_detach_solib_unloaded (struct observer *observer);
extern void observer_notify_solib_unloaded (struct so_list *solib);

/* new_objfile notifications.  */

typedef void (observer_new_objfile_ftype) (struct objfile *objfile);

extern struct observer *observer_attach_new_objfile (observer_new_objfile_ftype *f);
extern void observer_detach_new_objfile (struct observer *observer);
extern void observer_notify_new_objfile (struct objfile *objfile);

/* new_thread notifications.  */

typedef void (observer_new_thread_ftype) (struct thread_info *t);

extern struct observer *observer_attach_new_thread (observer_new_thread_ftype *f);
extern void observer_detach_new_thread (struct observer *observer);
extern void observer_notify_new_thread (struct thread_info *t);

/* thread_exit notifications.  */

typedef void (observer_thread_exit_ftype) (struct thread_info *t, int silent);

extern struct observer *observer_attach_thread_exit (observer_thread_exit_ftype *f);
extern void observer_detach_thread_exit (struct observer *observer);
extern void observer_notify_thread_exit (struct thread_info *t, int silent);

/* thread_stop_requested notifications.  */

typedef void (observer_thread_stop_requested_ftype) (ptid_t ptid);

extern struct observer *observer_attach_thread_stop_requested (observer_thread_stop_requested_ftype *f);
extern void observer_detach_thread_stop_requested (struct observer *observer);
extern void observer_notify_thread_stop_requested (ptid_t ptid);

/* target_resumed notifications.  */

typedef void (observer_target_resumed_ftype) (ptid_t ptid);

extern struct observer *observer_attach_target_resumed (observer_target_resumed_ftype *f);
extern void observer_detach_target_resumed (struct observer *observer);
extern void observer_notify_target_resumed (ptid_t ptid);

/* about_to_proceed notifications.  */

typedef void (observer_about_to_proceed_ftype) (void);

extern struct observer *observer_attach_about_to_proceed (observer_about_to_proceed_ftype *f);
extern void observer_detach_about_to_proceed (struct observer *observer);
extern void observer_notify_about_to_proceed (void);

/* breakpoint_created notifications.  */

typedef void (observer_breakpoint_created_ftype) (int bpnum);

extern struct observer *observer_attach_breakpoint_created (observer_breakpoint_created_ftype *f);
extern void observer_detach_breakpoint_created (struct observer *observer);
extern void observer_notify_breakpoint_created (int bpnum);

/* breakpoint_deleted notifications.  */

typedef void (observer_breakpoint_deleted_ftype) (int bpnum);

extern struct observer *observer_attach_breakpoint_deleted (observer_breakpoint_deleted_ftype *f);
extern void observer_detach_breakpoint_deleted (struct observer *observer);
extern void observer_notify_breakpoint_deleted (int bpnum);

/* breakpoint_modified notifications.  */

typedef void (observer_breakpoint_modified_ftype) (int bpnum);

extern struct observer *observer_attach_breakpoint_modified (observer_breakpoint_modified_ftype *f);
extern void observer_detach_breakpoint_modified (struct observer *observer);
extern void observer_notify_breakpoint_modified (int bpnum);

/* tracepoint_created notifications.  */

typedef void (observer_tracepoint_created_ftype) (int tpnum);

extern struct observer *observer_attach_tracepoint_created (observer_tracepoint_created_ftype *f);
extern void observer_detach_tracepoint_created (struct observer *observer);
extern void observer_notify_tracepoint_created (int tpnum);

/* tracepoint_deleted notifications.  */

typedef void (observer_tracepoint_deleted_ftype) (int tpnum);

extern struct observer *observer_attach_tracepoint_deleted (observer_tracepoint_deleted_ftype *f);
extern void observer_detach_tracepoint_deleted (struct observer *observer);
extern void observer_notify_tracepoint_deleted (int tpnum);

/* tracepoint_modified notifications.  */

typedef void (observer_tracepoint_modified_ftype) (int tpnum);

extern struct observer *observer_attach_tracepoint_modified (observer_tracepoint_modified_ftype *f);
extern void observer_detach_tracepoint_modified (struct observer *observer);
extern void observer_notify_tracepoint_modified (int tpnum);

/* architecture_changed notifications.  */

typedef void (observer_architecture_changed_ftype) (struct gdbarch *newarch);

extern struct observer *observer_attach_architecture_changed (observer_architecture_changed_ftype *f);
extern void observer_detach_architecture_changed (struct observer *observer);
extern void observer_notify_architecture_changed (struct gdbarch *newarch);

/* thread_ptid_changed notifications.  */

typedef void (observer_thread_ptid_changed_ftype) (ptid_t old_ptid, ptid_t new_ptid);

extern struct observer *observer_attach_thread_ptid_changed (observer_thread_ptid_changed_ftype *f);
extern void observer_detach_thread_ptid_changed (struct observer *observer);
extern void observer_notify_thread_ptid_changed (ptid_t old_ptid, ptid_t new_ptid);

/* inferior_added notifications.  */

typedef void (observer_inferior_added_ftype) (struct inferior *inf);

extern struct observer *observer_attach_inferior_added (observer_inferior_added_ftype *f);
extern void observer_detach_inferior_added (struct observer *observer);
extern void observer_notify_inferior_added (struct inferior *inf);

/* inferior_appeared notifications.  */

typedef void (observer_inferior_appeared_ftype) (struct inferior *inf);

extern struct observer *observer_attach_inferior_appeared (observer_inferior_appeared_ftype *f);
extern void observer_detach_inferior_appeared (struct observer *observer);
extern void observer_notify_inferior_appeared (struct inferior *inf);

/* inferior_exit notifications.  */

typedef void (observer_inferior_exit_ftype) (struct inferior *inf);

extern struct observer *observer_attach_inferior_exit (observer_inferior_exit_ftype *f);
extern void observer_detach_inferior_exit (struct observer *observer);
extern void observer_notify_inferior_exit (struct inferior *inf);

/* inferior_removed notifications.  */

typedef void (observer_inferior_removed_ftype) (struct inferior *inf);

extern struct observer *observer_attach_inferior_removed (observer_inferior_removed_ftype *f);
extern void observer_detach_inferior_removed (struct observer *observer);
extern void observer_notify_inferior_removed (struct inferior *inf);

/* memory_changed notifications.  */

typedef void (observer_memory_changed_ftype) (CORE_ADDR addr, int len, const bfd_byte *data);

extern struct observer *observer_attach_memory_changed (observer_memory_changed_ftype *f);
extern void observer_detach_memory_changed (struct observer *observer);
extern void observer_notify_memory_changed (CORE_ADDR addr, int len, const bfd_byte *data);

/* test_notification notifications.  */

typedef void (observer_test_notification_ftype) (int somearg);

extern struct observer *observer_attach_test_notification (observer_test_notification_ftype *f);
extern void observer_detach_test_notification (struct observer *observer);
extern void observer_notify_test_notification (int somearg);

#endif /* OBSERVER_H */
