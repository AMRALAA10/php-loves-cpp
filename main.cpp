#include <phpcpp.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "miaxis_api.h"

/**
 * To build 
 * rm main.o fingerprintmatcher.so && make && sudo make install
*/

/*
*  Get the sdk version, this is usful to check the verion in php so 
*  you make sure that you are using the correct functions
*/
Php::Value sdk_version()
{    
    char version[100] = {0};
    mxGetVersion(version);
    return version;
}

/**
 * Base 64 finger print matcher
 * you should pass 2 strings in base 64 of 2 finger prints
 * this function returns 0 when he match success, 
 * any other number otherwise
 */
Php::Value matcher_Base64(Php::Parameters &params){
    /*
        unsigned char tz[344+1] = {0};
    	unsigned char mb[344+1] = {0};
        ret = mxFingerMatchBase64(mb,tz,3);
        if (ret != 0)
        {
            m_static_info.SetWindowText("match failed");
        }
        else
        {
            m_static_info.SetWindowText("match success");	
        }
    */
    std::string print1 = params[0];
    std::string print2 = params[1];
    
    unsigned char p1[344+1];
    unsigned char p2[344+1];

    copy(print1.begin(), print1.end(), p1);
    copy(print2.begin(), print2.end(), p2);
    
    // pass 3 params
    // first 2 is the 2 fingerprints strings
    // third one the  security level
    return mxFingerMatchBase64(p1, p2, 3);
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
        // this have to be static
        static Php::Extension extension("fingerprintmatcher", "1.0");

        //add sdk version function
        extension.add<sdk_version>("sdk_version");

        //base64 fingerprint matcher
        extension.add<matcher_Base64>("matcher_Base64");


        // return the extension details
        return extension;
    }
}