using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyShapeLibrary
{
    // La classe Coordonnee représente un point avec des coordonnées X et Y
    public class Coordonnee
    {
        // Variable publique pour stocker la coordonnée X
        public int X;
        // Variable publique pour stocker la coordonnée Y
        public int Y;

        // Constructeur par défaut qui initialise X et Y à 0
        public Coordonnee()
        {
            X = 0;
            Y = 0;
        }

        // Constructeur qui initialise X et Y avec des valeurs données
        public Coordonnee(int x, int y)
        {
            X = x;
            Y = y;
        }

        // Méthode ToString pour obtenir une représentation textuelle des coordonnées
        public override string ToString()
        {
            // Retourne une chaîne de caractères décrivant les coordonnées
            return $"({X}, {Y})";
        }
    }
}
