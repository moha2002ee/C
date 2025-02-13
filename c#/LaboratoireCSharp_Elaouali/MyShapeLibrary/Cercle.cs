using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyShapeLibrary
{
    // La classe Cercle hérite de la classe Forme
    public class Cercle : Forme
    {
        // Variable privée pour stocker le rayon du cercle
        private int _rayon;

        // Propriété pour accéder et modifier le rayon du cercle
        public int Rayon
        {
            get { return _rayon; }
            set { _rayon = value; }
        }

        // Propriété calculée pour obtenir le diamètre du cercle (2 fois le rayon)
        public int Diametre
        {
            get { return _rayon * 2; }
        }

        // Constructeur par défaut qui initialise le rayon à 0
        // et appelle le constructeur de la classe mère Forme
        public Cercle() : base()
        {
            _rayon = 0;
        }

        // Constructeur d'initialisation qui prend un point d'accroche et un rayon
        // et appelle le constructeur de la classe mère Forme
        public Cercle(Coordonnee pointAccroche, int rayon) : base()
        {
            // Initialise le point d'accroche avec la valeur passée en paramètre
            PA = pointAccroche;
            // Initialise le rayon avec la valeur passée en paramètre
            _rayon = rayon;
        }

        // Méthode ToString surchargée pour fournir une représentation textuelle du cercle
        public override string ToString()
        {
            // Retourne une chaîne de caractères décrivant le cercle
            return $"Cercle [PA={PA}, Rayon={_rayon}, Diametre={Diametre}]";
        }
    }
}
