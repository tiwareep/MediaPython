/**
 * glist: 
 *   A GIMP plugin that prints out a list of the names of all the procedures.
 *
 *   Portions of this code are based on the MediaScheme files 
 *   libs/mpltg/mpltg.c and plugins/gimp/msg-console.c.
 *
 * Copyright (c) 2011 Samuel A. Rebelsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// +---------+--------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>

#include <libgimp/gimp.h>


// +----------------------------------+-------------------------------
// | Standard Gimp Plugin Boilerplate |
// +----------------------------------+

static void query (void);
static void quit (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);

GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  quit,
  query,
  run
};

MAIN ()


// +-------------------------------+----------------------------------
// | The Key Gimp Plugin Functions |
// +-------------------------------+

static void
query (void)
{
  // The arguments that the plug-in expects
  static GimpParamDef args[] =
  {
    { GIMP_PDB_INT32, "run-mode", "Run mode" }
  };

  // Install this plug-in.
  gimp_install_procedure (
    "proc_list",
    "List PDB functions",
    "Testing whether I can print out all the procedure names",
    "Samuel A. Rebelsky",
    "Copyright (c) Samuel A. Rebelsky",
    "2011",
    "<Toolbox>/Xtns/MediaScript/ProcList",
    NULL, 
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);
}

static void
run (const gchar      *name,
     gint              nparams,
     const GimpParam  *param,
     gint             *nreturn_vals,
     GimpParam       **return_vals)
{
  static GimpParam  values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;

  // Setting mandatory output values
  *nreturn_vals = 1;
  *return_vals  = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  // Getting run_mode, even though we ignore it.
  run_mode = param[0].data.d_int32;

  // Print out the list
  gchar **procnames;
  gint nprocs;
  gimp_procedural_db_query (".*", ".*", ".*", ".*", ".*", ".*", ".*",
                            &nprocs, &procnames);
  int i;
  for (i = 0; i < nprocs; i++)
    {
      printf ("%04d: %s\n", i, procnames[i]);
    }

} // run 

static void
quit (void)
{
} // quit
