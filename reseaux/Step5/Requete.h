#include <stdio.h> 

enum TypeRequete { 
       Question = 1 , 
       Achat  = 2 , 
       Livraison= 3 , 
       OK  = 4, 
       Fail = 5  
     } ; 
 
struct Requete 
{ 
  enum TypeRequete Type ; 
  int Numero ; // Contient le numéro de la requete 
  int NumeroFacture ; 
  time_t Date ;  
  int Reference ; // la référence du film 
  int Quantite ; ; 
  int Prix ; 
  char Constructeur[30] ; 
  char Modele[30] ; 
  char NomClient[80] ;  
  char Couleur[10];
} ;  
 
  
void AfficheRequete(FILE *fp, struct Requete R ) 
{ 
 fprintf(fp,">TypeRequete %d \n", R.Type ) ; 
 // fprintf(fp,">Reference %d \n", R.Numero ) ; 
 fprintf(fp,">NumeroFacture %d \n", R.NumeroFacture ) ; 
 // fprintf(fp,">Date %ld \n", R.Date ) ; 
 fprintf(fp,">Reference %d \n", R.Reference ) ; 
 fprintf(fp,">Quantite %d \n", R.Quantite ) ; 
 fprintf(fp,">Prix %d \n", R.Prix ) ; 
 fprintf(fp,">Constructeur %s \n", R.Constructeur ) ; 
 fprintf(fp,">Modele %s \n", R.Modele ) ; 
 fprintf(fp,">Client %s \n\n", R.NomClient ) ; 
  fprintf(fp,">Couleur %s \n\n", R.Couleur ) ; 
 return ; 
}
