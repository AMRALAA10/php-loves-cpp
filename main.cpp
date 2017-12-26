#include <phpcpp.h>
#include <iostream>
#include "miaxis_api.h"

void device_version()
{
    char version[100] = {0};
    mxGetVersion(version);
    Php::out << version << std::endl;
}

/**
 * rm main.o yourextension.so && make && sudo make install
*/

/**
 *  Native function that is callable from PHP
 *
 *  This function gets two parameters: an associative array and a callback.
 *  It does not do anything meaningful, it is just a demonstration function.
 *
 *  @param  params      The parameters passed to the function
 */
void example_function(Php::Parameters &params)
{
    // first parameter is an array
    Php::Value array = params[0];

    // call the PHP array_keys() function to get the parameter keys
    std::vector<std::string> keys = Php::array_keys(array);

    // loop through the keys
    for (auto &key : keys) 
    {
        // output key
        Php::out << "key: " << key << std::endl;
    }

    // call a function from user space
    Php::Value data = Php::call("some_function", "some_parameter");

    // create an object (this will also call __construct())
    Php::Object time("DateTime", "now");

    // call a method on the datetime object
    Php::out << time.call("format", "Y-m-d H:i:s") << std::endl;

    // second parameter is a callback function
    Php::Value callback = params[1];

    // call the callback function
    callback("some","parameter");

    // in PHP it is possible to create an array with two parameters, the first
    // parameter being an object, and the second parameter should be the name
    // of the method, we can do that in PHP-CPP too
    Php::Array time_format({time, "format"});

    // call the method that is stored in the array
    Php::out << time_format("Y-m-d H:i:s") << std::endl;
}

/**
 *  Switch to C context, because the Zend engine expects get get_module()
 *  to have a C style function signature
 */
extern "C" {
    /**
     *  Startup function that is automatically called by the Zend engine
     *  when PHP starts, and that should return the extension details
     *  @return void*
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // the extension object
        static Php::Extension extension("my_extension", "1.0");

        // add the example function so that it can be called from PHP scripts
        extension.add("example_function", example_function);

        //add device version function
        extension.add("device_version", device_version);

        // return the extension details
        return extension;
    }
}