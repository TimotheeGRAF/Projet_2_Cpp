/**
* \file			Nourriture.h
* \author		Timothee
* \version		1.09
* \date			19 Avril 2018
* \brief		Definit la classe Nourriture et ses particularites
*
* \details		Cette classe contient la definition du type de nourriture
*/
#pragma once
#include <iostream>

using namespace std;

class Nourriture
{
public:
	Nourriture();
	~Nourriture();

	/**
	* \brief     Types de nourriture possibles pour une Nourriture.
	* \details   La table de correspondance des types de nourriture est disponible en modification par les getters et setters.
	*/
	enum typeNourriture
	{
		fruit,	/*!< fraise*/
		viande,	/*!< jambon*/
		biscuit	/*!< muffin*/
	};

private:

protected:
	typeNourriture nourriture;
};

