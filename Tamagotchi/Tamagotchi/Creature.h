/**
* \file			Creature.h
* \author		Timothee
* \version		1.09
* \date			19 Avril 2018
* \brief		Definit la classe Creature et ses particularites
*
* \details		Cette classe contient les methodes necessaires a la creation de la creature
*				 , elle contient aussi la definition de ses stades, statuts et caracteristique.
*			
*/
#pragma once
#include <string>
#include "Nourriture.h"
#include "Medicament.h"
#include <iostream>
#include "SFML\Graphics.hpp"

/**
* \brief     Statuts possibles pour une Creature.
* \details   La table de correspondance des statuts est disponible en modification par les getters et setters.
*/
enum Statut 
{
	idle,		/*!< sans statut particulier*/
	deprime,	/*!< triste*/
	heureux,	/*!< heureux*/
	extenue,	/*!< fatigue*/
	dort,		/*!< dodo*/
	malade		/*!< malade*/
};

/**
* \brief     Stades possibles pour une Creature.
* \details   La table de correspondance des stades est disponible en modification par les getters et setters.
*/
enum Stade
{
	oeuf,		/*!< oeuf*/
	enfant,		/*!< enfant*/
	adulte		/*!< adulte*/
};

using namespace std;

class Creature
{
public:
	Creature();
	~Creature();

	bool enVie = true;

	int compteurClic = 0;

	/**
	* \brief		Donne a la creature cree un nom
	* \details		Creer le nom de la creature
	* \param    nomCrea         string pour le nom.
	*/
	void setNom(string nomCrea);

	/**
	* \brief		Recupere les points de vie
	* \details		Recupere les points de vie actuels de la creature
	* \return		Un \e int representant le montant de points de vie actuels.
	*/
	int getPV();

	/**
	* \brief		Determine les points de vie
	* \details		Determine les points de vie actuels de la creature
	* \param    pdV         int le nombre de points de vie actuels attribue.
	*/
	void setPV(int pdV);

	/**
	* \brief		Recupere les points de vie maximums
	* \details		Recupere les points de vie maximums de la creature
	* \return		Un \e int representant le montant de points de vie maximums.
	*/
	int getPVMax();

	/**
	* \brief		Recupere le nombre de points d'xp max
	* \details		Recupere les points de points d'xp actuels de la creature
	* \return		Un \e int representant le montant de points d'xp actuels.
	*/
	int getExpMax();

	/**
	* \brief		Determine les points d'xp maximums de la creature
	* \details		Determine les points d'xp maximums de la creature
	* \param    expM         int le nombre de points d'xp maximums attribue.
	*/
	void setExpMax(int expM);

	/**
	* \brief		Recupere le nombre de points d'xp actuels
	* \details		Recupere les points de points d'xp actuels de la creature
	* \return		Un \e int representant le montant de points d'xp actuels.
	*/
	int getExpActuel();

	/**
	* \brief		Determine les points d'xp actuels de la creature
	* \details		Determine les points d'xp actuels de la creature
	* \param    expGain         int le nombre de points d'xp actuels attribue.
	*/
	void setExpActuel(int expGain);

	/**
	* \brief		Recupere le niveau actuel
	* \details		Recupere le niveau actuel de la creature
	* \return		Un \e int representant le niveau actuel de la creature.
	*/
	int getNiveau();

	/**
	* \brief		Determine le niveau actuel de la creature
	* \details		Determine le niveau actuel de la creature
	* \param    lvl         int representant le niveau actuel de la creature.
	*/
	void setNiveau(int lvl);

	/**
	* \brief		Recupere le stade d'evolution actuel
	* \details		Recupere le stade d'evolution actuel de la creature
	* \return		Un \e enum representant le stade actuel de la creature.
	*/
	int getStade();

	/**
	* \brief		Determine le stade d'evolution actuel
	* \details		Determine stade d'evolution actuel de la creature
	* \param    stadeCrea         Stade representant le stade d'evolution actuel de la creature.
	*/
	void setStade(Stade stadeCrea);

	/**
	* \brief		Recupere l'energie actuelle
	* \details		Recupere l'energie actuelle de la creature
	* \return		Un \e int representant l'energie actuelle de la creature.
	*/
	int getEnergie();

	/**
	* \brief		Determine l'energie actuelle
	* \details		Determine l'energie actuelle de la creature
	* \param    nrj         int representant l'energie actuelle de la creature.
	*/
	void setEnergie(int nrj);

	/**
	* \brief		Recupere l'energie maximum
	* \details		Recupere l'energie maximum de la creature
	* \return		Un \e int representant l'energie maximum de la creature.
	*/
	int getEnergieMax();

	/**
	* \brief		Recupere la joie actuelle
	* \details		Recupere la joie actuelle de la creature
	* \return		Un \e int representant la joie actuelle de la creature.
	*/
	int getJoie();

