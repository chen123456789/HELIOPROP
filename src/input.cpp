#include "input.h"

std::string str(PARTICLETYPE p) {
	if (p == NUCLEUS)
		return "nucleus";
	else if (p == LEPTON)
		return "lepton";
	else
		return "unkown type";
}

void Input::set_default_values() {
	output_filename = "output/default.helioprop";
	Anumber = 1;
	Znumber = 1;
}

void Input::set_output_filename() {
	int found = xml_filename.rfind('/');
	if (found == std::string::npos)
		found = -1;
	output_filename = "output/";
	output_filename += std::string(xml_filename, found + 1,
			xml_filename.size() - 4 - (found + 1));
	output_filename += ".helioprop";
}

void Input::load_file(const std::string& filename) {
	xml_filename = filename;
	set_output_filename();
	try {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file( xml_filename.c_str() );
		if (!result) throw PROBINPUT;
		pugi::xml_node root = doc.child("Helioprop");
		if (!root) throw NOHELIOPROP;
		load_input(root);
		print();
	} catch (int e) {
		if (e == PROBINPUT)
			std::cerr << "Error reading XML card: " << xml_filename << "\n";
		if (e == NOHELIOPROP)
			std::cerr << "Error reading XML card: Root element Helioprop not found" << "\n";
	}
}

void Input::load_input(pugi::xml_node root) {
	seed = childIntValue(root, "RandomGeneratorSeed", seed);
	Rmax = childDoubleValue(root, "HeliosphereRadius", Rmax);
	dt = childDoubleValue(root, "TimeStep", dt);
	kenergyn_min = childDoubleValue(root, "KEnergyNucMin", kenergyn_min);
	kenergyn_max = childDoubleValue(root, "KEnergyNucMax", kenergyn_max);
	kenergyn_size = childIntValue(root, "KEnergyNucSize", kenergyn_size);
	particle_number = childIntValue(root, "ParticleNumber", 1000);
	Znumber = childIntValue(root, "ParticleCharge", 1);
	Anumber = childIntValue(root, "ParticleAtomicNumber", 1);
	if (Anumber == 0)
		particle_type = LEPTON;
	else
		particle_type = NUCLEUS;
	lambda_par = childDoubleValue(root, "ParallelMfp", lambda_par);
	MagField = childDoubleValue(root, "BfieldAtSun", MagField);
	delta = childDoubleValue(root, "Delta", delta);
	Kperp_factor = childDoubleValue(root, "PerpendicularDiffusion", Kperp_factor);
	/*		rig_break = false;
		b = 0.;
		c = 0.;
		el1 = tixmlel->FirstChildElement("Break");
		if (el1) {
			rig_break = true;
			b = QueryDoubleAttribute("b", el1);
			c = QueryDoubleAttribute("c", el1);
		}
	 */
	polarity = childDoubleValue(root, "Polarity", polarity);
	tiltangle = childDoubleValue(root, "TiltAngle", tiltangle);
}

void Input::print() {
	std::cout << "Setting list" << "\n";
	std::cout << "- Output file : " << output_filename << "\n";
	std::cout << "- RNG seed : " << seed << "\n";
	std::cout << "- time step = " << dt << "\n";
	std::cout << "- heliosphere radius = " << Rmax << "\n";
	std::cout << "- KEnergy size = " << kenergyn_size << "\n";
	std::cout << "- KEnergy max  = " << kenergyn_max << "\n";
	std::cout << "- KEnergy min  = " << kenergyn_min << "\n";
	std::cout << "- particle number = " << particle_number << "\n";
	std::cout << "- charge = " << Znumber << "\n";
	std::cout << "- atomic number = " << Anumber << "\n";
	std::cout << "- type = " << str(particle_type) << "\n";
	std::cout << "- parallel mean free path = " << lambda_par << "\n";
	std::cout << "- B field at Sun = " << MagField << "\n";
	std::cout << "- delta = " << delta << "\n";
	std::cout << "- perpendicular diffusion = " << Kperp_factor << "\n";
	std::cout << "- polarity = " << polarity << "\n";
	std::cout << "- tilt angle = " << tiltangle << "\n";
}
