#include <stdio.h>

void readFirstLineHex(const char *filePath, int bytesPerLine) {
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
			if (i%2 == 0) {
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

int main() {
	const char *filePath = "/home/james/link.txt";
	int bytesPerLine = 16;
	readFirstLineHex(filePath, bytesPerLine);
	return 0;
}
