#include <string>
#include <fstream>
#include "Control.hpp"

namespace Config
{
    template<typename T, typename U> //T = defaultValue type , U = Handler
    class Config
    {
    	public:
            
            enum errorHandler{
                THROW_EXCEPTIONS,
            };
            
            /**
             * Config:
             * @param filename
             * @param errorHandler
             */
            Config(std::string filename, errorHandler error) : errors_(error) 
            { 
                fileHandle_.open(filename, std::fstream::in); 
            }
            
            
            void load(std::string);
            void read(std::string, Control);    		
            void read(std::string, Control, T);
            void read(std::string, Control, U);
            void read(std::string, Control, T, U);
            void write(Control);
    	
    private:
            std::ifstream fileHandle_;
            errorHandler errors_;

    };

}