/**
 * Example 0.  Simplified version of Example 2 from
 *   From http://developer.gnome.org/gio/2.26/GDBusConnection.html
 */

#include <gio/gio.h>
#include <stdlib.h>

static GDBusNodeInfo *introspection_data = NULL;

/* Introspection data for the service we are exporting */
static const gchar introspection_xml[] =
  "<node>"
  "  <interface name='org.gtk.GDBus.TestInterface'>"
  "    <method name='GetAnswer'>"
  "      <annotation name='org.gtk.GDBus.Annotation' value='OnMethod'/>"
  "      <arg type='i' name='answer' direction='out'/>"
  "    </method>"
  "  </interface>"
  "</node>";

/* ---------------------------------------------------------------------------------------------------- */

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
  if (g_strcmp0 (method_name, "GetAnswer") == 0)
    {
      g_dbus_method_invocation_return_value (invocation,
                                             g_variant_new ("(i)", 42));
    }
}

static GVariant *
handle_get_property (GDBusConnection  *connection,
                     const gchar      *sender,
                     const gchar      *object_path,
                     const gchar      *interface_name,
                     const gchar      *property_name,
                     GError          **error,
                     gpointer          user_data)
{
  return NULL; // HACK
}

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
  return FALSE;	// HACK
}

static const GDBusInterfaceVTable interface_vtable =
{
  handle_method_call,
  handle_get_property,
  handle_set_property
};

static void
on_bus_acquired (GDBusConnection *connection,
                 const gchar     *name,
                 gpointer         user_data)
{
  guint registration_id;

  registration_id = g_dbus_connection_register_object (connection,
                                                       "/org/gtk/GDBus/TestObject",
                                                       introspection_data->interfaces[0],
                                                       &interface_vtable,
                                                       NULL,  /* user_data */
                                                       NULL,  /* user_data_free_func */
                                                       NULL); /* GError** */
  g_assert (registration_id > 0);

}

static void
on_name_acquired (GDBusConnection *connection,
                  const gchar     *name,
                  gpointer         user_data)
{
}

static void
on_name_lost (GDBusConnection *connection,
              const gchar     *name,
              gpointer         user_data)
{
  exit (1);
}

int
main (int argc, char *argv[])
{
  guint owner_id;
  GMainLoop *loop;

  g_type_init ();

  /* We are lazy here - we don't want to manually provide
   * the introspection data structures - so we just build
   * them from XML.
   */
  introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
  g_assert (introspection_data != NULL);

  owner_id = g_bus_own_name (G_BUS_TYPE_SESSION,
                             "org.gtk.GDBus.TestServer",
                             G_BUS_NAME_OWNER_FLAGS_NONE,
                             on_bus_acquired,
                             on_name_acquired,
                             on_name_lost,
                             NULL,
                             NULL);

  loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (loop);

  g_bus_unown_name (owner_id);

  g_dbus_node_info_unref (introspection_data);

  return 0;
}

