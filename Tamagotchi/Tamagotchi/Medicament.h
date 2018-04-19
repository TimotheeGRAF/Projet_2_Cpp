/**
* \file         Medicament.h
* \author		Timothee
* \version		1.09
* \date			19 Avril 2018
* \brief		Definit la classe Medicament et ses particularites
*
* \details		Cette classe contient la definition du type de medicament
*/
#pragma once

class Medicament
{
public:
	Medicament();
	~Medicament();

	/**
	* \brief     Types de medicaments possibles pour un Medicament.
	* \details   La table de correspondance des types de medicaments est disponible en modification par les getters et setters.
	*/
	enum typeMedicament
	{
		antidepresseur,	/*!< xanax*/
		hyperproteine,	/*!< medkit*/
		stimulant		/*!< guronsan*/
	};

private:

protected:


};