from Python.Utils.Packet import Packet, PacketBuilder
from Python.Utils.Serial import SerialHandler

from pprint import pprint

print("Hello World!")
pprint(dir(Packet()))

with SerialHandler() as serial:
    print(PacketBuilder.serialise_packet_string(Packet()))
    print(PacketBuilder.deserialise_packet_string(str(Packet())))
    # serial.open()
    # serial.write(Packet())

print("Goodbye World!")
