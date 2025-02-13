using System;
using System.Collections.Generic;

class Personne
{
    public string Nom { get; set; }
    public int Age { get; set; }
}

class Program
{
    static void Main(string[] args)
    {
        var personnes = new List<Personne>
        {
            new Personne { Nom = "Dupont", Age = 30 },
            new Personne { Nom = "Martin", Age = 25 }
        };

        foreach (var personne in personnes)
        {
            Console.WriteLine(personne.Nom + " a " + personne.Age + " ans");
        }
    }
}
