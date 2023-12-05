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

            var strings = input.Trim().Split("\n").Select(s => s.TrimEnd()).ToArray();
            
            var seeds = strings[0].Split(": ")[1].Split(' ').Select(s => long.Parse(s)).ToArray();

            var seedRanges = Enumerable.Range(0, seeds.Length / 2).Select(i => new Map(seeds[i * 2], seeds[i * 2], seeds[i * 2 + 1])).ToList();

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

            // part 2
        }
    }
}
