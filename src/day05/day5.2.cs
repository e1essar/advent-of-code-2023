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

            foreach (var key in maps.Keys)
            {
                var list = maps[key];

                list.Add(new Map(0, 0, long.MaxValue));

                var newList = new List<Map>();
                for (int i = 0; i < list.Count; i++)
                {
                    var currList = list[i];
                    var overlaps = Enumerable.Range(0, i)
                        .Select(ii => list[ii])
                        .Where(prevList => prevList.Source <= currList.Source + currList.Range && prevList.Source + prevList.Range >= currList.Source)
                        .ToArray();
                    if (!overlaps.Any())
                    {
                        newList.Add(currList);
                        continue;
                    }
                    else
                    {
                        var offset = currList.Destination - currList.Source;
                        var start = currList.Source;
                        while (start < currList.Source + currList.Range)
                        {
                            var nextStart = overlaps
                                .Where(prevList => prevList.Source + prevList.Range > start)
                                .OrderBy(prevList => prevList.Source)
                                .FirstOrDefault();
                            if (nextStart == null)
                            {
                                newList.Add(new Map(start, start + offset, currList.Source + currList.Range - start));
                                break;
                            }
                            else if (nextStart.Source > start)
                            {
                                newList.Add(new Map(start, start + offset, nextStart.Source - start));
                            }
                            start = nextStart.Source + nextStart.Range;
                        }
                    }
                    maps[key] = newList;
                }
            }

            var convertSeed = new Func<List<Map>, List<Map>, List<Map>>((source, map) =>
            {
                var mapped = new List<Map>();
                foreach (var s in source)
                {
                    foreach (var m in map.OrderBy(m => m.Source))
                    {
                        var targetStart = Math.Max(s.Destination, m.Source);
                        var targetEnd = Math.Min(s.Destination + s.Range, m.Source + m.Range);
                        var range = targetEnd - targetStart;
                        if (range <= 0)
                        {
                            continue;
                        }
                        var targetOffset = m.Destination - m.Source;
                        var sourceOffset = s.Destination - s.Source;
                        mapped.Add(new Map(targetStart - sourceOffset, targetStart + targetOffset, range));
                    }
                }
                return mapped;
            });

            var ranges = seedRanges;
            ranges = convertSeed(ranges, maps["seed-to-soil"]);
            ranges = convertSeed(ranges, maps["soil-to-fertilizer"]);
            ranges = convertSeed(ranges, maps["fertilizer-to-water"]);
            ranges = convertSeed(ranges, maps["water-to-light"]);
            ranges = convertSeed(ranges, maps["light-to-temperature"]);
            ranges = convertSeed(ranges, maps["temperature-to-humidity"]);
            ranges = convertSeed(ranges, maps["humidity-to-location"]);
            var result = ranges
                .Min(range => range.Destination);

            Console.WriteLine(result);
        }
    }
}
