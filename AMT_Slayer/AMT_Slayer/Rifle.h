#pragma once
#include "Repository.cpp"
#include "WeaponState.cpp"
class Rifle
{
private:
	const int _maxAmmo = 35;	//max ammo w magazynku
	const int _reloadTime = 50; //prze³adowanie w klatkach
	WeaponState _weaponState;
	int _ammoInMag;
public:
	bool realod();
	bool fire();

};

