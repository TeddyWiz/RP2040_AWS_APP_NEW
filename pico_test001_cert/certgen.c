#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOWS_SET   0
const char AWS_Cert[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDWTCCAkGgAwIBAgIUNwmWg8ZRMT+kyFYYVXKUl9M7wp0wDQYJKoZIhvcNAQEL\r\n"
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\r\n"
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDQyNDA2MzUy\r\n"
"M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\r\n"
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMxKKYwbt2FxQdMh1vx9\r\n"
"57wyDjaCQZzQ3eZ3Iu6gq/aii7tVZiFHECJE/HpRtaFELaz2DRT3+tXwcPEBwkXz\r\n"
"wvoQVxvqrHnOWD07QsQVaiSZc4olqWHRGMcN+cUKNCbp+AZP0ziWHg02n8bBXtPO\r\n"
"vA4eucF+a4OxFuZW+gq5iG29rlGieE+CzScMyvshFpTDoj5r9p9Vf4FoD7qLTIiE\r\n"
"Rp6xUaif465FIlyCS86cIQI+5Ma4J/jXr8JHPXHdzjsKw1GXjad6DU7LKaGkIG50\r\n"
"X4I6MnZlygEXwF7eT0t2Fm6TizHIxoFBKELVAmr2FpRPWvqonnC+kJdmptu/Bwng\r\n"
"fmECAwEAAaNgMF4wHwYDVR0jBBgwFoAUvalXtIgLUw4lJZKd+QugqU3kiNkwHQYD\r\n"
"VR0OBBYEFLS5YrLSwNcXu2kMlyIi9QusOSjuMAwGA1UdEwEB/wQCMAAwDgYDVR0P\r\n"
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCl71fJ0CK+ZXOzfpuBtVZ9GzVw\r\n"
"cUZdbEPrMA9+Ax1lY4tXBy4RbVe7Gbdk86gj2wF+Fm6vRTeienXHTx/y918vsRpY\r\n"
"2bDMqTDqjtjIGYob9NtDD9I+gglVxNi6wvzqNLQh0ijDi02Z+IlrYopNWT5W74Hi\r\n"
"x1H9RRvmr3aq6xvAQwVI83LgAfy4G8zUxE3YqLyGuTgt3E/ncvjA6yHITYureK1h\r\n"
"jTeVSGgqipcLpvITA7Z8eluK8wfc5yBk9pW2AEk9dmuEuABu64EXq7pCCknrYwXq\r\n"
"Ag/zt/rJg3+VVv+hLSWHXSs5j+LmlbHa36hR6GSq6ysfPvu4h343HM0wCtfT\r\n"
"-----END CERTIFICATE-----\r\n";

// gcc -o certgen certgen.c
// certgen input_certfileName output_certfilename
//ex) ./certgen W59500use1002212269b6d7b06l48l_device_certification.pem.cert client_cert

int FindLineFeed(char *buffer);
int FindLineFeedadd(char *inbuffer, char *outbuffer);

int main(int argc, char *argv[])
{
	char *buffer;
	int size;
	int count;
	char tempfilename[100];
	int LineFeedCnt = 0;
	char *newbuffer;

	//printf("AWS_Cer : \r\n %s<END> \r\n", AWS_Cert);

	printf("Open File [%s] \r\n",argv[1]);
	FILE *fp = fopen(argv[1],"r");

	sprintf(tempfilename,"%s.c",argv[2]);
	printf("Creat File [%s]\r\n", tempfilename);
	FILE *fp1 = fopen(tempfilename,"w");

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	buffer = calloc(size + 1, sizeof(char));
	
	fseek(fp, 0, SEEK_SET);
	count = fread(buffer, size, 1, fp);

	printf(">>%s<< \r\n size %d, count %d \r\n", buffer, size, count);

	LineFeedCnt = FindLineFeed(buffer);
	printf("LineFeed Count = %d\r\n", LineFeedCnt);
    
	newbuffer = calloc(size + 1 + 2 + (LineFeedCnt * 8), sizeof(char));
	FindLineFeedadd(buffer, newbuffer);
	
    #if WINDOWS_SET 
	printf("const char %s[] =\r\n\"%s\r\n", argv[2], newbuffer);
	//fprintf(fp1,"const char %s[] =\r\n\"%s\\r\\n\"; \n", argv[2], newbuffer);
	fprintf(fp1,"const char %s[] =\r\n\"%s", argv[2], newbuffer);
	#else
	printf("const char %s[] =\n\"%s\r\n", argv[2], newbuffer);
	//fprintf(fp1,"const char %s[] =\n\"%s\"\\n;", argv[2], newbuffer);
	fprintf(fp1,"const char %s[] =\n\"%s", argv[2], newbuffer);
	#endif
	#if 0
	fgets(buffer, sizeof(buffer), fp);
	printf(">>%s<<\n",buffer);
	#endif
	fclose(fp);
	fclose(fp1);
	free(buffer);
	free(newbuffer);
	return 0;
}

int FindLineFeed(char *buffer)
{
	int i, count = 0;
	for(i = 0; i < strlen(buffer); i++)
	{
		if(buffer[i] == '\n')
			count++;

	}
	return count;
}

int FindLineFeedadd(char *inbuffer, char *outbuffer)
{
	int i;
	char *p = outbuffer;
	for(i = 0; i < strlen(inbuffer); i++)
	{
		if(inbuffer[i] == '\r')
		{
			continue;
		}
		else if(inbuffer[i] == '\n')
		{
			//#if WINDOWS_SET 
			*p++ = '\\';
			*p++ = 'r';
			//#endif
			*p++ = '\\';
			*p++ = 'n';
			*p++ = '"';
			#if WINDOWS_SET 
			*p++ = '\r';
			#endif
			*p++ = '\n';
			*p++ = '"';
		}
		else
		{
			*p++ = inbuffer[i];
		}
	}
	*(p-2) = ';';
	*(p-1) = 0;
	return 0;
}