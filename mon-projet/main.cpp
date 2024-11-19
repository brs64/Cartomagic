//****************************************************************************
// EN-TETE
//****************************************************************************
/*
 Programme : Cartomagic
 But : Apprendre a programmer et a rediger des algorithmes complexes sur un jeu de cartes base sur la chance. 
 Règles du jeu :  Cartomagic est un jeu de réussite qui se base sur un paquet de 13 cartes magiques. Chaque carte a une valeur entre 1 et 5 et une couleur parmi bleu, vert,
 rouge, violet, jaune ou blanc. Une même carte peut se retrouver plusieurs fois dans le paquet et, à chaque partie, un paquet avec des cartes différentes est généré.
 Au début de la partie, le joueur dispose d'un score de 5 points. Chaque tour se déroule de la manière suivante : Le joueur doit choisir, parmi ses deux cartes,
 celle qui lui rapportera le plus de points ou lui fera perdre le moins de points par rapport à la carte tirée par l'ordinateur. 
 Les règles sont les suivantes :
  - Si le joueur choisit une carte de la même valeur que celle de l'ordinateur, il gagne 1 point ;
  - Si le joueur choisit une carte de la même couleur que celle de l'ordinateur, il gagne un nombre de points égal à la différence entre la valeur de la carte de l'ordinateur et la sienne ;
  - Si le joueur dispose d'une carte identique à celle de l'ordinateur (même couleur ET même valeur) et que le joueur joue cette carte, il gagne directement la partie (victoire jackpot !)
  - Si le joueur choisit une carte ayant une couleur et une valeur différente de celle de l'ordinateur, il perd un nombre de points équivalent à la valeur de la carte qu'il a choisie.
 Le joueur gagne la partie :
  - Si son score atteint ou dépasse 10 points ;
  - S'il dispose d'une carte avec la même valeur et la même couleur que celle de l'ordinateur (carte jackpot).
 Le joueur perd la partie :
  - Si son score tombe à zéro ou moins ;
  - S'il n'y a plus de cartes à tirer dans le paquet;
  - S'il décide d'abandonner la partie.

 Date de derniere modification : 24 octobre 2023
 Auteur : A. Baros / R. Masson
 Remarques : Code conforme aux specification internes redigees par notre binôme
*/

//****************************************************************************
// INCULSION
//****************************************************************************
#include "game-tools.h"
#include <iostream>
using namespace std;

