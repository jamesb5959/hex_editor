#include <stdio.h>
#include <stdlib.h>

void read_binary_file(const char *file_path) {
	FILE *file = fopen(file_path, "rb");
		if (file == NULL) {
			perror("Error opening file");
			return;
		}

		fseek(file, 0, SEEK_END);
		long file_size = ftell(file);
		fseek(file, 0, SEEK_SET);
		char *binary_data = (char *)malloc(file_size);
		if (binary_data == NULL) {
			perror("Error allocating memory");
			fclose(file);
			return;
		}
		size_t bytes_read = fread(binary_data, 1, file_size, file);
		fclose(file);
		if (bytes_read != file_size) {
			perror("Error reading file");
			free(binary_data);
			return;
		}

		// Process binary_data as needed
		printf("Binary content of %s:\n", file_path);
		for (size_t i = 0; i < file_size; i++) {
			printf("%02x ", (unsigned char)binary_data[i]);
		}
		// Cleanup
		free(binary_data);
}
																							
int main() {
	const char *file_path = "hex_editor";
	read_binary_file(file_path);					
	return 0;
}																		
