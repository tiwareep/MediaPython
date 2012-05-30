/**
 * Sam 0
 *   Sam'e experiments in D-Bus services.
 *
 * Illustrates
 *   * Basics of starting a server.  (See main and the procedures
 *     it calls.)
 *   * How to set up a "quit" message.  (See handle_method_call.)
 *   * How to create an interface dynamically.  (See sample_node and
 *     sample_interface, as well as the utilities they call.)
 *   * Receiving and returning values.  (See handle_method_call.)
 *   * How to register and generate errors.  (For registration, see the 
 *     SampleError enum, the error_entries global, and the quark_setup
 *     procedure.  For use, see the default code in handle_method_call.)
 *
 * Note that you can get some more output information while this
 * procedure is running by defining OBSERVE.
 *
 * Things to figure out:
 *   Sending and returning arrays (of strings, ints, doubles)
 *   Sending and returning structs
 *   Sending and returning chunks of memory (or maybe arrays will do)
 */

// +---------+--------------------------------------------------------
// | Headers |
// +---------+

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <gio/gio.h>


// +-------+----------------------------------------------------------
// | Types |
// +-------+

/**
 * Numbers for our wonderous errors.
 */
typedef enum
  {
    SAMPLE_ERROR_UNIMPLEMENTED,
    SAMPLE_ERROR_MISCELLANEOUS
  } SampleError;


// +---------+--------------------------------------------------------
// | Globals |
// +---------+

/**
 * The mapping of error numbers to error strings.
 */
static const GDBusErrorEntry error_entries[] =
  {
    { SAMPLE_ERROR_UNIMPLEMENTED, "org.glimmer.Sample.Error.Unimplemented" },
    { SAMPLE_ERROR_MISCELLANEOUS, "org.glimmer.Sample.Error.Miscellaneous" },

  };

/** 
 * The main event-handling loop.
 */
static GMainLoop *loop;

/**
 * The introspection data.  Whee!
 */
static GDBusNodeInfo *introspection_data = NULL;

/**
 * The error quark
 */
static GQuark quark;


// +-----------------+------------------------------------------------
// | Predeclarations |
// +-----------------+

GDBusInterfaceInfo *sample_interface (void);


// +-------------------+----------------------------------------------
// | General Utilities |
// +-------------------+

/**
 * Allocate and build an array of pointers.
 */
gpointer *
A (gpointer p0, ...)
{
  gpointer p;           // Iterator
  gint size = 0;        // Number of pointers
  va_list args;         // The extra arguments
  int i;                // Everyone's favorite couter

  // Figure out how many pointers we have
  va_start (args, p0);
  for (p = p0; p != NULL; p = va_arg (args, gpointer))
    ++size;
  va_end (args);

  // Build the array
  gpointer *ps = g_new (gpointer, size+1);
  va_start (args, p0);
  for (i = 0, p = p0; p != NULL; i++, p = va_arg (args, gpointer))
    ps[i] = p;
  va_end (args);
  ps[size] = NULL;

  // We're done
  return ps;
} // A

/**
 * Dump the introspection data for a node.
 */
void
dump_node (GDBusNodeInfo *node_data)
{
  if (node_data == NULL)
    fprintf (stderr, "NO INTROSPECTION DATA");

  GString *string = g_string_new ("");
  g_dbus_node_info_generate_xml (node_data, 0, string);
  fprintf (stderr, "%s", string->str);
  g_string_free (string, TRUE);
} // dump_node


// +----------------------------------------+-------------------------
// | Introspection Information Construction |
// +----------------------------------------+

GDBusArgInfo *
arg_new (gchar *name,
         gchar *signature,
         gpointer *annotations)
{
  GDBusArgInfo *arg= 
    g_try_malloc (sizeof (GDBusArgInfo));
  if (arg == NULL)
    return NULL;
  
  arg->ref_count = 0;
  arg->name = name;
  arg->signature = signature;
  arg->annotations = (GDBusAnnotationInfo **) annotations;

  return arg;
} // arg_new

