#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Define the maximum number of characters per line
#define MAXCHAR 1000

int main () {
	
	FILE *fp;

	// Open the CSV file in read mode
	fp = fopen("project.csv","r");

	// Check if the file was opened successfully
	if(!fp) {
		printf("Not able to open the file.");
		return 1; // Exit the program with an error code
	}
	
	char row[MAXCHAR];
	int row_count=0;
	int issues_found=0;

	// Read the file line by line until the end
	while (fgets(row, MAXCHAR, fp)) {
		row_count++;

		// Skip the first row (header row of the CSV)
		if (row_count == 1) continue;

		// Remove the trailing newline character from the current row
		row[strcspn(row, "\n")] = 0;

		// Tokenize the string using comma as the delimiter
		char *device_id = strtok(row, ",");
        char *type = strtok(NULL, ",");
        char *status = strtok(NULL, ",");
        char *temp_str = strtok(NULL, ",");
        char *error_str = strtok(NULL, ",");

		// Ensure all fields are present before processing to prevent segmentation faults
        if (device_id && type && status && temp_str && error_str) {
            float temperature = atof(temp_str); // Convert strings to appropriate numeric types
            int error_code = atoi(error_str);

			// Print the parsed data in a formatted table row
            printf("%-10s | %-10s | %-10s | %-12.2f | %-5d\n", 
                   device_id, type, status, temperature, error_code);

			// Commissioning logic: Flag devices that are not in normal operational status
            if (strcmp(status, "ERROR") == 0 || strcmp(status, "WARNING") == 0) {
                printf("  [!] WARNING: Device %s (%s) has a status of %s (Error Code: %d).\n", 
                       device_id, type, status, error_code);
                issues_found++;
			}
		}
	}

	// Close the file to free up system resources
	fclose(fp);

	// Print the final summary report
	printf("--------------------------------------------------------------\n");
    printf("Total checks: %d\n", row_count - 1);
    printf("Warnings/Errors: %d\n\n", issues_found);
	
	return 0; // Exit successfully
}
