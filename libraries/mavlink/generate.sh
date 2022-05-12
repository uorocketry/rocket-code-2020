# This file needs to be ran anytime the MAVLink message definitions are changed.
# First, install the needed utility: pip install pymavlink

mavgen.py --lang=C++11 --wire-protocol=2.0 --output=./generated ../protobuf-definitions/mavlink/uorocketry.xml