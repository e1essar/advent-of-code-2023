using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace Day06
{
    class Program
    {
        static void Main()
        {
            var input = File.ReadAllText("day06.txt");

            var strings = input
                .Trim()
                .Split("\n")
                .Select(s => s.TrimEnd())
                .ToArray();

            var times = strings[0]
                .Split(':')[1]
                .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                .Select(s => int.Parse(s))
                .ToArray();
            
            var distances = strings[1]
                .Split(':')[1]
                .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                .Select(s => int.Parse(s))
                .ToArray();


            var result = 1;

            for (var i = 0; i < times.Length; i++)
            {
                var time = times[i];
                var distance = distances[i];
                var ways = 0;

                for (var holdTime = 1; holdTime < time; holdTime++)
                    if ((time - holdTime) * holdTime > distance)
                        ways++;

                result *= ways;
            }

            Console.WriteLine(result);
        }
    }
}