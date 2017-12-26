
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
						   
/****************************************************************************
	��  ����int  mxGetVersion(char * version)
	��  �ܣ���ȡ�㷨�汾��
	��  ����version  - ����Ϊ100�ֽڵ��ַ���ָ��
	��  �أ�   0     - �ɹ�
              ����   - ʧ��
*****************************************************************************/
int WINAPI mxGetVersion(char* version);

/***************************************************************************
	��	��:	�����������ָ������ֵ���бȶ�
	��	��:	fingerdata1 -  ���룬ָ������ֵ1,256�ֽ�
			    fingerdata2 -  ���룬ָ������ֵ2,256�ֽ�
			     level      -  ����,ƥ��ȼ�
	����ֵ:	   0        -  ƥ��ɹ�
			      -1        -  ƥ��ʧ��
			      -2        -  ���ݷǷ�
****************************************************************************/
int WINAPI mxFingerMatch256(unsigned char *fingerdata1, 
							   unsigned char *fingerdata2,
							   int level);  

/***************************************************************************
	��	��:	�����������ָ������ֵ���бȶ�
	��	��:	fingerdata1 -  ���룬ָ������ֵ1,344�ֽ�base64��
			    fingerdata2 -  ���룬ָ������ֵ2,344�ֽ�base64��
			     level      -  ����,ƥ��ȼ�
	����ֵ:	   0        -  ƥ��ɹ�
			      -1        -  ƥ��ʧ��
			      -2        -  ���ݷǷ�
****************************************************************************/
int WINAPI mxFingerMatchBase64(unsigned char *fingerdata1, 
							   unsigned char *fingerdata2,
							   int level);  

#ifdef __cplusplus
}
#endif

