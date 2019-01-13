using Newtonsoft.Json;
using System.IO;

namespace ViewerLib.Utils
{
    public static class JsonFileHandler
    {
        public static T Deserialise<T>(string serialisedItem)
        {
            return JsonConvert.DeserializeObject<T>(serialisedItem);
        }

        public static string Serialise<T>(T item)
        {
            return JsonConvert.SerializeObject(item, Formatting.Indented);
        }

        public static T Read<T>(string filepath)
        {
            return Deserialise<T>(File.ReadAllText(filepath));
        }

        public static void Write<T>(T item, string filepath)
        {
            File.WriteAllText(filepath, Serialise(item));
        }
    }
}