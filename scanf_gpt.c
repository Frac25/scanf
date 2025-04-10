#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[100]; // Stocke l'entrée utilisateur
    int i = 0, j = 0, n = read(0, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0'; // Ajoute une fin de chaîne pour sécurité

    while (format[i]) {
        if (format[i] == '%') {
            i++;
            if (format[i] == 'd') {  // Lecture d'un entier
                int *val = va_arg(args, int *);
                int negatif = 0, nombre = 0;

                // Gérer les espaces
                while (buffer[j] == ' ' || buffer[j] == '\n')
                    j++;

                // Gérer les nombres négatifs
                if (buffer[j] == '-') {
                    negatif = 1;
                    j++;
                }

                // Convertir en entier
                while (buffer[j] >= '0' && buffer[j] <= '9') {
                    nombre = nombre * 10 + (buffer[j] - '0');
                    j++;
                }

                *val = negatif ? -nombre : nombre;
            }
            else if (format[i] == 'c') {  // Lecture d'un caractère
                char *val = va_arg(args, char *);

                // Ignorer les espaces et sauts de ligne
                while (buffer[j] == ' ' || buffer[j] == '\n')
                    j++;

                *val = buffer[j];
                j++;
            }
            else if (format[i] == 's') {  // Lecture d'une chaîne de caractères
                char *val = va_arg(args, char *);
                int k = 0;

                // Ignorer les espaces et sauts de ligne
                while (buffer[j] == ' ' || buffer[j] == '\n')
                    j++;

                // Lire la chaîne
                while (buffer[j] != ' ' && buffer[j] != '\n' && buffer[j] != '\0') {
                    val[k++] = buffer[j++];
                }
                val[k] = '\0'; // Terminer la chaîne
            }
        }
        i++;
    }

    va_end(args);
    return 0; // Retourner le nombre d'éléments lus peut être une amélioration
}


int main() {
    int nombre;
    char caractere;
    char mot[50];

    // Lecture d'un entier
    write(1, "Entrez un entier : ", 19);
    ft_scanf("%d", &nombre);
    printf("Vous avez entré : %d\n", nombre);

    // Lecture d'un caractère
    write(1, "Entrez un caractère : ", 22);
    ft_scanf("%c", &caractere);
    printf("Vous avez entré : %c\n", caractere);

    // Lecture d'un mot
    write(1, "Entrez un mot : ", 16);
    ft_scanf("%s", mot);
    printf("Vous avez entré : %s\n", mot);

    return 0;
}
