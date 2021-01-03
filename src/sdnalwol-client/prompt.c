#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>




// get_system_info() returns the hosting system's info using utsname struct and uname()
// the function returns the system's name, version, release, and architecture.
// sysname isn't returned because the hosting machine is probably linux (duh).

const char* get_system_info()
{

	char *failure = "Failed to get system info!\n";
	char *success = malloc(128 * sizeof(success));

	struct utsname system_info; // Used to store system data returned from uname().

	if (uname(&system_info) != 0) {
		return failure;
	} else {
		strcpy(success, "ID: ");

		strcat(success, system_info.nodename);
		strcat(success, "\n");

		strcat(success, "Release: ");
		strcat(success, system_info.release);
		strcat(success, "\n");

		strcat(success, "Version: ");
		strcat(success, system_info.version);
		strcat(success, "\n");

		strcat(success, "Machine: ");
		strcat(success, system_info.machine);
		strcat(success, "\n");
		
		return success;
	}
}


