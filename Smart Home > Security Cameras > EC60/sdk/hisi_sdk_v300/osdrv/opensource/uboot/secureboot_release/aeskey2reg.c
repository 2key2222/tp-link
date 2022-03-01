#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MaxCols 80

int getlinetxt(FILE *fp,int line,char *stri){
    int i;
    fseek(fp,0,0);
    for(i=0;i<line;i++) 
        if(fgets(stri,MaxCols,fp)==NULL)
            return -2;
    return strlen(stri);
}

int main(int argc, char **argv)
{
	int i,j;
	char buffer[0x100];
	int buf[32];
	int *tmp = buf;
	FILE *fp1 = NULL;
	char *input_file = argv[1];

	printf("==================================================================================\n");
	if (argc != 2) {
		printf("input err!!!!!!!!!!!!!!!! \n");
		printf("usage: %s filename\n",argv[0]);
		exit(-1);
	}
	printf("input_file:%s\n",input_file);

	fp1 = fopen(input_file, "r");
	if (fp1 == NULL) {
		printf("open file failed!\n"); 
		return -1; 
	}
#if 0
	sprintf(buffer,"cat %s",input_file);
	printf("%s\n",buffer);
	printf("==================================================================================\n");
	system(buffer);
	printf("==================================================================================\n");
#endif
    int ii;
    char tmp_buf[80];
#define MAX_ROW 100
    for(ii=0;ii<MAX_ROW;ii++) {
        getlinetxt(fp1,ii,tmp_buf);
            if(memcmp(tmp_buf,"KEY=",4))
                continue;
            else
                break;
    }
    if(memcmp(tmp_buf,"KEY=",4)) {
        printf("ERROR: not find KEY=XXXX string!!!\n");
	    fclose(fp1);
    }
    tmp_buf[79]='\0';

	sscanf(tmp_buf,"KEY=%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
			tmp + 0, tmp + 1, tmp + 2, tmp + 3, tmp + 4, tmp + 5, tmp + 6, tmp + 7, tmp + 8, tmp + 9, tmp + 10, tmp + 11, tmp + 12, tmp + 13, tmp + 14, tmp + 15, 
			tmp + 16 + 0, tmp + 16 + 1, tmp + 16 + 2, tmp + 16 + 3, tmp + 16 + 4, tmp + 16 + 5, tmp + 16 + 6, tmp + 16 + 7, tmp + 16 + 8, tmp + 16 + 9, tmp + 16 + 10, tmp + 16 + 11, tmp + 16 + 12, tmp + 16 + 13, tmp + 16 + 14, tmp + 16 + 15
            );
#if 1
	printf("==================================================================================\n");
	printf("AES KEY:\n");
	for (i = 0; i < 32; i++)
		printf("%02x", buf[i]);
	printf("\n");
	printf("==================================================================================\n");
#endif
	printf("==================================================================================\n");
	printf("AES KEY REG VALUE:\n");
	for (i = 0; i < 8; i++) {
		for (j = 3; j >= 0; j--) {
			if (j == 3)
				printf("mw 0x100900%02x 0x", (i * 4) + 0xc);
			printf("%02x", buf[i * 4 + j]);
			if (j == 0)
				printf("\n");
		}
	}
	printf("==================================================================================\n");
	
	fclose(fp1);
	return 0;
}

