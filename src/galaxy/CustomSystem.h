#ifndef _CUSTOMSYSTEM_H
#define _CUSTOMSYSTEM_H

#include "galaxy/StarSystem.h"
#include "Polit.h"
#include "vector3.h"
#include "fixed.h"

class CustomSystemBody {
public:
	CustomSystemBody();
	~CustomSystemBody();

	std::string            name;
	SystemBody::BodyType   type;
	fixed                  radius; // in earth radii for planets, sol radii for stars
	fixed                  mass; // earth masses or sol masses
	int                    averageTemp; // kelvin
	fixed                  semiMajorAxis; // in AUs
	fixed                  eccentricity;
	fixed                  orbitalOffset;
	bool                   want_rand_offset;
	// for orbiting things, latitude = inclination
	float                  latitude, longitude; // radians
	fixed                  rotationPeriod; // in days
	fixed                  axialTilt; // in radians
	std::string            heightMapFilename;
	int                    heightMapFractal;
	std::vector<CustomSystemBody*> children;

	/* composition */
	fixed metallicity; // (crust) 0.0 = light (Al, SiO2, etc), 1.0 = heavy (Fe, heavy metals)
	fixed volatileGas; // 1.0 = earth atmosphere density
	fixed volatileLiquid; // 1.0 = 100% ocean cover (earth = 70%)
	fixed volatileIces; // 1.0 = 100% ice cover (earth = 3%)
	fixed volcanicity; // 0 = none, 1.0 = fucking volcanic
	fixed atmosOxidizing; // 0.0 = reducing (H2, NH3, etc), 1.0 = oxidising (CO2, O2, etc)
	fixed life; // 0.0 = dead, 1.0 = teeming

	Uint32 seed;
	bool   want_rand_seed;
};

class CustomSystem {
public:
	typedef std::vector<CustomSystem*> SystemList;
	static void Init();
	static void Uninit();
	// XXX this is not as const-safe as it should be
	static const SystemList &GetCustomSystemsForSector(int sectorX, int sectorY, int sectorZ);

	CustomSystem();
	~CustomSystem();

	std::string            name;
    CustomSystemBody*      sBody;
	SystemBody::BodyType   primaryType[4];
	int                    numStars;
	int                    sectorX, sectorY, sectorZ;
	vector3f               pos;
	Uint32                 seed;
	bool                   want_rand_explored;
	bool                   explored;
	Polit::GovType         govType;
	std::string            shortDesc;
	std::string            longDesc;

	bool IsRandom() const { return !sBody; }
};

#endif /* _CUSTOMSYSTEM_H */
