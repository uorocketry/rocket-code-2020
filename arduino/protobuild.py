import os
import shutil

print("Building UORocketry Protobuf files...")

if os.path.exists('./lib/RocketryProto'):
    shutil.rmtree('./lib/RocketryProto')

os.mkdir('./lib/RocketryProto')
os.system('protoc --nanopb_out=-I../protobuf:./lib/RocketryProto/ -I=../protobuf ../protobuf/ArduinoComm.proto')
