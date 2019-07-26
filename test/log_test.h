#include "../src/log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int log_test_01() {
    struct LogThresholds th;
    th.console_threshold = LEVEL_WARN;
    th.logfile_threshold = LEVEL_DEBUG;

    assert(LEVEL_WARN == highestThreshold(th));

    return 0;
}