#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXCHAR 1000

int main () {
	
	FILE *fp;
	
	fp = fopen("project.csv","r");
	if(!fp) {
		printf("Not able to open the file.");
		return 1;
	}
	
	char row[MAXCHAR];
	int row_count=0;
	int issues_found=0;
	
	while (fgets(row, MAXCHAR, fp)) {
		row_count++;
		
		if (row_count == 1) continue;
		
		row[strcspn(row, "\n")] = 0;
		
		char *device_id = strtok(row, ",");
        char *type = strtok(NULL, ",");
        char *status = strtok(NULL, ",");
        char *temp_str = strtok(NULL, ",");
        char *error_str = strtok(NULL, ",");
        
        if (device_id && type && status && temp_str && error_str) {
            float temperature = atof(temp_str);
            int error_code = atoi(error_str);
            
            printf("%-10s | %-10s | %-10s | %-12.2f | %-5d\n", 
                   device_id, type, status, temperature, error_code);
                   
            if (strcmp(status, "ERROR") == 0 || strcmp(status, "WARNING") == 0) {
                printf("  [!] WARNING: Device %s (%s) has a status of %s (Error Code: %d).\n", 
                       device_id, type, status, error_code);
                issues_found++;
			}
		}
	}
	
	fclose(fp);
	
	printf("--------------------------------------------------------------\n");
    printf("Total checks: %d\n", row_count - 1);
    printf("Warnings/Errors: %d\n\n", issues_found);
	
	return 0;
}
