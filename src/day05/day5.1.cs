using System;

namespace Day05
{
    class Program
    {
        private class Map
        {
            public long Source { get; }
            public long Destination { get; }
            public long Range { get; }
            public Map(long source, long destination, long range)
            {
                Source = source;
                Destination = destination;
                Range = range;
            }
        }
        static void Main()
        {
            var input = File.ReadAllText("day05.txt");

            var strings = input
                .Trim()
                .Split("\n")
                .Select(s => s.TrimEnd())
                .ToArray();
            
            var seeds = strings[0]
                .Split(": ")[1]
                .Split(' ')
                .Select(s => long.Parse(s))
                .ToArray();
            
            var maps = new Dictionary<string, List<Map>>();
            var map = (string)null;
            foreach (var s in strings.Skip(2))
            {
                if (map == null)
                {
                    map = s.Split(' ')[0];
                    maps[map] = new List<Map>();
                    continue;
                }
                if (string.IsNullOrEmpty(s))
                {
                    map = null;
                    continue;
                }
                var ss = s.Split(' ');
                maps[map].Add(new Map(long.Parse(ss[1]), long.Parse(ss[0]), long.Parse(ss[2])));
            }

            long convertSeed(long num, List<Map> map)
            {
                Map convert = null;
                foreach (var m in map)
                {
                    if (m.Source <= num && m.Source + m.Range >= num)
                    {
                        convert = m;
                        break;
                    }
                }

                return convert != null ? num + convert.Destination - convert.Source : num;
            }

            var result = seeds
                .Select(num => convertSeed(convertSeed(convertSeed(convertSeed(convertSeed(convertSeed(convertSeed(
                    num, maps["seed-to-soil"]), 
                    maps["soil-to-fertilizer"]), 
                    maps["fertilizer-to-water"]), 
                    maps["water-to-light"]), 
                    maps["light-to-temperature"]), 
                    maps["temperature-to-humidity"]), 
                    maps["humidity-to-location"]))
                .Min();

            Console.WriteLine(result);
        }
    }
}
