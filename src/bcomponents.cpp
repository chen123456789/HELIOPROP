#include "bfield.h"

double TBfield::dGamma_dtheta() const {
	return gamma / tan(theta);
} // gamma*cos(theta)*(3.0-pow(cos(theta),2))/(1.0+pow(cos(theta),2));

double TBfield::B_r() const {
	return Ac * B0 * pow(r0 / r, 2) * Heaviside(theta - thetaprime());
}

double TBfield::B_phi() const {
	return -B_r() * gamma;
}

double TBfield::B_total() const {
	return fabs(Heaviside(theta - thetaprime())) * B0 * pow(r0 / r, 2)
	* sqrt(1.0 + gamma_squared); //sqrt(pow(Br(r,theta,phi),2) + pow(Bphi(r,theta,phi),2));
}

double TBfield::dBtotal_dr() const {
	return -B_total() / r * (2.0 + gamma_squared) / (1.0 + gamma_squared);
}

double TBfield::dBtotal_dphi() const {
	return 0;
}

double TBfield::dBtotal_dtheta() const {
	return -B_total() * gamma / (1.0 + gamma_squared) * dGamma_dtheta();
}
