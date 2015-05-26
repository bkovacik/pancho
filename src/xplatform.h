//xplatform.h

#ifdef _WIN32
	#include <windows.h>
#endif

#elif __linux__
	#include <unistd.h>
#endif

#ifdef __APPLE__ && __MACH__
	#include <unistd.h>
#endif

