using System;

class Program
{
    static void Main()
    {
        int x = 19;
        int y = 20;

        if (x > y)
        {
            Console.WriteLine($"{x} is greater than {y}");
        }
        else if (x < y)
        {
            Console.WriteLine($"{y} is greater than {x}");
        }
        else
        {
            Console.WriteLine($"{x} and {y} are equal");
        }
    }
}
