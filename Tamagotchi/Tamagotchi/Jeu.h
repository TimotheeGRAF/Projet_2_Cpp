/**
* \file			Jeu.h
* \author		Timothee
* \version		1.09
* \date			19 Avril 2018
* \brief		Definit la classe Jeu et ses particularites
*
* \details		Cette classe contient les methodes necessaires au lancement du jeu
*				, elle contient aussi une partie des requetes SQL.
*/

#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Creature.h"
#include <iostream>
#include <vector>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Audio\Music.hpp>
#include "sqlite3.h"


class Jeu
{
public:
	Jeu();
	~Jeu();

	/**
	* \brief     Les etats du jeu possibles pour un Jeu.
	* \details   La table de correspondance des etats de jeu est disponible en modification par la methode chooseState.
	*/
	enum gameState {
		game,	/*!< jouer*/
		menu	/*!< ecran titre*/
	};

	bool onMenu = false;
	bool onOptions = false;
	int difficulte = 1;

	/**
	* \brief       Ouvre la base de donnee
	* \details    Ouvre la base de donnee
	*/
	void openDatabase();

	/**
	* \brief       Ferme la base de donnee
	* \details    Ferme la base de donnee
	*/
	void closeDatabase();

	/**
	* \brief       Lance avec SQLite la requete cree
	* \details    Lance avec SQLite3 la requete contenue dans un string
	* \param    query         string contenant la requete SQL
	* \return    Un \e bool representant le succes ou l'echec de la requete
	*/
	bool executeQuery(string query);

	/**
	* \brief       Cree une liaison entre les bindings des valeurs et la base de donnee
	* \details    Cree une liaison entre les bindings des valeurs et la base de donnee
	* \param    s         const string& valeur de l'adresse où le pointeur se trouve
	* \return    Un \e string contenant des quotes afin de liers les bindings dans la requete SQL
	*/
	string quotesql(const string& s);

	/**
	* \brief       Determine l'etat du jeu dans lequel il se trouve
	* \details   Selon une enumeration, le jeu est dans l'un ou l'autre state(jeu ou menu)
	* \param    tamago         Jeu actif
	* \param    state         gameState dans lequel le jeu va se trouver
	* \param    creature         Creature active dans le jeu
	*/
	void chooseState(Jeu tamago, Jeu::gameState state, Creature creature);

	/**
	* \brief       Contient la logique et le deroulement du Jeu a l'ecran titre
	* \details   Contient la logique et le deroulement du Jeu a l'ecran titre avec les boutons
	* \param    creature         Creature utilisee pour le chargement de partie
	*/
	void titlescreen(Creature creature);

	/**
	* \brief       Contient la fenetre de jeu pour jouer : fenetre principale pour l'utilisateur
	* \details    Contient la logique du jeu et les interaction avec Creature, Nourriture et Medicament, contient aussi les graphismes et sons
	* \param    creature         Creature pour le jeu et pouvant etre sauvegardee en BDD
	*/
	void jouer(Creature creature);

	/**
	* \brief       Sauvegarde
	* \details    Sauvegarde en base de donnee la creature active dans jouer(Creature creature) et ses caracteristiques
	* \param    creature         Creature a sauvegarder en base de donnee
	* \return    Un \e bool representant le succes ou non de la sauvgarde.
	*/
	bool save(Creature creature);

	/**
	* \brief       Chargement
	* \details    Charge via la base de donnee les caracteristiques de la creature
	* \return    Un \e Creature representant la creature chargee;
	*/
	Creature load();


private:

	sqlite3 * db;
	string dbfile;

protected:

};