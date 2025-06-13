#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include "ATarget.hpp"

# include <string>
# include <map>

class TargetGenerator
{
	public:
		TargetGenerator();

		void learnTargetType(ATarget*);
		void forgetTargetType(const std::string&);
		ATarget* createTarget(const std::string&);

		~TargetGenerator();
	
	std::map<const std::string, ATarget*> _targets;

	TargetGenerator(const TargetGenerator&);
	const TargetGenerator& operator=(const TargetGenerator&);
};

#endif
