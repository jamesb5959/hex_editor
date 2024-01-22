#include <stdio.h>
#include <string.h>

void printHelp() {
	printf("Usage: program_name [-h] [-hex] <file_path>\n");
	printf("Options:\n");
	printf("  -h      : Print help\n");
	printf("  -hex    : Read and print the first line in hexadecimal\n");
}

void readHex(const char *filePath, int bytesPerLine) {
	FILE *file = fopen(filePath, "rb");
	if (file == NULL) {
		printf("File not found: %s\n", filePath);
		return;
	}
	// Read the first line
	unsigned char buffer[bytesPerLine];
	size_t bytesRead = fread(buffer, 1, bytesPerLine, file);
	size_t offset = 0;
	while (bytesRead > 0) {
	// Print offset
		printf("%08zx: ", offset);
	// Convert the bytes to hex representation
		for (size_t i = 0; i < bytesRead; i++) {
			printf("%02X ", buffer[i]);
			if (i%2 != 0) {
				printf(" ");
			}
		}
    //Print ASCII representation
		printf(" ");
		for (size_t i = 0; i < bytesRead; i++) {
			if (buffer[i] >= 32 && buffer[i] <= 126) {
				printf("%c", buffer[i]);
			} 
			else {
				printf(".");
			}
		}

		printf("\n");
		offset += bytesRead;
		bytesRead = fread(buffer, 1, bytesPerLine, file);
	}	
	fclose(file);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Error: Missing file path argument.\n");
		printHelp();
		return 1;
	}
	int bytesPerLine = 16;
  if (argc >= 2) {
		if (strcmp(argv[1], "-h") == 0) {
			printHelp();
			return 0;
		} 
		else if (strcmp(argv[1], "-hex") == 0) {
			// Call readFirstLineHex function
			const char *filePath = argv[2];
			readHex(filePath, bytesPerLine);
			return 0;
		} 
		else {
			printf("Error: Unknown argument %s\n", argv[2]);
			printHelp();
			return 1;
		}
	}
	printf("Error: Invalid number of arguments.\n");
	printHelp();
	return 1;
}
