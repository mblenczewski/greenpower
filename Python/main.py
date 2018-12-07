from Python.Utils.Packet import Packet, PacketBuilder
from Python.Utils.Serial import SerialHandler

from pprint import pprint

print("Hello World!")
pprint(Packet().__dir__())

with SerialHandler() as serial:
    print("Doot")
    # serial.open()
    # serial.write(Packet())

print("Goodbye World!")
