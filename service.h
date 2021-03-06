// Copyright (c) 2021 David Helkowski
// Anti-Corruption License

#ifndef __SERVICE_H
#define __SERVICE_H

#include<CoreFoundation/CoreFoundation.h>
#include"mobiledevice.h"
#include"mobdev_err.h"
#include"uclop.h"
#include"archiver/archiver.h"

typedef struct {
  int nextChanId;
  void *service;
  char secure;
  //CFDictionaryRef channels;
  tDICT *channels;
} serviceT;

typedef struct {
  int nextMsgId;
  void *service;
  char secure;
  int channel;
  serviceT *serviceOb;
} channelT;

#define SEND_HASREPLY 1
#define SEND_SECUREARG 2

serviceT *service__new( void *device, char *name, char *secureName );
channelT *service__connect_channel( serviceT *service, char *name );
channelT *service__connect_channel_int( serviceT *service, char *name, char skipRecv );
channelT *channel__connect_channel_int( channelT *channel, char *name, char skipRecv );
char service__handshake( serviceT *self );
char channel__handshake( channelT *self ) ;
char service__handshake2( serviceT *self );

channelT *channel__new( void *service, char secure, int id );
char channel__send( channelT *chan, const char *method, tBASE *args, uint8_t flags );
char channel__send_withid( channelT *self, const char *method, tBASE *args, uint8_t flags, uint32_t id );
char channel__reply( channelT *self, tBASE *argsT, uint32_t id, int convIndex );

//char channel__recv( channelT *self, CFTypeRef *msgOut, CFArrayRef *argOut );
char channel__recv( channelT *self, tBASE **msgOut, tARR **argOut );
char channel__recv_withid( channelT *self, tBASE **msgOut, tARR **argOut, int *idout, int *convIndexOut, int *channeOut );

//char channel__call( channelT *chan, const char *method, tBASE *args,
//    uint8_t flags, CFTypeRef *msgOut, CFArrayRef *auxOut );
char channel__call( channelT *chan, const char *method, tBASE *args,
    uint8_t flags, tBASE **msgOut, tARR **auxOut );

//char service__send( serviceT *self, CFTypeRef msg, tBASE *aux, uint8_t flags );
char service__send( serviceT *self, char *msg, tBASE *ux, uint8_t flags );

//char service__recv( serviceT *self, CFTypeRef *msg, CFArrayRef *aux );
char service__recv( serviceT *self, tBASE **msg, tARR **aux );

//char service__call( serviceT *self, 
//  const char *method, tBASE *args, uint8_t flags,
//  CFTypeRef *msgOut, CFArrayRef *auxOut );
char service__call( serviceT *self, 
    const char *method, tBASE * args, uint8_t flags,
    tBASE **msgOut, tARR **auxOut );

void service__del( serviceT *self );

void devUp( void *device );

void devDown( void *device );

void exitOnError( int rc, const char *src );

void waitForConnect( void (*onConnect)(void *device) );
void waitForConnectDisconnect( void (*onConnect)(void *device), void (*onDisconnect)(void *device)  );

void setupTimeout( int seconds );

char desired_device( void *device, ucmd *g_cmd );
#endif