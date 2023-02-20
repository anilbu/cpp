// #pragma once

#include "car.h"
#include "nutility.h"
#include <iostream>

namespace nec::car_v1 {

void Bmw::start()
{
	std::cout << "Bmw has just started\n";
}

void Bmw::run()
{
	std::cout << "Bmw is running\n";
}

void Bmw::stop()
{
	std::cout << "Bmw has just stopped\n";
}

Bmw* Bmw::clone()
{
	return new Bmw;
}

void Bmw::print(std::ostream& os)const
{
	os << "I am a Bmw\n";
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

void Dacia::start()
{
	std::cout << "Dacia has just started\n";
}

void Dacia::run()
{
	std::cout << "Dacia is running\n";
}

void Dacia::stop()
{
	std::cout << "Dacia has just stopped\n";
}

void Dacia::print(std::ostream& os)const
{
	os << "I am a Dacia\n";
}

Dacia* Dacia::clone()
{
	return new Dacia;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

void Volvo::start()
{
	std::cout << "Volvo has just started\n";
}

void Volvo::run()
{
	std::cout << "Volvo is running\n";
}

void Volvo::stop()
{
	std::cout << "Volvo has just stopped\n";
}

void Volvo::print(std::ostream& os)const
{
	os << "I am a Volvo\n";
}

Volvo* Volvo::clone()
{
	return new Volvo;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

void Mercedes::start()
{
	std::cout << "Mercedes has just started\n";
}

void Mercedes::run()
{
	std::cout << "Mercedes is running\n";
}

void Mercedes::stop()
{
	std::cout << "Mercedes has just stopped\n";
}

void Mercedes::open_sunroof()
{
	std::cout << "Mercedes'in cam tavani acildi\n";
}

void Mercedes::print(std::ostream& os)const
{
	os << "I am a Mercedes\n";
}

Mercedes* Mercedes::clone()
{
	return new Mercedes;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

void MercedesS500::start()
{
	std::cout << "MercedesS500 has just started\n";
}

void MercedesS500::run()
{
	std::cout << "MercedesS500 is running\n";
}

void MercedesS500::stop()
{
	std::cout << "MercedesS500 has just stopped\n";
}

void MercedesS500::print(std::ostream& os)const
{
	os << "I am a MercedesS500\n";
}

MercedesS500* MercedesS500::clone()
{
	return new MercedesS500;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

void Renault::start()
{
	std::cout << "Renault has just started\n";
}

void Renault::run()
{
	std::cout << "Renault is running\n";
}

void Renault::stop()
{
	std::cout << "Renault has just stopped\n";
}

void Renault::print(std::ostream& os)const
{
	os << "I am a Renault\n";
}

Renault* Renault::clone()
{
	return new Renault;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

void Fiat::start()
{
	std::cout << "Fiat has just started\n";
}

void Fiat::run()
{
	std::cout << "Fiat is running\n";
}

void Fiat::stop()
{
	std::cout << "Fiat has just stopped\n";
}

void Fiat::print(std::ostream& os)const
{
	os << "I am a Fiat\n";
}

Fiat* Fiat::clone()
{
	return new Fiat;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Car& c)
{
	c.print(os);
	return os;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

Car* create_random_car()
{
	Irand rand{ 0, 6 };

	switch (rand()) {
	case 0: return new Bmw;
	case 1: return new Mercedes;
	case 2: return new MercedesS500;
	case 3: return new Fiat;
	case 4: return new Renault;
	case 5: return new Dacia;
	case 6: return new Volvo;
	default: return nullptr;
	}
}

}