GDBusInterfaceInfo *
interface_new (gchar    *name, 
               gpointer *methods,
               gpointer *signals,
               gpointer *properties,
               gpointer *annotations)
{
  GDBusInterfaceInfo *interface = 
    g_try_malloc (sizeof (GDBusInterfaceInfo));
  if (interface == NULL)
    return NULL;

  interface->ref_count = 1;
  interface->name = name;
  interface->methods = (GDBusMethodInfo **) methods;
  interface->signals = (GDBusSignalInfo **) signals;
  interface->properties = (GDBusPropertyInfo **) properties;
  interface->annotations = (GDBusAnnotationInfo **) annotations;

  return interface;
} // interface_new

GDBusMethodInfo *
method_new (gchar *name,
            gpointer *in_args,
            gpointer *out_args,
            gpointer *annotations)
{
  GDBusMethodInfo *info = g_try_malloc (sizeof (GDBusMethodInfo));
  if (info == NULL)
    return NULL;
  info->ref_count = 1;
  info->name = name;
  info->in_args = (GDBusArgInfo **) in_args;
  info->out_args = (GDBusArgInfo **) out_args;
  info->annotations = (GDBusAnnotationInfo **) annotations;
  return info;
} // method_new


// +---------------------------+--------------------------------------
// | Sample Introspection Data |
// +---------------------------+

GDBusInterfaceInfo *
sample_interface (void)
{
  return 
    interface_new ("edu.glimmer.TestServer",
      A (method_new ("dump", NULL, NULL, NULL),
         method_new ("gets",
           NULL,
           A (arg_new ("str", "s", NULL), NULL),
           NULL),
         method_new ("putii", 
           A (arg_new ("i0", "i", NULL),
              arg_new ("i1", "i", NULL),
              NULL),
           NULL,
           NULL),
         method_new ("putis", 
           A (arg_new ("i", "i", NULL),
              arg_new ("s", "s", NULL),
              NULL),
           NULL,
           NULL),
         method_new ("puts",
           A (arg_new ("str", "s", NULL), NULL),
           NULL,
           NULL),
         method_new ("quit", NULL, NULL, NULL),
         NULL),
      NULL,
      NULL,
      NULL);
} // sample_interface

GDBusNodeInfo *
sample_node (void)
{
  GDBusNodeInfo *node = g_try_malloc (sizeof (GDBusNodeInfo));
  node->ref_count = 1;
  node->path = "/org/glimmer/TestServer";
  node->nodes = NULL;
  node->annotations = NULL;
  node->interfaces = (GDBusInterfaceInfo **) A (sample_interface (), NULL);
  return node;
} // sample_node


// +------------------+-----------------------------------------------
// | Message Handlers |
// +------------------+

static void
handle_method_call (GDBusConnection       *connection,
                    const gchar           *sender,
                    const gchar           *object_path,
                    const gchar           *interface_name,
                    const gchar           *method_name,
                    GVariant              *parameters,
                    GDBusMethodInvocation *invocation,
                    gpointer               user_data)
{
#ifdef OBSERVE
  gchar *params = g_variant_print (parameters, TRUE);
  const gchar *type = g_variant_get_type_string (parameters);
  g_message ("%s %s called (type %s)", method_name, params, type);
#endif // OBSERVE

  // A hack to make it easier to rearrange the handlers
  if (FALSE)
    ;
  
  // Dump the XML
  else if (g_strcmp0 (method_name, "dump") == 0)
    {
      dump_node (introspection_data);
      g_dbus_method_invocation_return_value (invocation, NULL);
    } // dump

  // Get a string
  else if (g_strcmp0 (method_name, "gets") == 0)
    {
      gchar *response = "A constant string.";
      g_dbus_method_invocation_return_value (invocation,
                                             g_variant_new ("(s)", response));
    } // gets

  // Quit the program
  else if (g_strcmp0 (method_name, "quit") == 0)
    {
      g_dbus_method_invocation_return_value (invocation,
                                             g_variant_new ("(s)", "goodbye"));
      g_main_loop_quit (loop);
      g_dbus_method_invocation_return_value (invocation, NULL);
    } // quit

  // Everything else is unimplemented
  else
    {
      g_dbus_method_invocation_return_error (invocation,
                                             quark,
                                             SAMPLE_ERROR_UNIMPLEMENTED,
                                             "%s is unimplemented",
                                             method_name);
    } // default
} // handle_method_call

