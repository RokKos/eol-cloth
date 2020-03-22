/*
* @author: Gustavo Lopez 10-21-17
*
* @version: 1.0
*/

#pragma once

namespace EOL {

	class Brenderable
	{
	public:
		Brenderable() {};
		virtual ~Brenderable() {}
		virtual int getBrenderCount() const { return 1; }
		virtual std::vector<std::string> getBrenderNames() const { return std::vector<std::string>(1, ""); }
		virtual void exportBrender(std::vector< std::shared_ptr< std::ofstream > > outfiles) const = 0;
	private:

	};
}