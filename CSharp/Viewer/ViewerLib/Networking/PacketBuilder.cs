using System.Text;

namespace ViewerLib.Networking
{
    /// <summary>
    /// Factory class for serialising and deserialising packets to and from
    /// their binary representations.
    /// </summary>
    public static class PacketBuilder
    {
        public static Packet DeserialisePacket(byte[] encodedPacket)
        {
            return new Packet();
        }
    }
}