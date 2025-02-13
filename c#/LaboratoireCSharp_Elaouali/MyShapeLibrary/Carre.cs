using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyShapeLibrary
{
    // La classe Carre hérite de la classe Forme
    public class Carre : Forme
    {
        // Variable privée pour stocker la longueur du côté du carré
        private int longueurCote;

        // Propriété pour accéder et modifier la longueur du côté du carré
        public int LongueurCote
        {
            get { return longueurCote; }
            set { longueurCote = value; }
        }

        // Constructeur par défaut qui initialise la longueur du côté à 0
        // et appelle le constructeur de la classe mère Forme
        public Carre() : base()
        {
            longueurCote = 0;
        }

        // Constructeur d'initialisation qui prend un point d'accroche et une longueur de côté
        // et appelle le constructeur de la classe mère Forme
        public Carre(Coordonnee pointAccroche, int longueurCotee) : base()
        {
            // Initialise le point d'accroche avec la valeur passée en paramètre
            PA = pointAccroche;
            // Initialise la longueur du côté avec la valeur passée en paramètre
            longueurCote = longueurCotee;
        }

        // Méthode ToString surchargée pour fournir une représentation textuelle du carré
        public override string ToString()
        {
            // Retourne une chaîne de caractères décrivant le carré
            return $"Carre [PointAccroche={PA}, LongueurCote={longueurCote}]";
        }
    }
}

