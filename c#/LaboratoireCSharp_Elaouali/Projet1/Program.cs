using MyShapeLibrary;
namespace Projet1
{
    internal class Program
    {
        // La méthode Main est le point d'entrée de l'application
        static void Main(string[] args)
        {
            // Crée une nouvelle instance de Coordonnee avec les valeurs par défaut (0, 0)
            Coordonnee coord1 = new Coordonnee();
            // Crée une nouvelle instance de Coordonnee avec les valeurs (5, 10)
            Coordonnee coord2 = new Coordonnee(5, 10);

            // Affiche les coordonnées de coord1 dans la console
            // Cela affichera (0, 0)
            Console.WriteLine(coord1);

            // Affiche les coordonnées de coord2 dans la console
            // Cela affichera (5, 10)
            Console.WriteLine(coord2);
        }
    }
}