//****************************************************************************
// PROGRAMME PRINCIPAL
//****************************************************************************
int main(void)
{
  
  enum SituationFinJeu {jackpot, victoireScore, defaiteScore, abandon, paquetVide}; // Contient toutes les fins possibles du jeu : Jackpot = victoire par jackpot, abandon = 
  // defaite par abandon, paquetVide = defaite par paquet vide, defaiteScore = defaite par le score, victoireScore = victoire par le score 

  // VARIABLES
  unsigned short int tourCourant = 1;        // Numero du tour actuel de la partie (initialise a 1 au debut de la partie)
  int nbCartesRestantes = 13;                // Contient le nombre de cartes encore dans la pioche (initialise a 13 au debut de la partie)
  int score = 5;                             // Score actuel du joueur (vaut 5 au debut de la partie)
  int valeurSaisieParJ;                      // Contient le choix de carte du joueur
  unsigned short int valeurCarte1;           // Contient la valeur de la carte 1 du joueur
  unsigned short int valeurCarte2;           // Contient la valeur de la carte 2 du joueur
  unsigned short int valeurCarteOrdi;        // Contient la valeur de la carte de l'ordinateur
  unsigned short int numeroCouleur;          // Nombre choisi aleatoirement entre 1 et 6 servant a determiner une couleur pour les cartes
  Couleur couleurCarte1;                     // Contient la couleur de la carte 1 du joueur
  Couleur couleurCarte2;                     // Contient la couleur de la carte 2 du joueur
  Couleur couleurCarteOrdi;                  // Contient la couleur de la carte de l'ordinateur
  unsigned short int valeurCarteJouee;       //	Contient la valeur de la carte jouee par le joueur, sert aussi a creer des cartes
  Couleur couleurCarteJouee;                 // Contient la couleur de la carte jouee par le joueur, sert aussi a creer des cartes
           
  SituationFinJeu finDePartie;                       // Contient la raison de la fin de partie
  
  // INITIALISER LA PARTIE

  // Initialiser les 3 premieres cartes
  for (unsigned short int i = 1; i <= 3; i++)
  {
    // Creer une carte
    valeurCarteJouee = static_cast<unsigned short int>(random(1, 5));  // Attribuer a cette carte une valeur aleatoire comprise entre 1 et 5
    numeroCouleur = static_cast<unsigned short int>(random(1, 6));     // Attribuer a cette carte une couleur aleatoire parmi bleu, vert, rouge, violet, jaune ou blanc (6 couleurs)
    switch (numeroCouleur)
    {
    case 1:
      couleurCarteJouee = bleu;
      break;
    case 2:
      couleurCarteJouee = vert;
      break;
    case 3:
      couleurCarteJouee = rouge;
      break;
    case 4:
      couleurCarteJouee = violet;
      break;
    case 5:
      couleurCarteJouee = jaune;
      break;
    case 6:
      couleurCarteJouee = blanc;
      break;
    }
    
    // Determiner a quelle carte attribuer la valeur et la couleur generee
    switch (i)
    {
    case 1: // Affecter la valeur et la couleur generee et la carte 1 du joueur
      valeurCarte1 = valeurCarteJouee;
      couleurCarte1 = couleurCarteJouee; 
      break; 
    case 2: // Affecter la valeur et la couleur generee et la carte 2 du joueur
      valeurCarte2 = valeurCarteJouee;
      couleurCarte2 = couleurCarteJouee;
      break;
    case 3: // Affecter la valeur et la couleur generee et la carte de l'ordinateur
      valeurCarteOrdi = valeurCarteJouee;
      couleurCarteOrdi = couleurCarteJouee;
      break;
    }
  }
  // Enlever 3 cartes de la pioche
  nbCartesRestantes -= 3; 



  // JOUER LA PARTIE

  // Jouer un tour
  while (true)
  {
    // Afficher toutes les informations du jeu sur le terminal
    // Afficher en couleur "C A R T O M A G I C "
    afficherTexteEnCouleur("C ", bleu, false);
    afficherTexteEnCouleur("A ", vert, false);
    afficherTexteEnCouleur("R ", rouge, false);
    afficherTexteEnCouleur("T ", jaune, false);
    afficherTexteEnCouleur("O ", violet, false);
    afficherTexteEnCouleur("M ", blanc, false);
    afficherTexteEnCouleur("A ", bleu, false);
    afficherTexteEnCouleur("G ", vert, false);
    afficherTexteEnCouleur("I ", rouge, false);
    afficherTexteEnCouleur("C ", jaune, false);
    
    cout << "- Tour " << tourCourant << endl;             // Afficher tourCourant
    cout << "__________________________" << endl << endl; // Afficher "__________________________"

    // Afficher en couleurCarteOrdi "Carte piochee par l'ordinateur : ", valeurCarteOrdi
    cout << "Carte piochee par l'Ordinateur : ";
    afficherNombreEnCouleur(valeurCarteOrdi, couleurCarteOrdi, true); 

    // Afficher "Vos cartes : ", en couleurCarte1 valeurCarte1, en couleurCarte2 valeurCarte2
    cout << "Vos cartes : ";
    afficherNombreEnCouleur(valeurCarte1, couleurCarte1, false);
    cout << "  "; 
    afficherNombreEnCouleur(valeurCarte2, couleurCarte2, true);

    //Afficher "Nombre de cartes restantes dans le paquet : ", nbCartesRestantes
    cout << endl << "Nombre de cartes restantes dans le paquet : " << nbCartesRestantes << endl;
    // Afficher "Votre score : ", score
    cout << "Votre score : " << score << endl << endl;

    // Afficher "Choisissez la carte que vous voulez jouer : "
    cout << "Choisissez la carte que vous voulez jouer : " << endl;
    // Afficher en couleurCarte1 "1 - la carte ", valeurCarte1
    cout << "1- la carte ";
    afficherNombreEnCouleur(valeurCarte1, couleurCarte1, true);
    // Afficher en couleurCarte2 "2 - la carte ", valeurCarte2
    cout << "2- la carte ";
    afficherNombreEnCouleur(valeurCarte2, couleurCarte2, true);
    

    // Jouer une carte
    // Verifier la saisie du joueur
    while (true)
    {
      cout << endl << "Votre choix : "; // Afficher "Votre choix :"
      cin >> valeurSaisieParJ;
      cout << endl;
      if (valeurSaisieParJ >= 0 && valeurSaisieParJ <= 2) 
      {
        break;
      }

      afficherTexteEnCouleur("SAISIE INCORRECTE... RECOMMENCEZ", rouge, true);
      // Afficher "Choisissez la carte que vous voulez jouer : "

      
      cout << "Choisissez la carte que vous voulez jouer : " << endl;
      // Afficher en couleurCarte1 "1 - la carte ", valeurCarte1
      
      
      cout << "1- la carte ";
      afficherNombreEnCouleur(valeurCarte1, couleurCarte1, true);
      // Afficher en couleurCarte2 "2 - la carte ", valeurCarte2
      cout << "2- la carte ";
      afficherNombreEnCouleur(valeurCarte2, couleurCarte2, true);
    }
    
    // Verifier si le joueur abandonne
    if (valeurSaisieParJ == 0)
    {
      finDePartie = abandon;
      break;
    }
      
    // Determiner quelle carte a ete jouee
    if (valeurSaisieParJ == 1)
    {
      valeurCarteJouee = valeurCarte1;
      couleurCarteJouee = couleurCarte1;
    }
    else if (valeurSaisieParJ == 2)
    {
      valeurCarteJouee = valeurCarte2;
      couleurCarteJouee = couleurCarte2;
    }

    // Verifier si le joueur a une victoire par carte jackpot
    if (valeurCarteJouee == valeurCarteOrdi && couleurCarteJouee == couleurCarteOrdi)
    {
      finDePartie = jackpot;
      break;
    }

    // Comparer la carte jouee par le joueur et la carte de l'ordinateur
    if (valeurCarteJouee == valeurCarteOrdi && couleurCarteJouee != couleurCarteOrdi)
    {
      // Le joueur choisit une carte de la meme valeur que celle de l'ordinateur, il gagne 1 point
      score += 1;
      cout << "Votre carte a la meme VALEUR que celle de l'ordinateur : vous gagnez 1 point ! Votre score passe a ";
      afficherNombreEnCouleur(score, rouge, false);
      cout << "." << endl << endl;
    }
    else if (valeurCarteJouee != valeurCarteOrdi && couleurCarteJouee == couleurCarteOrdi)
    {
      // Le joueur choisit une carte de la même couleur que celle de l'ordinateur, il gagne un nombre de points egal a la difference entre la valeur de la carte de l'ordinateur et la sienne
      if (valeurCarteJouee > valeurCarteOrdi)
      {
        score += (valeurCarteJouee - valeurCarteOrdi);
        cout << "Votre carte a la meme COULEUR que celle de l'ordinateur, vous gagnez la difference de points entre votre carte et celle de l'ordinateur soit " << valeurCarteJouee - valeurCarteOrdi << " point(s). Votre score passe a ";
        afficherNombreEnCouleur(score, rouge, false);
        cout << "." << endl << endl;
      }
      else if (valeurCarteJouee < valeurCarteOrdi)
      {
        score += (valeurCarteOrdi - valeurCarteJouee);
        cout << "Votre carte a la meme COULEUR que celle de l'ordinateur, vous gagnez la difference de points entre votre carte et celle de l'ordinateur soit " << valeurCarteOrdi - valeurCarteJouee << " point(s). Votre score passe a ";
        afficherNombreEnCouleur(score, rouge, false);
        cout << "." << endl << endl;
      }
    }
    else if (valeurCarteJouee != valeurCarteOrdi && couleurCarteJouee != couleurCarteOrdi)
    {
      // Le joueur choisit une carte ayant une couleur et une valeur differente de celle de l'ordinateur, il perd un nombre de points equivalent a la valeur de la carte qu'il a choisi.
      score -= valeurCarteJouee;
      cout << "Votre carte est TOTALEMENT DIFFERENTE de celle de l'ordinateur, vous perdez un nombre de points equivalant a la valeur" << endl << "de votre carte soit " << valeurCarteJouee << " points. Votre score passe a ";
      afficherNombreEnCouleur(score, rouge, false);
      cout << "." << endl << endl; 
    }
    pause (5);


    // Verifier si il y a victoire ou defaite par le score
    if (score >= 10)
    {
      finDePartie = victoireScore;
      break;
    }
    else if (score <= 0)
    {
      finDePartie = defaiteScore;
      break;
    }
    

    // Verifier si il reste des cartes piochables
    if (nbCartesRestantes <= 0) 
    {
      finDePartie = paquetVide;
      break;
    }

    // Attribuer une nouvelle carte au joueur et a l'ordinateur
    // Generer 2 nouvelles cartes
    for (unsigned short int i = 1; i <= 2; i++)
    {
      // Generer une nouvelle carte
      valeurCarteJouee = static_cast<unsigned short int>(random(1, 5));  // Attribuer a cette carte une valeur aleatoire comprise entre 1 et 5
      numeroCouleur = static_cast<unsigned short int>(random(1, 6));     // Attribuer a cette carte une couleur aleatoire parmi bleu, vert, rouge, violet, jaune ou blanc (6 couleurs)
      switch (numeroCouleur)
      {
      case 1:
        couleurCarteJouee = bleu;
        break;
      case 2:
        couleurCarteJouee = vert;
        break;
      case 3:
        couleurCarteJouee = rouge;
        break;
      case 4:
        couleurCarteJouee = violet;
        break;
      case 5:
        couleurCarteJouee = jaune;
        break;
      case 6:
        couleurCarteJouee = blanc;
        break;
      }
      
      // Determiner a quelle carte attribuer la valeur et la couleur generee
      if (i == 1) // Affecter la valeur et la couleur generee et la carte 1 du joueur
      {
        valeurCarteOrdi = valeurCarteJouee;
        couleurCarteOrdi = couleurCarteJouee;
      }
      else if (i == 2 && valeurSaisieParJ == 1) // Affecter la valeur et la couleur generee et la carte 2 du joueur
      {
        valeurCarte1 = valeurCarteJouee;
        couleurCarte1 = couleurCarteJouee;
      }
      else if (i == 2 && valeurSaisieParJ == 2) // Affecter la valeur et la couleur generee et la carte de l'ordinateur
      {
        valeurCarte2 = valeurCarteJouee;
        couleurCarte2 = couleurCarteJouee;
      } 
    }
    // Enlever 2 cartes de la pioche
    nbCartesRestantes -= 2; 

    // Passer au tour suivant
    tourCourant++;

    // Effacer le terminal
    effacer();
  }

  // FINIR LA PARTIE
  // Afficher la raison de la fin de la partie
  switch (finDePartie)
  {
  case jackpot:
    afficherTexteEnCouleur("Vous avez gagne la partie grace a une carte Jackpot !!", bleu);
    break;
  case abandon:
    afficherTexteEnCouleur("Vous avez perdu la partie par abandon :-(", rouge);
    break;
  case paquetVide:
    afficherTexteEnCouleur("Vous avez perdu la partie, il ne reste pas suffisament de carte dans le paquet. :-(", rouge);
    break;
  case victoireScore:
    afficherTexteEnCouleur("Vous avez gagne la partie grace a votre score :-)", vert);
    break;
  case defaiteScore:
    afficherTexteEnCouleur("Vous avez perdu la partie, votre score est trop bas :-(", rouge);
    break;
  }
  
  return 0;
}