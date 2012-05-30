/**
 * ginfo: 
 *   A GIMP plugin that prints out information on some GIMP procedures.  
 *    Intended as an example of how one uses gimp_procedural_db_proc_info.
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


// +-------+----------------------------------------------------------
// | Types |
// +-------+

/**
 * A pair that associates a gimp type (GIMP_PDB_????) to an associated
 * name.
 */
struct
pair {
  int value;
  const char *name;
};


// +-----------+------------------------------------------------------
// | Constants |
// +-----------+

/**
 * A structure to convert PDB types to human-readable strings.
 */
static struct pair
pdb_readable_types[] =
  {
    { GIMP_PDB_INT32, "integer" },
    { GIMP_PDB_INT16, "integer" },
    { GIMP_PDB_INT8, "integer" },
    { GIMP_PDB_FLOAT, "real" },
    { GIMP_PDB_STRING, "string" },
    { GIMP_PDB_INT32ARRAY, "vector of integers" },
    { GIMP_PDB_INT16ARRAY, "vector of integers" },
    { GIMP_PDB_INT8ARRAY, "vector of integers" },
    { GIMP_PDB_FLOATARRAY, "vector of real numbers" },
    { GIMP_PDB_STRINGARRAY, "vector of strings" },
    { GIMP_PDB_COLOR, "color" },
    { GIMP_PDB_REGION, "region" },
    { GIMP_PDB_DISPLAY, "display/integer" },
    { GIMP_PDB_IMAGE , "image/integer" },
    { GIMP_PDB_LAYER, "layer/integer" },
    { GIMP_PDB_CHANNEL, "channel/integer" },
    { GIMP_PDB_DRAWABLE, "drawable/integer" },
    { GIMP_PDB_SELECTION, "selection/integer" },
    { GIMP_PDB_BOUNDARY, "boundary/integer" },
    { GIMP_PDB_VECTORS, "vectors/integer" },
    { GIMP_PDB_PARASITE, "parasite" },
    { GIMP_PDB_END, "unknown" },
  }; // pdb_readable_types



// +---------------+--------------------------------------------------
// | Local Helpers |
// +---------------+

/**
 * Determine a human-readable version of a PDB type.
 */
static const char *
pdb_readable_typename (int type)
{
  int i;
  for (i = 0; pdb_readable_types[i].value != GIMP_PDB_END; i++)
    {
      if (pdb_readable_types[i].value == type)
        return pdb_readable_types[i].name;
    }
  return "UNKNOWN TYPE";
} // pdb_readable_typename

/**
 * Print information on a GIMP procedure.
 */
static void
pdb_print_info (gchar *proc_name)
{
  gint i;
  // Lots and lots and lots of fields for getting info.
  gchar           *proc_blurb;
  gchar           *proc_help;
  gchar           *proc_author;
  gchar           *proc_copyright;
  gchar           *proc_date;
  GimpPDBProcType  proc_type;
  GimpParamDef    *params;       
  gint             nparams;
  GimpParamDef    *return_vals;
  gint             nreturn_vals;
  
  if (! gimp_procedural_db_proc_info (proc_name,
                                     &proc_blurb,
                                     &proc_help,
                                     &proc_author,
                                     &proc_copyright,
                                     &proc_date,
                                     &proc_type,
                                     &nparams, &nreturn_vals,
                                     &params, &return_vals))
    {
      printf ("%s is undefined.\n", proc_name);
    } // if we could not look up the procedure
  else
    {
      printf ("Procedure:   %s\n", proc_name);
      printf ("  Blurb:     %s\n", proc_blurb);
      printf ("  Help:      %s\n", proc_help);
      printf ("  Author:    %s\n", proc_author);
      printf ("  Copyright: %s\n", proc_copyright);
      printf ("  Date:      %s\n", proc_date);
      printf ("  Parameters:\n");
      for (i = 0; i < nparams; i++)
        {
          printf ("    %d: (%s) %s // %s\n", 
                  i, 
                  pdb_readable_typename (params[i].type), 
                  params[i].name,
                  params[i].description);
        }
      printf ("  Return Values:\n");
      for (i = 0; i < nreturn_vals; i++)
        {
          printf ("    %d: (%s) %s // %s\n", 
                  i, 
                  pdb_readable_typename (return_vals[i].type), 
                  return_vals[i].name,
                  return_vals[i].description);
        }
    } // found
  printf ("\n");
} // pdib_print_info


// +----------------------------+-------------------------------------
// | Standard Gimp Plugin Stuff |
// +----------------------------+

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
    "proc_info",
    "Testing PDB functions",
    "Testing whether I can print out info on a procedure",
    "Samuel A. Rebelsky",
    "Copyright (c) Samuel A. Rebelsky",
    "2011",
    "<Toolbox>/Xtns/MediaScript/ProcInfo",
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

  // Print info on a procedure
  pdb_print_info ("gimp-image-new");
  pdb_print_info ("gimp-rect-select");
} // run 

static void
quit (void)
{
} // quit
