/*
 * BDB - Debugger for the Birtual Machine
 * Copyright 2020 by Nico Sonack
 *
 * Contribution to https://github.com/tsoding/bm
 */

#ifndef BDB_H
#define BDB_H

#include "bm.h"

typedef enum {
   BDB_OK = 0,
   BDB_FAIL = 1,
   BDB_EXIT
} Bdb_Err;

typedef struct Bdb_Breakpoint
{
    int is_enabled;
    int id;
    int is_broken;
} Bdb_Breakpoint;

typedef struct Bdb_State
{
    Bm bm;
    String_View cood_file_name;
    Bdb_Breakpoint breakpoints[BM_PROGRAM_CAPACITY];
    String_View labels[BM_PROGRAM_CAPACITY];
    Arena arena;
} Bdb_State;

Bdb_Err bdb_state_init(Bdb_State *, const char *executable);
Bdb_Err bdb_load_symtab(Bdb_State *state, String_View symtab_file);
Bdb_Err bdb_step_instr(Bdb_State *);
Bdb_Err bdb_continue(Bdb_State *);
Bdb_Err bdb_find_addr_of_label(Bdb_State *, String_View, Inst_Addr *);
Bdb_Err bdb_parse_label_or_addr(Bdb_State *, String_View, Inst_Addr *);
void bdb_print_instr(FILE *, Inst *);
void bdb_add_breakpoint(Bdb_State *, Inst_Addr);
void bdb_delete_breakpoint(Bdb_State *, Inst_Addr);
Bdb_Err bdb_fault(Bdb_State *, Err);

#endif // BDB_H
