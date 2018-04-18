#include "Creature.h"
#include <string>
#include <iostream>

Creature::Creature()
{
}
Creature::~Creature()
{
}

//GETTEURS ET SETTEURS
	//Nom
	string Creature::getNom()
	{
		return this->nom;
	}
	void Creature::setNom(string nomCrea)
	{
		this->nom = nomCrea;
	}
	//PV
	int Creature::getPV()
	{
		return pvActuel;
	}
	void Creature::setPV(int pdV)
	{
		this->pvActuel = pdV;
	}
	//PVMAX
	int Creature::getPVMax()
	{
		return pvMax;
	}
	//ENERGIE
	int Creature::getEnergie()
	{
		return energieActuel;
	}
	void Creature::setEnergie(int nrj)
	{
		this->energieActuel = nrj;
	}
	//ENERGIEMAX
	int Creature::getEnergieMax()
	{
		return energieMax;
	}
	//JOIE
	int Creature::getJoie()
	{
		return joieActuel;
	}
	void Creature::setJoie(int joie)
	{
		this->joieActuel = joie;
	}
	//JOIE MAX
	int Creature::getJoieMax()
	{
		return joieMax;
	}
	//FAIM
	int Creature::getFaim()
	{
		return faimActuel;
	}
	void Creature::setFaim(int faim)
	{
		this->faimActuel = faim;
	}
	//FAIM MAX
	int Creature::getFaimMax()
	{
		return faimMax;
	}
	//STATUT
	int Creature::getStatut()
	{
		return statut;
	}
	void Creature::setStatut(Statut stats)
	{
		this->statut = stats;
	}
	//NIVEAU
	int Creature::getNiveau()
	{
		return niveau;
	}
	void Creature::setNiveau(int lvl)
	{
		this->niveau = niveau + lvl;
	}
	//STADE
	int Creature::getStade()
	{
		return stadeCrea;
	}
	void Creature::setStade(Stade stadeE)
	{
		this->stadeCrea = stadeE;
	}
	//NOMBRE DE FOIS NOURRIS
	int Creature::getNbNourris()
	{
		return nbNourris;
	}
	void Creature::setNbNourris(int nbN)
	{
		this->nbNourris = nbN;
	}
	//NOMBRE DE CACAS FAIT
	int Creature::getNbCacas()
	{
		return nbCacas;
	}
	void Creature::setNbCacas(int nbKK)
	{
		this->nbCacas = nbKK;
	}
	//XP MAX
	int Creature::getExpMax()
	{
		return expMax;
	}
	void Creature::setExpMax(int expM)
	{
		this->expMax = expM;
	}
	//XP ACTUEL
	int Creature::getExpActuel()
	{
		return expActuel;
	}
	void Creature::setExpActuel(int expGain)
	{
		this->expActuel = expGain;
	}


//METHODES DES INTERACTIONS
	//Faire ses besoins
	int Creature::faireCaca()
	{
		this->nbNourris = 0;
		this->setNbCacas(getNbCacas() + 1);
		return this->getNbCacas();
	}


	//Laver Creature et enlever les étrons
	int Creature::laver()
	{
		this->nbCacas = 0;
		this->joieActuel= this->joieActuel+10;
		if (this->joieActuel >= this->joieMax)
		{
			this->setJoie(this->getJoieMax());
		}
		return this->nbLave++;
	}


	//Donner à manger
	void Creature::donnerAManger(Nourriture::typeNourriture repas, Creature animal)
	{
		switch (repas)
		{
		case Nourriture::fruit:
		
			this->faimActuel += 15;
			if (this->faimActuel > this->faimMax)
			{
				this->faimActuel = this->faimMax;
			}
			this->joieActuel += 15;
			if (this->joieActuel > this->pvMax)
			{
				this->joieActuel = this->joieMax;
			}

			this->pvActuel += 20;
			if (this->pvActuel > this->pvMax)
			{
				this->pvActuel = this->pvMax;
			}

			//this->expActuel += 15;
			//if (this->expActuel > this->expMax)
			//{
			//	animal.gagnerNiveau(animal);
			//	this->expActuel = 0;
			//}
			break;

		case Nourriture::viande:
		
			this->faimActuel += 20;
			if (this->faimActuel > this->faimMax)
			{
				this->faimActuel = this->faimMax;
			}

			this->joieActuel += 15;
			if (this->joieActuel > this->pvMax)
			{
				this->joieActuel = this->joieMax;
			}

			this->pvActuel += 15;
			if (this->pvActuel > this->pvMax)
			{
				this->pvActuel = this->pvMax;
			}

			/*this->expActuel += 15;
			if (this->expActuel > this->expMax)
			{
				animal.gagnerNiveau(animal);
				this->expActuel = 0;
			}*/
			break;

		case Nourriture::biscuit:
		
			this->faimActuel += 15;
			if (this->faimActuel > this->faimMax)
			{
				this->faimActuel = this->faimMax;
			}

			this->joieActuel += 20;
			if (this->joieActuel > this->pvMax)
			{
				this->joieActuel = this->joieMax;
			}

			this->pvActuel -=15 ;

			/*this->expActuel += 15;
			if (this->expActuel > this->expMax)
			{
				animal.gagnerNiveau(animal);
				this->expActuel = 0;
			}*/
			break;

		default:
			break;
		}

		this->setNbNourris(this->getNbNourris() + 1);
	}



	//Soigner Creature et changer statut
	int Creature::soigner(Medicament::typeMedicament medoc, Creature animal)
	{
		switch (medoc)
		{
		case Medicament::typeMedicament::antidepresseur:
			if (animal.getStatut() == deprime)
			{
				animal.setStatut(idle);
			}
			break;
		/*case Medicament::typeMedicament::hyperproteine:
			if (animal.getStatut() == affame)
			{
				animal.setStatut(idle);
			}
			break;*/
		case Medicament::typeMedicament::stimulant:
			if (animal.getStatut() == extenue)
			{
				animal.setStatut(idle);
			}
			break;
		default:
			break;
		}

		return animal.getStatut();
	}

	//// Level Up !
	//int Creature::gagnerNiveau(Creature animal)
	//{
	//	animal.setNiveau(+1);
	//	animal.pvMax = animal.pvMax + 15;
	//	animal.energieMax = animal.energieMax + 10;
	//	animal.joieMax = animal.joieMax + 10;
	//	animal.faimMax = animal.faimMax + 10;
	//	animal.expMax = animal.expMax + 50;
	//
	//	animal.setPV(animal.pvMax);
	//	animal.setEnergie(animal.energieMax);
	//	animal.setJoie(animal.joieMax);
	//	animal.setFaim(animal.faimMax);
	//	animal.setExpActuel(0);
	//
	//	return animal.getNiveau();
	//}

	//Evolution de la créature selon son stade
	//void Creature::evoluer(Creature animal, Stade stadeCrea)
	//{
	//	switch (stadeCrea)
	//	{
	//	case oeuf:
	//		animal.setStade(enfant);
	//		break;
	//
	//	case enfant:
	//		animal.setStade(adulte);
	//		break;
	//
	//	default:
	//		break;
	//	}
	//}