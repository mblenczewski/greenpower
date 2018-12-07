from typing import Dict, Any
from datetime import datetime

PACKET_ATTRIBUTE_DELIMITER = "|"
""" The character used to delimit serialised properties in the packet. """

PACKET_END = "{EOP}"
""" The character sequence used to signal the end of a data packet. """


class Packet:
    """
    A base class encapsulating a basic data packet.
    Should be overwritten for custom packets.
    If inherited, the __str__ and __dir__ methods should be
    overridden to provide adequate serialisation and
    deserialisation.
    """

    date: str
    """ The date that this packet was sent on. """

    packet_id: int
    """ The id of the packet. """

    def __init__(self, date: datetime = datetime.now, packet_id: int = 0):
        self.date = str(date)
        self.packet_id = packet_id

    def __dir__(self) -> Dict[str, type]:
        """ Overrides the default __dir__ method, to provide a list of all attributes and their values. """
        return self.__dict__

    def __str__(self) -> str:
        """ Overrides the default __str__ method, for serialising the packet to a string. """
        serialised_packet: str = ""
        attribute_list = self.__dir__()
        for attr in attribute_list:
            serialised_packet += attr + ":" + self.__getattribute__(attr) + PACKET_ATTRIBUTE_DELIMITER
        return serialised_packet + PACKET_END


class PacketBuilder:
    """
    A static factory class for serialising and deserialising data packets.
    """

    @staticmethod
    def serialise_packet(packet: Packet) -> str:
        """ Serialises and returns the string representation of the given data packet. """
        return str(packet)

    @staticmethod
    def deserialise_packet(packet: str) -> Packet:
        """ Deserialises and returns a packet from the given string. """
        if packet.find(PACKET_END):
            packet_attributes = Packet().__dir__()  # gets all the packet attributes
            data_packet: Packet  # final packet to return
            delimited_data: str = packet.strip(PACKET_END)
            for serialised_attribute in delimited_data.split(PACKET_ATTRIBUTE_DELIMITER):
                attribute_name: str = serialised_attribute.split(PACKET_ATTRIBUTE_DELIMITER)[0]
                attribute_type: type = packet_attributes[attribute_name]
                attribute_value: Any = serialised_attribute.split(PACKET_ATTRIBUTE_DELIMITER)[1]
                data_packet.__setattr__(attribute_name, attribute_type.)
            return data_packet
        else:
            raise ValueError("Malformed packet given, lacking end delimiter. Packet given: '{}'".format(packet))
