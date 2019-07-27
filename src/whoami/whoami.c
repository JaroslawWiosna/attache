#include <sys/stat.h>
#include <stdlib.h>
#include "whoami.h"
#include "../log.h"

void whoami(int c, char* v[]) {
    LOGD("Entering function");
    char* configFilepath = "attache.config";
    struct stat* buf = malloc(sizeof(struct stat));

    stat(configFilepath, buf);

    // LOGI("size of file is %d", buf->st_size);
    printf("size of file is %d\n", (int)buf->st_size);

    if ((int)buf->st_size > 0) {
        SLOGI("File %s exists", configFilepath);
    } else {
        SLOGI("File %s does not exist", configFilepath);
    }

    free(buf);

    (void)c;
    (void)v;
}
