#pragma once

/// Thin include wrapper for official MAVLink C headers (ADR 0001).
/// Mirrors the idea of QGC `src/MAVLink/MAVLinkLib.h`: one place to silence
/// packed-member warnings and pin dialect includes.

#ifdef __GNUC__
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Waddress-of-packed-member"
#    pragma GCC diagnostic ignored "-Wpedantic"
#endif

// c_library_v2 root is on the include path; common dialect provides HEARTBEAT.
#include <common/mavlink.h>

#ifdef __GNUC__
#    pragma GCC diagnostic pop
#endif
