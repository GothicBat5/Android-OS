#ifndef _SPAWN_H_
#define _SPAWN_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sched.h>
#include <signal.h>

__BEGIN_DECLS

#define POSIX_SPAWN_RESETIDS 1
#define POSIX_SPAWN_SETPGROUP 2
#define POSIX_SPAWN_SETSIGDEF 4
#define POSIX_SPAWN_SETSIGMASK 8
#define POSIX_SPAWN_SETSCHEDPARAM 16
#define POSIX_SPAWN_SETSCHEDULER 32

#if defined(__USE_GNU)

#define POSIX_SPAWN_USEVFORK 64
#define POSIX_SPAWN_SETSID 128
#endif

typedef struct __posix_spawnattr* posix_spawnattr_t;
typedef struct __posix_spawn_file_actions* posix_spawn_file_actions_t;
#if __ANDROID_API__ >= 28

int posix_spawn(pid_t* __pid, 
  const char* __path, 
    const posix_spawn_file_actions_t* __actions, 

const posix_spawnattr_t* __attr, 
  char* const __argv[], 
    char* const __env[]) __INTRODUCED_IN(28);

int posix_spawnp(pid_t* __pid, 
  const char* __file, 
    const posix_spawn_file_actions_t* __actions, 

const posix_spawnattr_t* __attr, 
  char* const __argv[], 
    char* const __env[]) __INTRODUCED_IN(28);

int posix_spawnattr_init(posix_spawnattr_t* __attr) __INTRODUCED_IN(28);
int posix_spawnattr_destroy(posix_spawnattr_t* __attr) __INTRODUCED_IN(28);
int posix_spawnattr_setflags(posix_spawnattr_t* __attr, short __flags) __INTRODUCED_IN(28);
int posix_spawnattr_getflags(const posix_spawnattr_t* __attr, short* __flags) __INTRODUCED_IN(28);
int posix_spawnattr_setpgroup(posix_spawnattr_t* __attr, pid_t __pgroup) __INTRODUCED_IN(28);
int posix_spawnattr_getpgroup(const posix_spawnattr_t* __attr, pid_t* __pgroup) __INTRODUCED_IN(28);
int posix_spawnattr_setsigmask(posix_spawnattr_t* __attr, const sigset_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_setsigmask64(posix_spawnattr_t* __attr, const sigset64_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_getsigmask(const posix_spawnattr_t* __attr, sigset_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_getsigmask64(const posix_spawnattr_t* __attr, sigset64_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_setsigdefault(posix_spawnattr_t* __attr, const sigset_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_setsigdefault64(posix_spawnattr_t* __attr, const sigset64_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_getsigdefault(const posix_spawnattr_t* __attr, sigset_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_getsigdefault64(const posix_spawnattr_t* __attr, sigset64_t* __mask) __INTRODUCED_IN(28);
int posix_spawnattr_setschedparam(posix_spawnattr_t* __attr, const struct sched_param* __param) __INTRODUCED_IN(28);
int posix_spawnattr_getschedparam(const posix_spawnattr_t* __attr, struct sched_param* __param) __INTRODUCED_IN(28);
int posix_spawnattr_setschedpolicy(posix_spawnattr_t* __attr, int __policy) __INTRODUCED_IN(28);
int posix_spawnattr_getschedpolicy(const posix_spawnattr_t* __attr, int* __policy) __INTRODUCED_IN(28);
int posix_spawn_file_actions_init(posix_spawn_file_actions_t* __actions) __INTRODUCED_IN(28);
int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t* __actions) __INTRODUCED_IN(28);
int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t* __actions, int __fd, const char* __path, int __flags, mode_t __mode) __INTRODUCED_IN(28);
int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t* __actions, int __fd) __INTRODUCED_IN(28);
int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t* __actions, int __fd, int __new_fd) __INTRODUCED_IN(28);

#endif /* __ANDROID_API__ >= 28 */

__END_DECLS

#endif
