#include <stdio.h>
 
int main() {
    const int max = 100;
    char line[max], firstName[50], lastName[50], phoneNumber[50];    
    FILE *in = fopen("phone.txt", "r");
    while (!feof(in)) {
        fgets(line, max, in);
        sscanf(line, "%s %s %s", firstName, lastName, phoneNumber);
        printf("%-6s %-10s %-10s", "Name: ", firstName, lastName);
        printf("%10s %-12s\n", "Number: ", phoneNumber);
    }
    fclose(in);
}

#include <stdio.h>
 
int main() {
    const int max = 100;
    char line[max], name[50];
    int number;
    FILE *in = fopen("phone2.txt", "r");
    fgets(line, max, in);
    while (!feof(in)) {
        sscanf(line, "%[^,], %d", name, &number);
        printf("%-6s %-20s", "Name: ", name);
        printf("%10s %-12d\n", "Number: ", number);
        fgets(line, max, in);
    }
    fclose(in);
}
