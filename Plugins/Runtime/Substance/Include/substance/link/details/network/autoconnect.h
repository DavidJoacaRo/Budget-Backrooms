/** @file autoconnect.h
    @brief Contains functions for automatically connecting to other instances
    @author Galen Helfter - Adobe
    @date 20190718
    @copyright Adobe. All rights reserved.
*/

#ifndef _SUBSTANCE_LINK_DETAILS_NETWORK_AUTOCONNECT_H
#define _SUBSTANCE_LINK_DETAILS_NETWORK_AUTOCONNECT_H

#include <substance/link/common.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* __cplusplus */

/* Broadcast connects to all open link instances using Unix sockets. */
unsigned int link_broadcast_connect_unix(void);

/* Broadcast connects to all open link instances using TCP sockets. */
unsigned int link_broadcast_connect_tcp(void);

/* Broadcast connects to all open instances of Substance link, using the
 * default implementation for the given platform. */
unsigned int link_broadcast_connect_default(void);

/* Opens a default tcp connection, allowing other instances to connect
 * using a tcp broadcast connection. Returns an errorcode representing
 * success or failure. */
unsigned int link_open_default_tcp(unsigned int *context);

/* Opens a default unix connection, allowing other instances to connect
 * using a unix broadcast connection call. Returns an errorcode representing
 * success or failure. */
unsigned int link_open_default_unix(unsigned int *context);

/* Opens a default connection, using the platform-specific default
 * type. This will be set up in a way that a default broadcast connection
 * call from another instance will establish a connection. Returns an
 * errorcode representing success or failure.*/
unsigned int link_open_default_connection(unsigned int *context);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _SUBSTANCE_LINK_DETAILS_NETWORK_AUTOCONNECT_H */
