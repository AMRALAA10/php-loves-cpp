
#if defined(_WIN32) || defined(_WIN64)
	#ifndef WINAPI
		#define WINAPI __stdcall
	#endif
#else
	#define WINAPI 
#endif

#ifdef __cplusplus
extern "C" {
#endif

int WINAPI mxGetVersion(char* version);

int WINAPI mxFingerMatch256(unsigned char *fingerdata1, unsigned char *fingerdata2, int level);  

int WINAPI mxFingerMatchBase64(unsigned char *fingerdata1, unsigned char *fingerdata2, int level);  

#ifdef __cplusplus
}
#endif

