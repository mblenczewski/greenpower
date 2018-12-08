from Python.Utils.Packet import Packet, PacketBuilder
from Python.Utils.Serial import SerialHandler


print("Hello World!")
packet: Packet = Packet()
print("Serialisation test:")
print("Serialisation to string: {}".format(PacketBuilder.serialise_packet_string(packet)))
print("Serialisation to bytes: {}".format(PacketBuilder.serialise_packet_bytes(packet)))
print("Deserialisation from string: {}".format(PacketBuilder.deserialise_packet_string(str(packet))))
print("Deserialisation from bytes: {}".format(PacketBuilder.deserialise_packet_bytes(str(packet).encode())))

with SerialHandler() as serial:
    pass
    # serial.open()
    # serial.write(Packet())

print("Goodbye World!")