	/**
	* \brief		Determine la joie actuelle
	* \details		Determine la joie actuelle de la creature
	* \param    joie         int representant la joie actuelle de la creature.
	*/
	void setJoie(int joie);

	/**
	* \brief		Recupere la joie maximum
	* \details		Recupere la joie maximum de la creature
	* \return		Un \e int representant la joie maximum de la creature.
	*/
	int getJoieMax();

	/**
	* \brief		Recupere le statut de la creature
	* \details		Recupere le statut de la creature
	* \return		Un \e enum representant le statut de la creature.
	*/
	int getStatut();

	/**
	* \brief		Determine le statut actuel de la creature
	* \details		Determine le statut actuel de la creature
	* \param    statut         Statut representant le statut actuel de la creature.
	*/
	void setStatut(Statut statut);

	/**
	* \brief		Recupere la faim actuelle
	* \details		Recupere la faim actuelle de la creature
	* \return		Un \e int representant la faim actuelle de la creature.
	*/
	int getFaim();

	/**
	* \brief		Determine la faim actuelle
	* \details		Determine la faim actuelle de la creature
	* \param    faim         Statut representant la faim actuelle de la creature.
	*/
	void setFaim(int faim);

	/**
	* \brief		Recupere la faim maximum
	* \details		Recupere la faim maximum de la creature
	* \return		Un \e int representant la faim maximum de la creature.
	*/
	int getFaimMax();

	/**
	* \brief		Recupere le nombre de fois où la creature a ete nourrie
	* \details		Recupere le nombre de fois où la creature a ete nourrie
	* \return		Un \e int representant le nombre de fois où la creature a ete nourrie
	*/
	int getNbNourris();

	/**
	* \brief		Determine le nombre de fois où la creature a ete nourrie
	* \details		Determine le nombre de fois où la creature a ete nourrie
	* \param    nbN         int representant le nombre de fois où la creature a ete nourrie
	*/
	void setNbNourris(int nbN);

	/**
	* \brief		Recupere le nombre de fois où la creature a fait ses besoins
	* \details		Recupere le nombre de fois où la creature a fait ses besoins
	* \return		Un \e int representant le nombre de fois où la creature a fait ses besoins
	*/
	int getNbCacas();

	/**
	* \brief		Determine le nombre de fois où la creature a fait ses besoins
	* \details		Determine le nombre de fois où la creature a fait ses besoins
	* \param    nbKK         int representant le nombre de fois où la creature a fait ses besoins
	*/
	void setNbCacas(int nbKK);

	/**
	* \brief		Cette methode sert a incrementer le nombre de besoins fait en fonction du nombre de fois nourris
	* \details		Recupere le nombre de fois nourris, le reinitialise, puis incremente le nombre de caca fait
	* \return		Un \e int representant le nombre de fois où la creature a fait ses besoins
	*/
	int faireCaca();

	/**
	* \brief		En fonction de la nourriture selectionnee dans l'enum, donne a manger
	* \details		Si un type de nourriture est selectionne, la creature augmente ses points de vie, faim et joie, selon le type de nourriture selectionne via switch-case
	* \param    typeNourriture         typeNourriture representant le type d'aliment
	* \param    animal         Creature representant la creature cree dans le jeu
	*/
	void donnerAManger(Nourriture::typeNourriture, Creature animal);

	/**
	* \brief		En fonction du medicament selectionne dans l'enum, soigne la creature
	* \details		Si un type de medicament est selectionne, la creature change son statut via un switch-case
	* \param    typeMedicament       typeMedicament representant le type de medicament
	* \param    animal         Creature representant la creature cree dans le jeu
	* \return		Un \e int representant le nombre de fois où la creature a ete soignee
	*/
	int soigner(Medicament::typeMedicament, Creature animal);

	/**
	* \brief		Cette methode sert a nettoyer les besoins de la creature
	* \details		On remet a 0 le compteur de cacas fait, et on increment le nombre de fois où la creature a ete lavee
	* \return		Un \e int representant le nombre de fois où la creature a ete lavee
	*/
	int laver();

	//int gagnerNiveau(Creature animal);
	//void evoluer(Creature animal, Stade stadeCrea);

private:

	Stade stadeCrea;
	Statut stats;
	string nom;
	int pvMax=100;
	int pvActuel=100;
	int energieMax=100;
	int energieActuel=100;
	int joieMax=100;
	int joieActuel=100;
	int expMax = 50;
	int expActuel=0;
	int niveau = 1;
	int faimMax = 100;
	int faimActuel=100;
	int statut=idle;
	int nbNourris=0;
	int nbCacas=0;
	int nbLave=0;
	int nbSoigne=0;

protected:
};