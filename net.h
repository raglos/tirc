#ifndef __NET_H__
#define __NET_H__

#define NETESOCKET 1
#define NETEHOST   2
#define NETECON    3

int net_connect (const char *, int, int*);
int net_disconnect (int);
int net_receive (const int, char *, const size_t);
int net_send (const int, const char *, const size_t);
#endif
