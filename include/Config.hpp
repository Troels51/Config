#include "Control.hpp"
#include <fstream>

namespace Config
{
    template<typename T, typename U> //T = defaultValue type , U = Handler
    class Config
    {
    	public:
            enum errorHandler{
                Error,

            };
        public:
    		Config(std::string, errorHandler);
    		void load(std::string);
    		void read(std::string, Control);    		
    		void read(std::string, Control, T);
    		void read(std::string, Control, U);
    		void read(std::string, Control, T, U);
    		void write(Control);
    	private:
    		std::ifstream fileHandle;

    };

}