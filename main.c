#include <sys/statvfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "missing argument!\n");
    return EXIT_FAILURE;
  }

  struct statvfs stats;
  const int rc = statvfs(argv[1], &stats);
  if (rc) {
    fprintf(stderr, "statvfs %s failed with: %s\n", argv[1], strerror(errno));
    return EXIT_FAILURE;
  }

  printf("statvfs '%s' (expressed in 1K-blocks):\n", argv[1]);
  printf("* Total data blocks in filesystem:            %12" PRIu64 " (*)\n", (uint64_t)stats.f_blocks * (stats.f_bsize/1024));
  printf("* Free blocks in filesystem:                  %12" PRIu64 "\n", (uint64_t)stats.f_bfree  * (stats.f_bsize/1024));
  printf("* Free blocks available to unprivileged user: %12" PRIu64 " (*)\n", (uint64_t)stats.f_bavail * (stats.f_bsize/1024));

  printf("* (Total - Free) blocks:                      %12" PRIu64 " (*)\n", (uint64_t)(stats.f_blocks-stats.f_bfree) * (stats.f_bsize/1024));
  printf("* (Total - Available) blocks:                 %12" PRIu64 "\n", (uint64_t)(stats.f_blocks-stats.f_bavail) * (stats.f_bsize/1024));

  printf("* Total inodes in filesystem:                 %12" PRIu64 " (i)\n", (uint64_t)stats.f_files);
  printf("* Free inodes in filesystem:                  %12" PRIu64 " (i)\n", (uint64_t)stats.f_ffree);
  printf("* (Total - Free) inodes in filesystem:        %12" PRIu64 " (i)\n", (uint64_t)(stats.f_files-stats.f_ffree));
  printf("(*) values returned by 'df'\n");
  printf("(i) values returned by 'df -i'\n");

  return EXIT_SUCCESS;
}

