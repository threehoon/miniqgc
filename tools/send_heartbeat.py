#!/usr/bin/env python3
"""Send one or more MAVLink HEARTBEAT UDP datagrams for MiniQGC M3 self-test.

Requires: pip install pymavlink

Usage:
  python3 tools/send_heartbeat.py [host] [port] [count]
  python3 tools/send_heartbeat.py 127.0.0.1 14550 5
"""

from __future__ import annotations

import sys
import time


def main() -> int:
    host = sys.argv[1] if len(sys.argv) > 1 else "127.0.0.1"
    port = int(sys.argv[2]) if len(sys.argv) > 2 else 14550
    count = int(sys.argv[3]) if len(sys.argv) > 3 else 3

    try:
        from pymavlink import mavutil
    except ImportError:
        print("pymavlink not installed. Run: pip install pymavlink", file=sys.stderr)
        return 1

    # mavutil.mavlink_connection with udpout sends TO host:port
    master = mavutil.mavlink_connection(f"udpout:{host}:{port}", source_system=1, source_component=1)

    for i in range(count):
        master.mav.heartbeat_send(
            type=mavutil.mavlink.MAV_TYPE_QUADROTOR,
            autopilot=mavutil.mavlink.MAV_AUTOPILOT_PX4,
            base_mode=0,
            custom_mode=0,
            system_status=mavutil.mavlink.MAV_STATE_ACTIVE,
        )
        print(f"sent HEARTBEAT {i + 1}/{count} → {host}:{port}")
        time.sleep(0.5)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
