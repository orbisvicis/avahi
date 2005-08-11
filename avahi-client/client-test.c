/* $Id$ */

/***
  This file is part of avahi.
 
  avahi is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.
 
  avahi is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
  Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with avahi; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
***/

#include <avahi-client/client.h>
#include <avahi-common/error.h>
#include <stdio.h>
#include <glib.h>

void
avahi_client_callback (AvahiClient *c, AvahiClientState state, void *user_data)
{
    printf ("XXX: Callback on client, state -> %d, data -> %s\n", state, (char*)user_data);
}

void
avahi_entry_group_callback (AvahiClient *c, AvahiEntryGroup *g, AvahiEntryGroupState state, void *user_data)
{
    printf ("Callback on %s, state -> %d, data -> %s\n", avahi_entry_group_get_path (g), state, (char*)user_data);
}

int
main (int argc, char *argv[])
{
    GMainLoop *loop;
    AvahiClient *avahi;
    AvahiEntryGroup *group;
    AvahiStringList *txt;
    char *ret;

    loop = g_main_loop_new (NULL, FALSE);
    
    avahi = avahi_client_new (avahi_client_callback, "omghai2u");

    g_assert (avahi != NULL);

    ret = avahi_client_get_version_string (avahi);
    printf ("Avahi Server Version: %s (Error Return: %s)\n", ret, avahi_strerror (avahi_client_errno (avahi)));
    g_free (ret);

    ret = avahi_client_get_host_name (avahi);
    printf ("Host Name: %s (Error Return: %s)\n", ret, avahi_strerror (avahi_client_errno (avahi)));
    g_free (ret);

    ret = avahi_client_get_domain_name (avahi);
    printf ("Domain Name: %s (Error Return: %s)\n", ret, avahi_strerror (avahi_client_errno (avahi)));
    g_free (ret);

    ret = avahi_client_get_host_name_fqdn (avahi);
    printf ("FQDN: %s (Error Return: %s)\n", ret, avahi_strerror (avahi_client_errno (avahi)));
    g_free (ret);
    
    group = avahi_entry_group_new (avahi, avahi_entry_group_callback, "omghai");

    printf ("Creating entry group: %s\n", avahi_strerror (avahi_client_errno (avahi)));

    if (group == NULL)
        printf ("Failed to create entry group object\n");
    else
        printf ("Sucessfully created entry group, path %s\n", avahi_entry_group_get_path (group));

    txt = avahi_string_list_new ("foo=bar", NULL);

    avahi_entry_group_add_service (group, AVAHI_IF_UNSPEC, AF_UNSPEC, "Lathiat's Site", "_http._tcp", "", "", 80, txt);

    avahi_entry_group_commit (group);

    g_main_loop_run (loop);

    g_free (avahi);

    return 0;
}
