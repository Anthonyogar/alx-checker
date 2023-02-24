//
// Created by Achraf El khnissi on 2/24/23.
//

#ifndef ALX_CHECKER_INSTALLER_HPP
#define ALX_CHECKER_INSTALLER_HPP

#include <iostream>		// std::cout, std::cerr
#include <string>		// std::string
#include <vector>		// std::vector
#include <cstdlib>		// EXIT_SUCCESS
#include <unistd.h>		// access, getuid
#include <cstdlib>		// system
#include <fstream>		// std::ifstream
#include <sys/stat.h>	// stat

#include <filesystem>



#include "Print.hpp"
#include "Animation.hpp"

#define STATUS_OK true
#define STATUS_KO false

namespace alx {

	class Installer {

	private:
		mutable std::vector<std::string> _dependencies;
		Animation _animation;
		Print	  _cout;

	public:
		Installer();
		~Installer();

		void install() const;
		void uninstall() const;
		void update() const;
		void usage() const;
		void checkArgs(int argc, char *argv[]) const;
		void check() const;


		std::vector<std::string> getDependencies() const;
		void checkDependencies() const;
		void installDependencies() const;
		void installSvn() const;

		void downloadTests(void) const;

		bool checkBetty() const;
		void installBetty() const;
		bool isRunningAsRoot() const;

		bool isMacos() const;
		bool isLinux() const;

		void installBrew() const;

		void loadingAnimation() const;


	}; /* class Installer */

} /* namespace alx */



#endif //ALX_CHECKER_INSTALLER_HPP
