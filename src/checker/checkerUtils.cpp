/**
 * @author: Achraf El Khnissi
 * @date: Thursday, 5 March 2023
*/

#include "Checker.hpp"

namespace alx
{
	int Checker::createDirectory(const std::string& path)
	{
		if (access(path.c_str(), F_OK) == -1) {
			return mkdir(path.c_str(), 0777);
		}
		return 0;
	}

	int Checker::compile(const std::string& file, const std::string& output)
	{
		std::string command = "gcc -I . " + _CFLAGS + " " + file + " -o " + output;
		std::cout << "Compile command: " << command << std::endl;
		return system(command.c_str());
	}

	int Checker::diff(const std::string& correctOutput, const std::string& output)
	{
		std::string diffCommand = "diff -u " + correctOutput + " " + output;
		std::cout << "Diff command: " << diffCommand << std::endl;
		return system(diffCommand.c_str());
	}

	std::string Checker::_getBasename(const std::string& path) const {
		size_t pos = path.find_last_of("/\\");
		if (pos != std::string::npos) {
			return path.substr(pos + 1);
		}
		return path;
	}

	std::string Checker::getParentDirectory(const std::string& path) {
	    std::string parent_dir;
	    size_t last_slash_pos = path.rfind('/');
	    if (last_slash_pos != std::string::npos) {
	        parent_dir = path.substr(0, last_slash_pos);
	    }
	    return _getBasename(parent_dir);
	}

	bool Checker::directoryExists(const std::string &path) const {
        struct stat info{};
        if (stat(path.c_str(), &info) != 0) {
            return false;
        } else if (info.st_mode & S_IFDIR) {
            return true;
        } else {
            return false;
        }
    } /* directoryExists */

	std::string Checker::_getMainFile(const std::string& file) const {

		// get hyphen position
		std::size_t hyphenPos = file.find('-');
		if (hyphenPos == std::string::npos || hyphenPos == 0) {
			throw std::runtime_error("Invalid file name: " + file);
		}

		// get main file name
		std::string mainFile = "test_files/" + file.substr(0, hyphenPos) + "-main.c";

		// if it doesn't exist return empty string
		if (!std::filesystem::exists(mainFile))
			return "";

		return mainFile;
	}

	std::string Checker::_getCurrentDirectory() const {
		char buff[FILENAME_MAX];
		getcwd(buff, FILENAME_MAX);
		return {buff};
	}

	bool Checker::_checkScript(const std::string& file) const {

		std::ifstream f(file);
		std::string line;
		int count = 0;


		const std::string specialChars = "&&||;";
		bool shebang = true;
		bool endsWithNewLine = true;
		bool hasSpecialChars = false;

		while (std::getline(f, line)) {

			// check if the file has a shebang
			if (count == 0 && line != "#!/bin/bash")
				shebang = false;

			// check if the file has special characters
			if (count == 1 && line.find_first_of(specialChars) != std::string::npos)
				hasSpecialChars = true;

			count++;
		}
		f.close();

		std::ifstream f2(file);
		std::string fileContent;
		char c;
		int newLineCount = 0;
		while (f2.get(c)) {
			if (c == '\n')
				newLineCount++;
			fileContent += c;
		}
		f2.close();

		std::cout << "newLineCount: " << newLineCount << std::endl;
		if (fileContent.at(fileContent.size() - 1) != '\n')
			endsWithNewLine = false;


		std::string result = (newLineCount == 2) ? "OK" : "KO";
		std::cout << "2 lines: " << result << std::endl;

		result = (shebang) ? "OK" : "KO";
		std::cout << "Shebang: " << result << std::endl;

		result = (endsWithNewLine) ? "OK" : "KO";
		std::cout << "Ends with a new line: " << result << std::endl;

		result = (hasSpecialChars) ? "KO" : "OK";
		std::cout << "Has special characters: " << result << std::endl;

		return (newLineCount == 2 && shebang && endsWithNewLine && !hasSpecialChars);
	}

} /* alx namespace */
