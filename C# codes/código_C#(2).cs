using System;
class Program
{
    static void Main()
    {
        // Pregunta el nombre del usuario
        Console.Write("What's your name? ");
        string name = Console.ReadLine();

        // Pregunta la edad del usuario
        Console.Write("How old are you? ");
        string ageText = Console.ReadLine(); // Fución leer 'Console.ReadLine()'
        int age = Convert.ToInt32(ageText); // Convierte la respuesta a entero (base 32 bits ya que no es un valor grande)

        // Crear condición en base a edad
        if (age >= 18)
        {
            Console.WriteLine("Welcome, " + name + "! You're an adult.");
        }
        else
        {
            Console.WriteLine("Hey there, " + name + "! You're still a youngster!");
        }

        // Meramente mantener la consola abierta e indicar cómo salir
        Console.WriteLine("Press any key to exit.");
        Console.ReadKey();
    }
}
