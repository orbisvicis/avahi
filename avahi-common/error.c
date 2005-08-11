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

#include "error.h"

const char *avahi_strerror(int error) {
    
    const char * const msg[- AVAHI_ERR_MAX] = {
        "OK",
        "Operation failed",
        "Bad state",
        "Invalid host name",
        "Invalid domain name",
        "No suitable network protocol available",
        "Invalid DNS TTL",
        "Resource record key is pattern",
        "Local name collision",
        "Invalid record",
        "Invalid service name",
        "Invalid service type",
        "Invalid port number",
        "Invalid record key",
        "Invalid address",
        "Timeout reached",
        "Too many clients",
        "Too many objects",
        "Too many entries",
        "OS Error",
        "Access denied",
        "Invalid operation",
        "An unexpected DBUS error occured",
        "Could not get a connection to the daemon"
    };

    if (-error < 0 || -error >= -AVAHI_ERR_MAX)
        return "Invalid Error Code";

    return msg[-error];
}
