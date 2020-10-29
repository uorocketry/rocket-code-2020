#pragma once

#ifndef USE_SBG
#define USE_SBG 1
#endif

#ifndef USE_SOCKET_CLIENT
#define USE_SOCKET_CLIENT 0
#endif

#ifndef USE_LOGGER
#define USE_LOGGER 0
#endif

#ifndef USE_INPUT
#define USE_INPUT 1
#endif

#ifndef TESTING
#define TESTING 0
#endif

#ifndef USE_RADIO
#define USE_RADIO 1
#endif

#ifndef SKIP_INIT
#define SKIP_INIT 0
#endif

// because we can't use inputs if it is manual testing
#if TESTING
#define USE_LOGGER 0
#define USE_SOCKET_CLIENT 0
#endif