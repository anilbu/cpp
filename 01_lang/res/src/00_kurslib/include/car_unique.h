#ifndef CAR_H
#define CAR_H

#include <ostream>
#include <memory>

namespace nec::car_v2 {
	

class Car {
public:
	virtual void start() = 0;
	virtual void run() = 0;
	virtual void stop() = 0;
	virtual ~Car() {}
	virtual Car* clone() = 0;
	virtual void print(std::ostream&)const = 0;
};

//--------------------------------------------------------------------------------------------

class Bmw  : public Car {
public:
	virtual void start() override;
	virtual void run() override;
	virtual void stop() override;
	Bmw* clone() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

class Dacia : public Car {
public:
	virtual void start() override;
	virtual void run() override;
	Dacia* clone() override;
	virtual void stop() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

class Volvo : public Car {
public:
	virtual void start() override;
	virtual void run() override;
	virtual void stop() override;
	Volvo* clone() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

class Mercedes : public Car {
public:
	virtual void start() override;
	virtual void run() override;
	virtual void stop() override;
	void open_sunroof();
	Mercedes* clone() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

class MercedesS500 : public Mercedes {
public:
	virtual void start() override;
	virtual void run() override;
	virtual void stop() override;
	MercedesS500* clone() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

class Renault : public Car {
public:
	virtual void start() override;
	virtual void run() override;
	virtual void stop() override;
	Renault* clone() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

class Fiat : public Car {
public:
	virtual void start() override;
	virtual void run() override;
	virtual void stop() override;
	Fiat* clone() override;
	virtual void print(std::ostream&)const override;
};

//--------------------------------------------------------------------------------------------

std::unique_ptr<Car> createRandomCar(void);

std::ostream& operator<<(std::ostream&, const Car& c);
}

#endif