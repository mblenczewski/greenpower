

class Packet:
    """
    A class encapsulating a data packet.
    """
    pass


class PacketBuilder:
    """
    A static factory class for serialising and deserialising data packets.
    """

    terminator = ''
    """ The terminator character used to signal the end of a data packet. """

    @staticmethod
    def deserialise_packet(packet: str) -> Packet:
        """ Deserialises and returns a packet from the given string. """

    @staticmethod
    def serialise_packet(packet: Packet) -> str:
        """ Serialises and returns the string representation of the given data packet. """
