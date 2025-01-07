#include "minishell.h"

// void remove_substring(char *str, const char *substr) {
//     char *pos = ft_strnstr(str, substr, ft_strlen(str)); // Find the first occurrence of substr in str
//     printf("pos is %s\n", pos);
// 	if (pos != NULL) {
//         // Calculate the lengths
//         size_t len_substr = strlen(substr);
//         size_t len_rest = strlen(pos + len_substr);

//         // Shift the remaining part of the string
//         ft_memmove(pos, pos + len_substr, len_rest + 1); // +1 to include null-terminator
//     }
// }

// int main() {
//     char str[100] = "hello $fake hi there";
//     const char *substr = "$fake";

//     printf("Original string: \"%s\"\n", str);
//     remove_substring(str, substr);
//     printf("Modified string: \"%s\"\n", str);

//     return 0;
// }

// Function to replace the first occurrence of a substring with another substring
void replace_substring(char *str, const char *substr, const char *replacement) {
    char buffer[1024]; // Temporary buffer to hold the modified string
    char *pos = ft_strnstr(str, substr, ft_strlen(str)); // Find the first occurrence of substr in str

    if (pos != NULL) {
        // Calculate the lengths
        size_t len_before = pos - str; // Length of the part before the substring
        size_t len_substr = ft_strlen(substr);
        size_t len_replacement = ft_strlen(replacement);

        // Build the new string in the buffer using strlcpy and strlcat
        ft_strlcpy(buffer, str, len_before + 1);         // Copy the part before the substring
        ft_strlcat(buffer, replacement, sizeof(buffer)); // Add the replacement
        ft_strlcat(buffer, pos + len_substr, sizeof(buffer)); // Add the rest of the original string

        // Copy the result back into the original string using strlcpy
        ft_strlcpy(str, buffer, sizeof(buffer));
    }
}

int main() {
    char str[1024] = "hello $real hi there"; // Ensure enough space for modifications
    const char *substr = "$real";
    const char *replacement = "12345678910";

    printf("Original string: \"%s\"\n", str);
    replace_substring(str, substr, replacement);
    printf("Modified string: \"%s\"\n", str);

    return 0;
}
