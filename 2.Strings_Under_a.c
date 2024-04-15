#include <stdio.h>
#include <string.h>

int recognize_a_star(char str[]) {
    int i = 0;
    while (str[i] == 'a') {
        i++;
    }
    return (str[i] == '\0');
}

int recognize_a_star_b_plus(char str[]) {
    int i = 0;
    while (str[i] == 'a') {
        i++;
    }
    while (str[i] == 'b') {
        i++;
    }
    return (str[i] == '\0');
}

int recognize_abb(char str[]) {
    int i = 0;
    while (str[i] == 'a'&&i<1) {
        i++;
    }
    if (str[i] == 'b') {
        i++;
    }
    if (str[i] == 'b') {
        i++;
    }
    return (str[i] == '\0');
}

int main() {
    char str[100];
    
    printf("Enter a string: ");
    scanf("%s", str);
    
    if (recognize_a_star(str)) {
        printf("The string matches the regular expression 'a*'\n");
    }
     else if (recognize_abb(str)) {
        printf("The string matches the regular expression 'abb'\n");
    }
     else if (recognize_a_star_b_plus(str)) {
        printf("The string matches the regular expression 'a*b+'\n");
    } else {
        printf("The string does not match any of the regular expressions\n");
    }
    
    return 0;
}