static GVariant *
handle_get_property (GDBusConnection  *connection,
                     const gchar      *sender,
                     const gchar      *object_path,
                     const gchar      *interface_name,
                     const gchar      *property_name,
                     GError          **error,
                     gpointer          user_data)
{
  return NULL;
} // handle_get_property

static gboolean
handle_set_property (GDBusConnection  *connection,
                     const gchar      *sender,
                     const gchar      *object_path,
                     const gchar      *interface_name,
                     const gchar      *property_name,
                     GVariant         *value,
                     GError          **error,
                     gpointer          user_data)
{
  return FALSE;
} // handle_set_property

/**
 * The table of DBus handlers.
 */
static const GDBusInterfaceVTable interface_vtable =
{
  handle_method_call,
  handle_get_property,
  handle_set_property
};


// +----------+-------------------------------------------------------
// | Handlers |
// +----------+

static void
on_bus_acquired (GDBusConnection *connection,
                 const gchar     *name,
                 gpointer         user_data)
{
  guint registration_id;

#ifdef OBSERVE
  g_message ("acquired bus");
#endif

  registration_id = 
    g_dbus_connection_register_object (connection,
                                       "/org/gtk/GDBus/TestObject",
                                       introspection_data->interfaces[0],
                                       &interface_vtable,
                                       NULL,  /* user_data */
                                       NULL,  /* user_data_free_func */
                                       NULL); /* GError** */
  g_assert (registration_id > 0);

#ifdef OBSERVE
  g_message ("got registration id");
#endif // OBSERVE
} // on_bus_acquired

static void
on_name_acquired (GDBusConnection *connection,
                  const gchar     *name,
                  gpointer         user_data)
{
#ifdef OBSERVE
  g_message ("acquired name");
#endif // OBSERVE
} // on_name_acquired

static void
on_name_lost (GDBusConnection *connection,
              const gchar     *name,
              gpointer         user_data)
{
#ifdef OBSERVE
  g_message ("name_lost");
#endif // OBSERVE
  exit (1);
} // on_name_lost


// +---------------+--------------------------------------------------
// | Miscellaneous |
// +---------------+

/**
 * Set up the quark
 */
void
quark_setup (void)
{
  static volatile gsize quark_volatile = 0;
  g_dbus_error_register_error_domain ("org-glimmer-error-quark",
                                      &quark_volatile,
                                      error_entries,
                                      G_N_ELEMENTS (error_entries));
  quark = quark_volatile;
} // quark_setup


// +------+-----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  guint owner_id;
  GBusNameOwnerFlags flags;

  g_type_init ();

  // Set up the quark
  quark_setup ();

  // Build the introspection data
  introspection_data = sample_node ();
#ifdef OBSERVE
  dump_node (introspection_data);
#endif // OBSERVE

  // Get the bus
  flags = G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT 
        | G_BUS_NAME_OWNER_FLAGS_REPLACE;
  owner_id = g_bus_own_name (G_BUS_TYPE_SESSION,
                             "org.glimmer.TestServer",
                             flags,
                             on_bus_acquired,
                             on_name_acquired,
                             on_name_lost,
                             NULL,
                             NULL);

  // Main loop
  loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (loop);

  // Clean up
  g_bus_unown_name (owner_id);

  // And we're done
  return 0;
} // main

