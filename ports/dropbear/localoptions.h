/* QNX / BlackBerry Passport localoptions.h
 * Server stays single-user (no setresgid on this QNX).
 * The getgroups multiuser-kernel check is skipped on QNX in
 * common-session.c (GitHub issue #6). See build-dropbear-passport.sh.
 */
#define DROPBEAR_SVR_DROP_PRIVS 0
#define DROPBEAR_SVR_MULTIUSER 0
#define DROPBEAR_SVR_PAM_AUTH 0
#define DROPBEAR_SVR_LOCALSTREAMFWD 0
#define DROPBEAR_SVR_REMOTESTREAMFWD 0
