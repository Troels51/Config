Config
======
Not really valid anymore

 Requirements
 ------------
  
    -   All objects that are streamable may be saved

        class Server { 
          public:
            std::string name;
            int port
        }obj;

        write(obj)

    -   Each node denoted like "Server.ctrl.port"

    -   Read variable in four fashions

        - Two parameter that denotes the name
            
            read("Server.ctrl.name",obj.name)
            
        - Three parameters (name,default_value)

            read("Server.ctrl.name",obj.name,"Server")

        - Three parameters (name,handler) 
          The handler dictates what should happen if the data cannot be read

            read("Server.ctrl.name",obj.name,handler())

        - Four parameters - (name,default_value,handler)

            read("Server.ctrl.name",obj.name,"Server,handler())

    - Exception safety is a must

    - Ensure shared_ptr can be handled both on the reading and writing part



TODO:
Architechture:
Notes:
    User specifies the parser/generator

